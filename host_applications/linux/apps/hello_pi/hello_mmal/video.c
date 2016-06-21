/*
Copyright (c) 2016, Raspberry Pi (Trading) Ltd
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of the copyright holder nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

// Video decode demo using MMAL

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <interface/mmal/mmal.h>
#include <interface/mmal/util/mmal_util.h>
#include <interface/mmal/util/mmal_default_components.h>
#include <interface/mmal/util/mmal_util_params.h>
#include <interface/mmal/mmal_parameters_video.h>

#include "bcm_host.h"
#include "ilclient.h"

#ifndef min
#define min(a,b) ((a)<(b)?(a):(b))
#endif

#ifndef max
#define max(a,b) ((a)>(b)?(a):(b))
#endif

typedef enum {false, true} bool;
typedef void CMMALVideoBuffer;

#define CLASSNAME "video_decode"
enum { LOGERROR, LOGWARNING, LOGDEBUG };
static void Log(int priority, const char *format, ...)
{
  char str[1024];
  va_list args;
  va_start(args, format);
  vsnprintf(str, sizeof str, format, args);
  va_end(args);
  puts(str);
}

#define LogF(priority, format, ...) Log(priority, "%12s::%4d:%-20s " format, CLASSNAME, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#define LogD(format, ...) LogF(LOGDEBUG, format, ##__VA_ARGS__)
#define LogE(format, ...) LogF(LOGERROR, format, ##__VA_ARGS__)

#ifdef WIN32
#define LogEWin32(format, status, mmal_status) LogE(format, status, mmal_status)
#define LogS(status, ...) if (status == MMAL_SUCCESS) {} else LogEWin32(" (status=0x%x %s)" ##__VA_ARGS__, status, mmal_status_to_string(status))
#else
#define LogS(status, format, ...) if (status == MMAL_SUCCESS) {} else LogE(format " (status=0x%x %s)", ##__VA_ARGS__, status, mmal_status_to_string(status))
#endif

typedef struct {
  int m_decoded_width;
  int m_decoded_height;
  MMAL_ES_FORMAT_T *m_es_format;
  MMAL_COMPONENT_T *m_dec;
  MMAL_PORT_T *m_dec_input;
  MMAL_PORT_T *m_dec_output;
  MMAL_POOL_T *m_dec_input_pool;
  MMAL_POOL_T *m_dec_output_pool;
  MMAL_POOL_T *m_vout_input_pool;
  MMAL_QUEUE_T *m_queue;
  float m_fps;
} decoder_state_t;

typedef struct {
  int extrasize;
  int fpsrate;
  int fpsscale;
  void *extradata;
  MMAL_FOURCC_T m_codingType;
  MMAL_FOURCC_T m_encoding;
} stream_info_t;


static int GetAllowedReferences() { return 5; }

static void PortSettingsChanged(decoder_state_t *state, MMAL_BUFFER_HEADER_T *buffer)
{
  MMAL_STATUS_T status;
  MMAL_EVENT_FORMAT_CHANGED_T *fmt = mmal_event_format_changed_get(buffer);
  mmal_format_copy(state->m_es_format, fmt->format);

  if (state->m_es_format->es->video.crop.width && state->m_es_format->es->video.crop.height)
  {
    float m_aspect_ratio = 1.0f;
    if (state->m_es_format->es->video.par.num && state->m_es_format->es->video.par.den)
      m_aspect_ratio = (float)(state->m_es_format->es->video.par.num * state->m_es_format->es->video.crop.width) / (state->m_es_format->es->video.par.den * state->m_es_format->es->video.crop.height);
    state->m_decoded_width = state->m_es_format->es->video.crop.width;
    state->m_decoded_height = state->m_es_format->es->video.crop.height;
    LogD("format changed: %dx%d %.2f", state->m_decoded_width, state->m_decoded_height, m_aspect_ratio);
  }
  else
    LogE("format changed: Unexpected %dx%d", state->m_es_format->es->video.crop.width, state->m_es_format->es->video.crop.height);

  mmal_format_copy(state->m_dec_output->format, state->m_es_format);

  status = mmal_port_parameter_set_boolean(state->m_dec_output, MMAL_PARAMETER_ZERO_COPY,  MMAL_TRUE);
  LogS(status, "Failed to enable zero copy mode on %s", state->m_dec_output->name);

  status = mmal_port_format_commit(state->m_dec_output);
  LogS(status, "Failed to commit decoder output port");

  LogD("Output %dx%d (%dx%d) encoding %4.4s", state->m_es_format->es->video.width, state->m_es_format->es->video.height, state->m_es_format->es->video.crop.width, state->m_es_format->es->video.crop.height, &state->m_dec_output->format->encoding);

  if (!state->m_dec_output_pool)
  {
    LogD("create output pool: %d x %d, (min:%d recommended:%d)", state->m_dec_output->buffer_num, state->m_dec_output->buffer_size, state->m_dec_output->buffer_size_min, state->m_dec_output->buffer_num_recommended);
    state->m_dec_output_pool = mmal_port_pool_create(state->m_dec_output, state->m_dec_output->buffer_num, state->m_dec_output->buffer_size);
    if (!state->m_dec_output_pool)
      LogE("Failed to create pool for decoder output port");
    // prime decoder output buffers
    MMAL_BUFFER_HEADER_T *buffer;
    while (buffer = mmal_queue_get(state->m_dec_output_pool->queue), buffer)
    {
      LogD("Sending buffer:%p to dec_output", buffer);
      mmal_buffer_header_reset(buffer);
      buffer->cmd = 0;
      status = mmal_port_send_buffer(state->m_dec_output, buffer);
      if (status != MMAL_SUCCESS)
      {
        mmal_buffer_header_release(buffer);
        LogE("Failed to return buffer to dec_output");
        return;
      }
    }
  }
}

static void dec_control_port_cb(MMAL_PORT_T *port, MMAL_BUFFER_HEADER_T *buffer)
{
  decoder_state_t *state = (decoder_state_t *)port->userdata;
  LogD("port:%p buffer %p, len %d cmd:%4.4s", port, buffer, buffer->length, &buffer->cmd);
  mmal_queue_put(state->m_queue, buffer);
}

static void dec_input_port_cb(MMAL_PORT_T *port, MMAL_BUFFER_HEADER_T *buffer)
{
  //decoder_state_t *state = (decoder_state_t *)port->userdata;
  LogD("port:%p buffer %p, len %d cmd:%4.4s", port, buffer, buffer->length, &buffer->cmd);
  mmal_buffer_header_release(buffer);
}

static void dec_output_port_cb(MMAL_PORT_T *port, MMAL_BUFFER_HEADER_T *buffer)
{
  decoder_state_t *state = (decoder_state_t *)port->userdata;
  LogD("port:%p buffer %p, len %d cmd:%4.4s", port, buffer, buffer->length, &buffer->cmd);
  mmal_queue_put(state->m_queue, buffer);
}


bool SendCodecConfigData(decoder_state_t *state, stream_info_t m_hints)
{
  MMAL_STATUS_T status;
  if (!state->m_dec_input_pool || !m_hints.extrasize)
    return true;
  // send codec config data
  MMAL_BUFFER_HEADER_T *buffer = mmal_queue_timedwait(state->m_dec_input_pool->queue, 500);
  if (!buffer)
  {
    LogE("mmal_queue_get failed");
    return false;
  }

  mmal_buffer_header_reset(buffer);
  buffer->cmd = 0;
  buffer->length = min(m_hints.extrasize, buffer->alloc_size);
  memcpy(buffer->data, m_hints.extradata, buffer->length);
  buffer->flags |= MMAL_BUFFER_HEADER_FLAG_FRAME_END | MMAL_BUFFER_HEADER_FLAG_CONFIG;
  LogD("%-8p %-6d flags:%x", buffer, buffer->length, buffer->flags);
  status = mmal_port_send_buffer(state->m_dec_input, buffer);
  LogS(status, "Failed send buffer to decoder input port");
  return true;
}

static int test_mmal_setup(decoder_state_t *state, stream_info_t m_hints)
{
  MMAL_STATUS_T status;

  // initialize mmal.
  status = mmal_component_create(MMAL_COMPONENT_DEFAULT_VIDEO_DECODER, &state->m_dec);
  LogS(status, "Failed to create MMAL decoder component %s", MMAL_COMPONENT_DEFAULT_VIDEO_DECODER);

  state->m_dec->control->userdata = (struct MMAL_PORT_USERDATA_T *)state;
  status = mmal_port_enable(state->m_dec->control, dec_control_port_cb);
  LogS(status, "Failed to enable decoder control port %s", MMAL_COMPONENT_DEFAULT_VIDEO_DECODER);

  state->m_dec_input = state->m_dec->input[0];

  state->m_dec_input->format->type = MMAL_ES_TYPE_VIDEO;
  state->m_dec_input->format->encoding = m_hints.m_codingType;
  if (m_hints.fpsrate > 0 && m_hints.fpsscale > 0)
  {
    state->m_dec_input->format->es->video.frame_rate.num = m_hints.fpsrate;
    state->m_dec_input->format->es->video.frame_rate.den = m_hints.fpsscale;
    state->m_fps = m_hints.fpsrate / m_hints.fpsscale;
  }
  else
    state->m_fps = 0.0f;
  //state->m_dec_input->format->flags |= MMAL_ES_FORMAT_FLAG_FRAMED;

  status = mmal_port_parameter_set_boolean(state->m_dec_input, MMAL_PARAMETER_VIDEO_DECODE_ERROR_CONCEALMENT, MMAL_FALSE);
  LogS(status, "Failed to disable error concealment on %s", state->m_dec_input->name);

  status = mmal_port_parameter_set_uint32(state->m_dec_input, MMAL_PARAMETER_EXTRA_BUFFERS, GetAllowedReferences());
  LogS(status, "Failed to enable extra buffers on %s", state->m_dec_input->name);

  status = mmal_port_parameter_set_uint32(state->m_dec_input, MMAL_PARAMETER_VIDEO_INTERPOLATE_TIMESTAMPS, 1);
  LogS(status, "Failed to disable interpolate timestamps mode on %s", state->m_dec_input->name);

  status = mmal_port_format_commit(state->m_dec_input);
  LogS(status, "Failed to commit format for decoder input port %s", state->m_dec_input->name);

  state->m_dec_input->buffer_size = state->m_dec_input->buffer_size_recommended;
  state->m_dec_input->buffer_num = state->m_dec_input->buffer_num_recommended;

  state->m_dec_input->userdata = (struct MMAL_PORT_USERDATA_T *)state;
  status = mmal_port_enable(state->m_dec_input, dec_input_port_cb);
  LogS(status, "Failed to enable decoder input port %s", state->m_dec_input->name);

  state->m_dec_output = state->m_dec->output[0];

  // set up initial decoded frame format - will likely change from this
  state->m_dec_output->format->encoding = state->m_dec_output->format->encoding_variant = m_hints.m_encoding;
  state->m_es_format = mmal_format_alloc();
  mmal_format_copy(state->m_es_format, state->m_dec_output->format);

  status = mmal_port_parameter_set_boolean(state->m_dec_output, MMAL_PARAMETER_ZERO_COPY,  MMAL_TRUE);
  LogS(status, "Failed to enable zero copy mode on %s", state->m_dec_output->name);

  status = mmal_port_format_commit(state->m_dec_output);
  LogS(status, "Failed to commit decoder output format");

  LogD("Output %dx%d (%dx%d) encoding %4.4s", state->m_es_format->es->video.width, state->m_es_format->es->video.height, state->m_es_format->es->video.crop.width, state->m_es_format->es->video.crop.height, &state->m_dec_output->format->encoding);

  state->m_dec_output->buffer_size = state->m_dec_output->buffer_size_min;
  state->m_dec_output->buffer_num = max(GetAllowedReferences(), state->m_dec_output->buffer_num_recommended);
  state->m_dec_output->userdata = (struct MMAL_PORT_USERDATA_T *)state;
  status = mmal_port_enable(state->m_dec_output, dec_output_port_cb);
  LogS(status, "Failed to enable decoder output port");

  status = mmal_component_enable(state->m_dec);
  LogS(status, "Failed to enable decoder component %s", state->m_dec->name);

  LogD("create input pool: %d x %d, (min:%d recommended:%d)", state->m_dec_input->buffer_num, state->m_dec_input->buffer_size, state->m_dec_input->buffer_size_min, state->m_dec_input->buffer_num_recommended);
  state->m_dec_input_pool = mmal_port_pool_create(state->m_dec_input, state->m_dec_input->buffer_num, state->m_dec_input->buffer_size);
  LogS(status, "Failed to create pool for decoder input port");

  if (!SendCodecConfigData(state, m_hints))
    return -1;

  state->m_queue = mmal_queue_create();
  if (!state->m_queue)
  {
    LogE("Failed to create mmal queue");
    return -1;
  }
  return status;
}

static int test_mmal_decode(decoder_state_t *state, stream_info_t m_hints, const char *filename, const char *outfilename)
{
  MMAL_STATUS_T status;
  FILE *in, *out = NULL;
  if((in = fopen(filename, "rb")) == NULL)
    return -2;
  if (outfilename && (out = fopen(outfilename, "wb")) == NULL)
    return -2;

  while (1)
  {
    MMAL_BUFFER_HEADER_T *buffer = mmal_queue_timedwait(state->m_dec_input_pool->queue, 10);
    if (buffer)
    {
      buffer->length = fread(buffer->data, 1, buffer->alloc_size, in);
      if (buffer->length < 0)
      {
        LogE("fread returned %d", buffer->length);
        return -4;
      }
      else if (buffer->length > 0)
      {
        buffer->flags = MMAL_BUFFER_HEADER_FLAG_USER0;
        if (feof(in))
          buffer->flags |= MMAL_BUFFER_HEADER_FLAG_EOS;

        LogD("Sending buffer:%p to dec_input length:%d/%d flags:%x", buffer, buffer->length, buffer->alloc_size, buffer->flags);
        status = mmal_port_send_buffer(state->m_dec_input, buffer);
        LogS(status, "mmal_port_send_buffer failed");
      }
    }
    buffer = mmal_queue_timedwait(state->m_queue, 10);
    if (buffer)
    {
      assert(!(buffer->flags & MMAL_BUFFER_HEADER_FLAG_TRANSMISSION_FAILED));
      if (buffer->cmd == MMAL_EVENT_ERROR)
      {
        status = (MMAL_STATUS_T)*(uint32_t *)buffer->data;
        LogS(status, "Error");
      }
      else if (buffer->cmd == 0)
      {
        assert(!(buffer->flags & MMAL_BUFFER_HEADER_FLAG_DECODEONLY));
        if (!(buffer->flags & MMAL_BUFFER_HEADER_FLAG_CORRUPTED))
        {
          int eos = buffer->flags & MMAL_BUFFER_HEADER_FLAG_EOS;
          LogD("got decoded buffer:%p buffer_size(%u) dts:%.3f pts:%.3f flags:%x:%x",
             buffer, buffer->length, buffer->dts*1e-6, buffer->pts*1e-6, buffer->flags, buffer->type->video.flags);

          if (out && m_hints.m_encoding == MMAL_ENCODING_I420)
            fwrite(buffer->data, 1, buffer->length, out);

          mmal_buffer_header_reset(buffer);
          buffer->cmd = 0;
          LogD("Sending buffer:%p to dec_output", buffer);
          status = mmal_port_send_buffer(state->m_dec_output, buffer);
          LogS(status, "Failed to return buffer to dec_output");
          buffer = NULL;// don't want to release it
          if (eos)
          {
            LogD("stream complete!");
            break;
          }
        }
      }
      else if (buffer->cmd == MMAL_EVENT_FORMAT_CHANGED)
      {
        PortSettingsChanged(state, buffer);
      }
      if (buffer)
        mmal_buffer_header_release(buffer);
    }
  }
  fclose(in);
  if (out)
    fclose(out);
  return 0;
}

static void test_mmal_destroy(decoder_state_t *state, stream_info_t m_hints)
{
  if (state->m_queue)
    mmal_queue_destroy(state->m_queue);

  if (state->m_dec && state->m_dec->control && state->m_dec->control->is_enabled)
    mmal_port_disable(state->m_dec->control);

  if (state->m_dec_input && state->m_dec_input->is_enabled)
    mmal_port_disable(state->m_dec_input);

  if (state->m_dec_output && state->m_dec_output->is_enabled)
    mmal_port_disable(state->m_dec_output);
  state->m_dec_output = NULL;

  if (state->m_dec && state->m_dec->is_enabled)
    mmal_component_disable(state->m_dec);

  if (state->m_dec_input_pool)
    mmal_port_pool_destroy(state->m_dec_input, state->m_dec_input_pool);
  state->m_dec_input_pool = NULL;
  state->m_dec_input = NULL;

  if (state->m_dec)
    mmal_component_destroy(state->m_dec);
  state->m_dec = NULL;

  mmal_format_free(state->m_es_format);
}

int main(int argc, char **argv)
{
  decoder_state_t decoder_state = { 0 };
  stream_info_t m_hints = { 0 };
  m_hints.m_codingType = MMAL_ENCODING_H264;
  m_hints.m_encoding = MMAL_ENCODING_I420;
  //m_hints.m_encoding = MMAL_ENCODING_OPAQUE;
  if (argc < 2)
  {
     printf("Usage: %s <filename>\n", argv[0]);
     exit(1);
  }

  // MMAL application doesn't really need to call bcm_host_init as mmal core
  // would handle vchiq related initiliazation. For Windows bcm_host_init has 
  // not been ported yet.
  //bcm_host_init();

  test_mmal_setup(&decoder_state, m_hints);
  test_mmal_decode(&decoder_state, m_hints, argv[1], argc >=3 ? argv[2]:NULL);
  test_mmal_destroy(&decoder_state, m_hints);
  return 0;
}

