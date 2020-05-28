cmake_minimum_required(VERSION 3.1)
project(JEC VERSION 0.1.0)

#set(CMAKE_BUILD_TYPE Debug)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()
message("Build type: " ${CMAKE_BUILD_TYPE})

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#find OpenSMT library
get_filename_component(CMAKE_MODULE_PATH
    "${CMAKE_CURRENT_LIST_DIR}/cmake/" ABSOLUTE)

find_package(opensmt REQUIRED)

#find GMP
get_filename_component(CMAKE_MODULE_PATH
    "${CMAKE_CURRENT_LIST_DIR}/cmake/" ABSOLUTE)

find_package(GMP REQUIRED)

option(PRODUCE_PROOF "Produce proof" OFF)

# the function is used to add all header files
function(include_sub_directories_recursively root_dir)
    if (IS_DIRECTORY ${root_dir})
        message("include dir: " ${root_dir})
        include_directories(${root_dir})
    endif()

    file(GLOB ALL_SUB RELATIVE ${root_dir} ${root_dir}/*)
    foreach(sub ${ALL_SUB})
        if (IS_DIRECTORY ${root_dir}/${sub})
            include_sub_directories_recursively(${root_dir}/${sub})
        endif()
    endforeach()
endfunction()

# add all header files
include_sub_directories_recursively(${CMAKE_SOURCE_DIR}/include)

file(GLOB_RECURSE SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)
message("Source file: " ${SOURCE_FILES})

set(JEC_ALL_SRCS main.cpp ${SOURCE_FILES})

add_executable(${PROJECT_NAME} ${JEC_ALL_SRCS})
target_include_directories(${PROJECT_NAME} PUBLIC ${OPENSMT_INCLUDE_DIR} ${GMP_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${OPENSMT_LIBRARY} ${GMP_LIBRARIES} ${GMPXX_LIBRARIES})
if(PRODUCE_PROOF)
    message("Compiling with PRODUCE_PROOF")
    target_compile_definitions(${filename} PUBLIC -DPRODUCE_PROOF)
endif(PRODUCE_PROOF)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
