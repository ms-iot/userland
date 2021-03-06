SET( MMAL_TOP ../../.. )

include_directories(${PROJECT_SOURCE_DIR}/host_applications/linux/libs/bcm_host/include)

SET( MMALPLAY_TOP ${MMAL_TOP}/host_applications/vmcs/test_apps/mmalplay )

# Set compile options
if (WIN32)
    SET ( COMPILE_OPTIONS )
	SET ( ADDITIONAL_LINK_LIBRARIES )
else ()
    SET ( COMPILE_OPTIONS -Wl,--whole-archive mmal_components containers -Wl,--no-whole-archive )
	SET ( ADDITIONAL_LINK_LIBRARIES bcm_host mmal_vc_client )
endif ()

add_executable(mmalplay ${MMALPLAY_TOP}/playback.c ${MMALPLAY_TOP}/mmalplay.c)
target_link_libraries(mmalplay mmal_core mmal_util ${ADDITIONAL_LINK_LIBRARIES})
target_link_libraries(mmalplay ${COMPILE_OPTIONS} mmal_core)
target_link_libraries(mmalplay vcos)

SET( MMALCAM_TOP ${MMAL_TOP}/host_applications/vmcs/test_apps/mmalcam )
add_executable(mmalcam ${MMALCAM_TOP}/viewfinder.c ${MMALCAM_TOP}/mmalcam.c)
target_link_libraries(mmalcam mmal_core mmal_util ${ADDITIONAL_LINK_LIBRARIES})
target_link_libraries(mmalcam -Wl,--whole-archive mmal_components -Wl,--no-whole-archive mmal_core)
target_link_libraries(mmalcam vcos)

SET( MMALEXAMPLES_TOP ${MMAL_TOP}/interface/mmal/test/examples )
add_executable(mmal_example_connections ${MMALEXAMPLES_TOP}/example_connections.c)
target_link_libraries(mmal_example_connections mmal_core mmal_util ${ADDITIONAL_LINK_LIBRARIES})
target_link_libraries(mmal_example_connections -Wl,--whole-archive mmal_components -Wl,--no-whole-archive mmal_core)
add_executable(mmal_example_graph ${MMALEXAMPLES_TOP}/example_graph.c)
target_link_libraries(mmal_example_graph mmal_core mmal_util ${ADDITIONAL_LINK_LIBRARIES})
target_link_libraries(mmal_example_graph -Wl,--whole-archive mmal_components -Wl,--no-whole-archive mmal_core)
add_executable(mmal_example_basic_1 ${MMALEXAMPLES_TOP}/example_basic_1.c)
target_link_libraries(mmal_example_basic_1 mmal_core mmal_util ${ADDITIONAL_LINK_LIBRARIES})
target_link_libraries(mmal_example_basic_1 -Wl,--whole-archive mmal_components -Wl,--no-whole-archive mmal_core)
add_executable(mmal_example_basic_2 ${MMALEXAMPLES_TOP}/example_basic_2.c)
target_link_libraries(mmal_example_basic_2 mmal_core mmal_util ${ADDITIONAL_LINK_LIBRARIES})
target_link_libraries(mmal_example_basic_2 -Wl,--whole-archive mmal_components -Wl,--no-whole-archive mmal_core)
