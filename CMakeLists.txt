cmake_minimum_required(VERSION 3.1)
project(JEC VERSION 0.1.0)

#set(CMAKE_BUILD_TYPE Debug)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
    SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall") 
else()
    SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g2 -ggdb")
endif()
message("Build type: " ${CMAKE_BUILD_TYPE})

# Check platforms
if (CMAKE_HOST_WIN32)
    set(WINDOWS 1)
    message("The enviriment is in windows.")
elseif(CMAKE_HOST_APPLE)
    set(MACOS 1)
    message("The enviriment is in macos.")
elseif(CMAKE_HOST_UNIX)
    set(LINUX 1)
    message("The enviriment is in linux.")
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (LINUX)
    #find Opensmt library
    get_filename_component(CMAKE_MODULE_PATH
        "${CMAKE_CURRENT_LIST_DIR}/cmake/" ABSOLUTE)
    find_package(Opensmt REQUIRED)
    #find CaDiCaL library
    get_filename_component(CMAKE_MODULE_PATH
        "${CMAKE_CURRENT_LIST_DIR}/cmake/" ABSOLUTE)
    find_package(CaDiCaL REQUIRED)
endif()

#find GMP
get_filename_component(CMAKE_MODULE_PATH
    "${CMAKE_CURRENT_LIST_DIR}/cmake/" ABSOLUTE)
find_package(GMP REQUIRED)

# add croaring
add_library(croaring STATIC ${PROJECT_SOURCE_DIR}/include/CRoaring/roaring.c)
target_include_directories(croaring PUBLIC ${PROJECT_SOURCE_DIR}/include/CRoaring/)

# the function is used to add all header files
function(include_sub_directories_recursively root_dir)
    if (IS_DIRECTORY ${root_dir})
        message("include dir: " ${root_dir})
        include_directories(${root_dir})
    endif()

    file(GLOB ALL_SUB RELATIVE ${root_dir} ${root_dir}/*)
    foreach(sub ${ALL_SUB})
        if (IS_DIRECTORY ${root_dir}/${sub} AND NOT(${sub} STREQUAL "gmp") AND NOT(${sub} STREQUAL "opensmt") )
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
target_link_libraries(${PROJECT_NAME} croaring)

if (LINUX)
    target_include_directories(${PROJECT_NAME} PUBLIC ${OPENSMT_INCLUDE_DIR} ${GMP_C_INCLUDE_DIR} ${GMP_CXX_INCLUDE_DIR} ${CADICAL_C_INCLUDE_DIR} ${CADICAL_CXX_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${OPENSMT_LIBRARY} ${GMP_LIBRARIES} ${GMPXX_LIBRARIES} ${CADICAL_LIBRARY})
endif()