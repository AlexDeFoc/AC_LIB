#ifndef AC_LIB_STRING_MODULE
#define AC_LIB_STRING_MODULE
#include <stdint.h>

typedef struct ac_string_t {
    char *data;
    size_t lenght;
} ac_string_t;

typedef struct AC_STRING_CLASS {
    // Takes in a "char *" aka a "string literal".
    // Outputs ac_string_t object.
    ac_string_t (*create)(const char *text);


    // Takes in a "ac_string_t" object.
    // Clears, frees it and destroys it.
    void (*destroy)(ac_string_t *string);


    // Takes in a "ac_string_t" object.
    // Doesn't modify the object.
    // Returns "const char *" aka "const string literal".
    const char* (*get)(const ac_string_t *string);

    // Takes in two "const ac_string_t" object.
    // Doesn't modify either object.
    // Returns 0 for 'found' | 1 for 'not found'.
    int (*match)(const ac_string_t *string, const ac_string_t *match);

    // Takes in a "ac_string_t" object, "const char *" aka a "cosnt string literal".
    // Doesn't modify the "const char *" primitive.
    // Modifies the "ac_string_t" object.
    void (*change)(ac_string_t *string, const char *text);
} AC_STRING_CLASS;

extern AC_STRING_CLASS ac_string;

void init_AC_STRING_CLASS(void);

#endif
