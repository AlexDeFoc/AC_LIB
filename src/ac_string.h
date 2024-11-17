#ifndef AC_LIB_STRING_MODULE
#define AC_LIB_STRING_MODULE
#include <stdint.h>

typedef struct ac_string_t {
    char *data;
    size_t lenght;
} ac_string_t;

typedef struct AC_STRING_CLASS {
    // Action: Creates string object.
    // Arguments: Takes in a const string literal.
    // Changes: Doesn't modify the string literal taken in.
    // Returns: string object.
    ac_string_t (*create)(const char *text);

    // Action: Destroys & frees the string object.
    // Arguments: Takes in string object.
    // Changes: modifies the string object.
    void (*destroy)(ac_string_t *string);

    // Action: Gets the address of the string.
    // Arguments: Takes in string object.
    // Changes: Doesn't modify the string object.
    // Returns: address to const string literal.
    const char* (*get)(const ac_string_t *string);

    // Action: Checks if the match object is present in the string object.
    // Arguments: Takes in two string objects.
    // Changes: Doesn't change either string object.
    // Returns: 0 for 'found' | 1 for 'not found'.
    int (*match)(const ac_string_t *string, const ac_string_t *match);

    // Action: Changes the text inside the string object.
    // Arguments: Takes in const string literal.
    // Changes: Doesn't modify the string literal taken in.
    // Changes: Modifies the string object.
    void (*change)(ac_string_t *string, const char *text);
} AC_STRING_CLASS;

extern AC_STRING_CLASS ac_string;

void init_AC_STRING_CLASS(void);

#endif
