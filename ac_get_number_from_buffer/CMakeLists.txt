# Set cmake version
cmake_minimum_required(VERSION 3.31.3)

# Set project name
project(ac_get_number_from_buffer VERSION 1.0.0 LANGUAGES C)

# Set c compile version
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

# Set build type
set(CMAKE_BUILD_TYPE "Release")

# Generate compile json file
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Create library instance
add_library(ac_get_number_from_buffer SHARED src/library/ac_get_number_from_buffer.c)

# Add headers folder
target_include_directories(ac_get_number_from_buffer PUBLIC src/library)

# Define macro for enabling the library to be generated as a dynamic library
target_compile_definitions(ac_get_number_from_buffer PRIVATE BUILD_DLL)

# Generate tests executables
option(AC_GENERATE_TESTS "Generate test executables" ON)

if (AC_GENERATE_TESTS)
    add_executable(ac_test_1 src/tests/test_1.c)
    target_include_directories(ac_test_1 PUBLIC src/library)
    target_link_libraries(ac_test_1 PRIVATE ac_get_number_from_buffer)
endif()
