#include <ac_get_number_from_buffer.h>

ac_size_t ac_get_number_from_buffer(void *input_buffer, ac_signed_size_t input_buffer_length, void *output_number, ac_signed_size_t output_number_type_size)
{
    // Validate input parameters
    if (input_buffer == AC_NULL) return 1;
    if (input_buffer_length <= 0) return 2;
    if (output_number == AC_NULL) return 3;
    if (output_number_type_size <= 0) return 4;

    if (output_number_type_size == AC_TYPE_BYTES_1 && input_buffer_length > AC_TYPE_BYTES_1_LENGTH) return 5;
    else if (output_number_type_size == AC_TYPE_BYTES_2 && input_buffer_length > AC_TYPE_BYTES_2_LENGTH) return 5;
    else if (output_number_type_size == AC_TYPE_BYTES_4 && input_buffer_length > AC_TYPE_BYTES_4_LENGTH) return 5;
    else if (output_number_type_size == AC_TYPE_BYTES_MAX && input_buffer_length > AC_TYPE_BYTES_MAX_LENGTH) return 5;

    // Initialize variables
    char local_current_char = '\0';
    ac_size_t local_output_number = 0;
    ac_size_t local_loop_index = 0;

    // Read loop
    while (local_loop_index < input_buffer_length) {
        local_current_char = ((char *)input_buffer)[local_loop_index];

        if (local_current_char < '0' || local_current_char > '9') return 6;

        local_output_number *= 10;
        local_output_number += local_current_char - '0';

        local_loop_index += 1;
    }

    // Type cast output number
    if (output_number_type_size == AC_TYPE_BYTES_1) {
        *((uint8_t *)output_number) = ((uint8_t)local_output_number);
    } else if (output_number_type_size == AC_TYPE_BYTES_2) {
        *((uint16_t *)output_number) = ((uint16_t)local_output_number);
    } else if (output_number_type_size == AC_TYPE_BYTES_4) {
        *((uint32_t *)output_number) = ((uint32_t)local_output_number);
    } else if (output_number_type_size == AC_TYPE_BYTES_MAX) {
        *((ac_size_t *)output_number) = ((ac_size_t)local_output_number);
    }

    // Exit succeesfully
    return 0;
}
