# Container module needs to go in as a plugins so different prefix
# and install path
set(CMAKE_SHARED_LIBRARY_PREFIX "")

if (WIN32)
    set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -W4 -D_TIME_T_DEFINED")
endif ()

# Make sure the compiler can find the necessary include files
include_directories (../..)

add_library(reader_avi ${LIBRARY_TYPE} avi_reader.c)

target_link_libraries(reader_avi containers)

install(TARGETS reader_avi DESTINATION ${VMCS_PLUGIN_DIR})

add_library(writer_avi ${LIBRARY_TYPE} avi_writer.c)

target_link_libraries(writer_avi containers)

install(TARGETS writer_avi DESTINATION ${VMCS_PLUGIN_DIR})

