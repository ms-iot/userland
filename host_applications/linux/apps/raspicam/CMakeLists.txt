
# raspistill/raspivid/raspiyuv

SET(COMPILE_DEFINITIONS -Werror)

include_directories(${PROJECT_SOURCE_DIR}/host_applications/linux/libs/bcm_host/include)
include_directories(${PROJECT_SOURCE_DIR}/host_applications/linux/apps/raspicam/)

set (GL_SCENE_SOURCES
   gl_scenes/models.c
   gl_scenes/mirror.c
   gl_scenes/yuv.c
   gl_scenes/sobel.c
   gl_scenes/square.c
   gl_scenes/teapot.c)

set (COMMON_SOURCES
   RaspiCamControl.c
   RaspiCLI.c
   RaspiPreview.c)

set (MMAL_LIBS mmal_core mmal_util mmal_vc_client)

if(WIN32)
    # TODO Port raspi* to Windows

else()
    add_executable(raspistill ${COMMON_SOURCES} RaspiStill.c  RaspiTex.c RaspiTexUtil.c tga.c ${GL_SCENE_SOURCES})
    add_executable(raspiyuv   ${COMMON_SOURCES} RaspiStillYUV.c)
    add_executable(raspivid   ${COMMON_SOURCES} RaspiVid.c)
    add_executable(raspividyuv  ${COMMON_SOURCES} RaspiVidYUV.c)

    target_link_libraries(raspistill ${MMAL_LIBS} vcos bcm_host GLESv2 EGL m)
    target_link_libraries(raspiyuv   ${MMAL_LIBS} vcos bcm_host)
    target_link_libraries(raspivid   ${MMAL_LIBS} vcos bcm_host)
    target_link_libraries(raspividyuv   ${MMAL_LIBS} vcos bcm_host)

    install(TARGETS raspistill raspiyuv raspivid raspividyuv RUNTIME DESTINATION bin)
endif()
