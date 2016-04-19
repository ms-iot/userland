# Implementation of getopt originated from 
# "Windows Services for UNIX Version 3.5" distrbution
# http://www.microsoft.com/en-us/download/details.aspx?id=274

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -W4")

set (HEADERS
   getopt.h
)

foreach (header ${HEADERS})
   configure_file ("${header}" "${VIDEOCORE_HEADERS_BUILD_DIR}/${header}" COPYONLY)
endforeach ()

set (SOURCES
   getopt.c
   getopt1.c
)


add_library (getopt STATIC ${SOURCES})
target_link_libraries (getopt)
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")

install(FILES ${HEADERS} DESTINATION include)
install(TARGETS getopt DESTINATION lib)
