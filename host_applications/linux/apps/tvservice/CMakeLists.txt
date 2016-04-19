add_executable(tvservice tvservice.c)

if(WIN32)
target_link_libraries(tvservice vchostif getopt)
else()
target_link_libraries(tvservice vchostif)
endif()

install(TARGETS tvservice
        RUNTIME DESTINATION bin)
