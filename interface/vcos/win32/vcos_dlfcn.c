/*
Copyright (c) 2012, Broadcom Europe Ltd
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

#include "interface/vcos/vcos.h"
#include "interface/vcos/vcos_dlfcn.h"


void *vcos_dlopen(const char *name, int mode)
{
#ifdef WIN32_KERN
    UNREFERENCED_PARAMETER(name);
    UNREFERENCED_PARAMETER(mode);
    // Not Implemented
    vcos_assert(FALSE);
    return NULL;
#else
    UNREFERENCED_PARAMETER(mode);
    return LoadLibrary(name);
#endif
}

void (*vcos_dlsym(void *handle, const char *name))(void)
{
#ifdef WIN32_KERN
    UNREFERENCED_PARAMETER(handle);
    UNREFERENCED_PARAMETER(name);
    // Not Implemented
    vcos_assert(FALSE);
    return NULL;
#else
#pragma warning(suppress : 4113 )
    return GetProcAddress(handle, name);
#endif
}

int vcos_dlclose (void *handle)
{
#ifdef WIN32_KERN
    UNREFERENCED_PARAMETER(handle);
    // Not Implemented
    vcos_assert(FALSE);
    return 0;
#else
    return FreeLibrary(handle);
#endif
}

int vcos_dlerror(int *err, char *buf, size_t buflen)
{
#ifdef WIN32_KERN
   UNREFERENCED_PARAMETER(err);
    UNREFERENCED_PARAMETER(buf);
    UNREFERENCED_PARAMETER(buflen);
    // Not Implemented
    vcos_assert(FALSE);
    return 0;
#else
   /* not really threadsafe! */
   DWORD errorNumber = GetLastError();
   char errmsg[1];
   errmsg[0] = (char)(errorNumber + '0');

   vcos_assert(buflen > 0);

   if (errmsg)
   {
      *err = -1;
      strncpy(buf, errmsg, 1);
      buf[2] = '\0';
   }
   else
   {
      *err = 0;
      buf[0] = '\0';
   }
   return 0;
#endif
}




