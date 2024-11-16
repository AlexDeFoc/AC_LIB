#define AC_LIB_STRING

#include <ac_lib.h>

#include <stdio.h>

int main()
{
    ac_string_t src = ac_string.create("Testing works!\n");
    printf("%s\n", ac_string.get(&src));
    ac_string.destroy(&src);
    return 0;
}
