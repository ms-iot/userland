set(EXEC hello_mmal)
set(SRCS video.c)

add_executable(${EXEC} ${SRCS})

target_link_libraries(${EXEC} mmal_core mmal_util)

install(TARGETS ${EXEC}
        RUNTIME DESTINATION bin)
