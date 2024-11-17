cmake_minimum_required(VERSION 3.10)
project(ac_lib)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS_DEBUG "-O0")

include_directories(${CMAKE_SOURCE_DIR}/src)

option(BUILD_TESTS "Build the test project" ON)
if(BUILD_TESTS)
    add_subdirectory(test)
endif()

add_library(ac_lib STATIC src/ac_string.c src/ac_vector.c src/ac_input.c)
