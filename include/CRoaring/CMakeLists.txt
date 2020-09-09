file(GLOB_RECURSE c_files ./*.c)

add_library(croaring_lib_shared SHARED ${c_files})
add_library(croaring_lib_static STATIC ${c_files})

set_target_properties(croaring_lib_shared PROPERTIES OUTPUT_NAME "croaring")
set_target_properties(croaring_lib_static PROPERTIES OUTPUT_NAME "croaring")

set_target_properties(croaring_lib_shared PROPERTIES VERSION 1.0 SOVERSION 1)
set_target_properties(croaring_lib_static PROPERTIES VERSION 1.0 SOVERSION 1)

set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})
INSTALL(TARGETS croaring_lib_shared croaring_lib_static 
    LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib 
    ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
)
