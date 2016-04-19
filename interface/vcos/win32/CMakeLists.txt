
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -W4")

# Header originates from "Windows Services for UNIX Version 3.5" distrbution
# http://www.microsoft.com/en-us/download/details.aspx?id=274
set (UNIX_HEADERS
   dirent.h
   fcntl.h
   features.h
   limits.h
   stdarg.h
   syslog.h
   termios.h
   unistd.h
   va_list.h
   sys/unistd.h
   sys/endian.h
   sys/stat.h
   sys/statvfs.h
   sys/types.h
)

foreach (header ${UNIX_HEADERS})
   configure_file ("${header}" "${VIDEOCORE_HEADERS_BUILD_DIR}/${header}" COPYONLY)
endforeach ()

set (HEADERS
   vcos_platform.h
   vcos_platform_types.h
)

foreach (header ${HEADERS})
   configure_file ("${header}" "${VCOS_HEADERS_BUILD_DIR}/${header}" COPYONLY)
endforeach ()

add_subdirectory (../generic generic)

set (SOURCES
   vcos_pthreads.c
   vcos_dlfcn.c
   ../glibc/vcos_backtrace.c
   ../generic/vcos_generic_event_flags.c
   ../generic/vcos_mem_from_malloc.c
   ../generic/vcos_generic_named_sem.c
   ../generic/vcos_generic_safe_string.c
   ../generic/vcos_generic_reentrant_mtx.c
   ../generic/vcos_abort.c
   ../generic/vcos_cmd.c
   ../generic/vcos_init.c
   ../generic/vcos_msgqueue.c
   ../generic/vcos_logcat.c
   ../generic/vcos_generic_blockpool.c
)

add_library (vcos SHARED ${SOURCES})
target_link_libraries (vcos onecore)
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DWIN32DLL_EXPORTS -DVCOS_PROVIDER")

#install(FILES ${HEADERS} DESTINATION include)
install(TARGETS vcos DESTINATION lib)
