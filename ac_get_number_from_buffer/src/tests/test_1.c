#include <ac_get_number_from_buffer.h>
#include <string.h>
#include <stdio.h>

/*
 * Key takes:
 * Failure of example 1:
 * The first example fails with an error code of 6. The reason is that the items
 * are takes as literal values for characters. In ASCII text the values for
 * '1', '2' and '3' is 49, 50 and 51 and not 1, 2, 3. The function if detects
 * something smaller or bigger then '0' or '9' it will return 6.
 *
 * Use of string literal:
 * As it can be noticed that we can use string literals just as arrays.
 * Also the use of the function strlen is available.
 *
 * Checking for certain errors:
 * Notice we check for specific useful errors. It is recommended to check using
 * the macros provided.
 */

int main(void)
{
    char example_array_buffer[3] = {1, 2, 3};
    char *example_string_literal_buffer = "1500000";

    short output_number_from_array = 0;
    int output_number_from_string_literal = 0;

    size_t error_code_1 = 0;
    size_t error_code_2 = 0;

    error_code_1 = ac_get_number_from_buffer(example_array_buffer, 3, &output_number_from_array, sizeof(short));
    error_code_2 = ac_get_number_from_buffer(example_string_literal_buffer, strlen(example_string_literal_buffer), &output_number_from_string_literal, sizeof(int));

    printf("Example array buffer contents: \n");
    for (int i = 0; i < 3; i++) printf("%d\n", example_array_buffer[i]);
    printf("Output number: %d\n", output_number_from_array);
    printf("Error code: %zu\n", error_code_1);

    // Error code checking
    if (error_code_1 != 0) {
        printf("An error has happened reading the number from the array buffer!\n");
        if (error_code_1 == AC_ERROR_CODE_GET_NUMBER_FROM_BUFFER_NOT_A_NUMBER) {
            printf("Buffer contains corrupted/broken/non-number characters!\n");
        }
    }

    printf("Example string literal buffer: %s\n", example_string_literal_buffer);
    printf("Output number: %d\n", output_number_from_string_literal);
    printf("Error code: %zu\n", error_code_2);

    return 0;
}
