#define AC_LIB_STRING
#define AC_LIB_VECTOR

#include <ac_lib.h>

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

    // String testing.
    ac_string_t src = ac_string.create("Testing works!\n");
    printf("%s\n", ac_string.get(&src));
    ac_string.destroy(&src);

    // Vector testing.
    ac_vector_t vec = ac_vector.create(sizeof(int));
    printf("Vec item data size: %zu\n", vec.item_data_size);

    int a = 2;
    ac_vector.push(&vec, &a);
    int *a_addr = ac_vector.get(&vec, 0);
    printf("a value: %d\n", *a_addr);

    int b = 200000;
    ac_vector.push(&vec, &b);
    int *b_addr = ac_vector.get(&vec, 1);

    int b_val = 100;
    ac_vector.change(&vec, 1, &b_val);
    printf("b value: %d\n", *b_addr);

    printf("vec size before pop: %zu\n", vec.item_count);
    ac_vector.pop(&vec);
    printf("vec size after pop: %zu\n", vec.item_count);

    ac_vector.destroy(&vec);

    ac_vector_t vec2 = ac_vector.create(sizeof(Player));
    printf("Data size of item in vec2: %zu\n", vec2.item_data_size);

    /* Heavy test */
    /*
    Player p;
    ac_vector.push(&vec2, &p);
    */

    ac_vector.destroy(&vec2);

    ac_vector_t vec3 = ac_vector.create(-2);
    printf("Data size of item in vec3: %zu\n", vec3.item_data_size);

    return 0;
}
