#ifndef AC_LIB_STRING_MODULE
#define AC_LIB_STRING_MODULE

typedef struct ac_string_t {
    char *data;
    size_t lenght;
} ac_string_t;

typedef struct AC_STRING_CLASS {
    //// Functions for ac_string_t object.
    // Action: Creates string object on the heap.
    // Argumens: string literal.
    // Returns: address to string object.
    ac_string_t * (*create) (const char *string_literal);

    // Action: Frees and sets to null string object.
    // Arguments: string object.
    // Mutation: string object.
    void (*destroy) (ac_string_t *object);

    // Action: Gets address of string literal from inside string object.
    // Arguments: const string object.
    // Returns: address to const string literal.
    const char * (*get) (const ac_string_t *object);

    // Action: Checks if match string object is present in text string object.
    // Arguments: 2 string objects.
    // Args order: [object, match].
    // Returns: 0 for 'found' | 1 for 'not found'.
    int (*match) (const ac_string_t *object, const ac_string_t *match);

    // Action: Changes text inside string object.
    // Arguments: string object, string literal.
    // Args order: [object, literal]
    // Mutation: string object.
    void (*change) (ac_string_t *object, const char *string_literal);

    //// Tracking created objects.
    ac_string_t **tracked_list;
    size_t tracked_count;
    size_t tracked_limit;

    // Action: Calls destroy function for each tracked (created) object that isnt already destroyed.
    void (*destructor) (void);
} AC_STRING_CLASS;

extern AC_STRING_CLASS ac_string;

// Action: Makes ac_string functions available.
void ac_lib_init_string(void);

#endif
