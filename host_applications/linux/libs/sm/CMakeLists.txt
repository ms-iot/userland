
if (WIN32)
   set(VCOS_PLATFORM win32)
   # The vcsm module was not abstracted properly to export function like vcos.
   # So compiling this as a static lib instead.
   add_library(vcsm STATIC user-vcsm-win32.c)
else ()
   set(VCOS_PLATFORM pthreads)
   add_definitions(-Wall -Werror)
   add_library(vcsm ${SHARED} user-vcsm.c)
endif ()

include_directories( ../../../..
                     ../../../../interface/vcos/${VCOS_PLATFORM}
                     ../../../../host_applications/linux/kernel_headers )

target_link_libraries(vcsm vcos)

install(TARGETS vcsm DESTINATION lib)

