#define AC_LIB_STRING
#define AC_LIB_VECTOR
#define AC_LIB_INPUT

#include "ac_lib.h"

#include <stdio.h>

typedef struct Player {
    unsigned long long data_block[1 << 15];
} Player;

int main()
{
    // Init string library.
    ac_lib_init_string();

    // Init vector library.
    ac_lib_init_vector();

    // Init input library.
    ac_lib_init_input();

    /*
    // String testing.
    ac_string_t *src = ac_string.create("Testing works!\n");
    printf("%s\n", ac_string.get(src));
    ac_string.destructor();

    // Vector testing.
    ac_vector_t *v = ac_vector.create();
    int a = 10;
    ac_vector.push(v, &a);
    int *a_addr = ac_vector.get(v, 0);
    printf("Value of a: %d\n", *a_addr);
    ac_vector.pop(v);
    ac_vector.destructor();
    */

    // String+Vector testing
    ac_string_t *s_v = ac_string.create("Test string+vector");
    ac_vector_t *vec_s = ac_vector.create();
    ac_vector.push(vec_s, s_v);
    ac_string_t *s_v_addr = ac_vector.get(vec_s, 0);
    printf("s_v: %s\n", ac_string.get(s_v_addr));
    ac_string.destructor();
    ac_vector.destructor();
    ac_vector.destructor();

    /*
    // Input testing.
    ac_input_t *input = ac_input.create(0);
    ac_input_t *i2 = ac_input.create(0);
    ac_input_t *i3 = ac_input.create(0);
    ac_input.receive(input);
    const char *input_string = ac_input.get(input);
    printf("Input got: %s\n", input_string);

    ac_input.destructor();
    */
    return 0;
}
