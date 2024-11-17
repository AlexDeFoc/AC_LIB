#ifndef AC_LIB_STRING_MODULE
#define AC_LIB_STRING_MODULE

/* Dictionary:
'OOM': Out of memory.
*/

typedef struct ac_string_t {
    char *data;
    size_t lenght;
} ac_string_t;

typedef struct AC_STRING_CLASS {
    // Action: Creates string object.
    // Args type: const char *.
    // Args name: string_literal.
    // Returns: address to string object.
    ac_string_t * (*create) (const char *string_literal);

    // Action: Destroyes string object.
    // Args type: string object.
    // Mutates: string object.
    void (*destroy) (ac_string_t *object);

    // Action: Gets string literal from string object.
    // Args type: const string object.
    // Returns: string literal.
    const char * (*get) (const ac_string_t *object);

    // Action: Checks if match string object is present in string object.
    // Args type: string object, string object.
    // Args order: object, match.
    // Returns: 0 for 'found' | 1 for 'not found'.
    int (*match) (const ac_string_t *object, const ac_string_t *match);

    // Action: Changes text inside string object.
    // Args type: string object, const char *.
    // Args order: object, string literal.
    // Mutates: string object.
    void (*change) (ac_string_t *object, const char *string_literal);

    //// Tracker
    ac_string_t **tracked_list;
    size_t tracked_count;
    size_t tracked_limit;

    void (*destructor) (void);
} AC_STRING_CLASS;

extern AC_STRING_CLASS ac_string;

// Action: Makes ac_string functions available.
void ac_lib_init_string(void);

#endif
