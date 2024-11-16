cmake_minimum_required(VERSION 3.10)
project(test)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS_DEBUG "-O0")

include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(app ${CMAKE_SOURCE_DIR}/src/main.c)
target_link_libraries(app ac_lib)
