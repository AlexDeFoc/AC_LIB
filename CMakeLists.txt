cmake_minimum_required(VERSION 3.10)
project(ac_lib)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS_DEBUG "-O0")

include_directories(${CMAKE_SOURCE_DIR}/src)

add_library(ac_lib STATIC src/ac_string.c)
