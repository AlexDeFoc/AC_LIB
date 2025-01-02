#ifndef AC_GET_NUMBER_FROM_BUFFER_H
#define AC_GET_NUMBER_FROM_BUFFER_H

// Important macros in use:
// ERROR code for not-a-number characters inside input buffer
#ifndef AC_ERROR_CODE_GET_NUMBER_FROM_BUFFER_NOT_A_NUMBER
#define AC_ERROR_CODE_GET_NUMBER_FROM_BUFFER_NOT_A_NUMBER 6
#endif

// Included libraries
#include <inttypes.h>

// Define null type
#ifndef AC_NULL
#define AC_NULL ((void *)0)
#endif

// Define byte types
#ifndef AC_TYPE_BYTES_1
#define AC_TYPE_BYTES_1 1
#endif

#ifndef AC_TYPE_BYTES_2
#define AC_TYPE_BYTES_2 2
#endif

#ifndef AC_TYPE_BYTES_4
#define AC_TYPE_BYTES_4 4
#endif

// Define byte types lengths
#ifndef AC_TYPE_BYTES_1_LENGTH
#define AC_TYPE_BYTES_1_LENGTH UINT8_MAX
#endif

#ifndef AC_TYPE_BYTES_2_LENGTH
#define AC_TYPE_BYTES_2_LENGTH UINT16_MAX
#endif

#ifndef AC_TYPE_BYTES_4_LENGTH
#define AC_TYPE_BYTES_4_LENGTH UINT32_MAX
#endif

// Define based on architecture
#if defined(__x86_64__) || defined(__ppc64__) || defined(__LP64__) || defined(_WIN64)
// 64 bit systems
#ifndef AC_TYPE_BYTES_8
#define AC_TYPE_BYTES_8 8
#endif

#ifndef AC_TYPE_BYTES_MAX
#define AC_TYPE_BYTES_MAX AC_TYPE_BYTES_8
#endif

#ifndef AC_TYPE_BYTES_8_LENGTH
#define AC_TYPE_BYTES_8_LENGTH UINT64_MAX
#endif

#ifndef AC_TYPE_BYTES_MAX_LENGTH
#define AC_TYPE_BYTES_MAX_LENGTH AC_TYPE_BYTES_8_LENGTH
#endif

#ifndef ac_signed_size_t
#define ac_signed_size_t int64_t
#endif

#ifndef ac_size_t
#define ac_size_t uint64_t
#endif

// 32 bit systems
#else
#ifndef AC_TYPE_BYTES_MAX
#define AC_TYPE_BYTES_MAX AC_TYPE_BYTES_4
#endif

#ifndef AC_TYPE_BYTES_MAX_LENGTH
#define AC_TYPE_BYTES_MAX_LENGTH AC_TYPE_BYTES_4_LENGTH
#endif

#ifndef ac_signed_size_t
#define ac_signed_size_t int32_t
#endif

#ifndef ac_size_t
#define ac_size_t uint32_t
#endif
#endif

// Enable the library to be generated as dynamic - use ENABLE_DYNAMIC in front of functions, use BUILD_DLL in CMakeLists
#if defined(_WIN32) || defined(__CYGWIN__)
  #ifdef BUILD_DLL
    #define ENABLE_DYNAMIC __declspec(dllexport)
  #else
    #define ENABLE_DYNAMIC __declspec(dllimport)
  #endif
#else
  #define ENABLE_DYNAMIC
#endif

ENABLE_DYNAMIC ac_size_t ac_get_number_from_buffer(void *input_buffer, ac_signed_size_t input_buffer_length, void *output_number, ac_signed_size_t output_number_type_size);

#endif
