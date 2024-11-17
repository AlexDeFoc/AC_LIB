#ifndef AC_LIB_INPUT_MODULE
#define AC_LIB_INPUT_MODULE

#include <stdint.h>

typedef struct ac_input_t {
    char *data;
    size_t lenght;
    size_t input_limit;
    uint8_t unlimited_input;
} ac_input_t;

typedef struct AC_INPUT_CLASS {
    // Action: Creates input object.
    // Args type: const size_t.
    // Args name: limit.
    // Returns: input object.
    ac_input_t * (*create) (const size_t limit);

    // Action: Destroys input object.
    // Args type: input object.
    // Mutates: input object.
    void (*destroy) (ac_input_t *object);

    // Action: Receives input from stdin.
    // Args type: input object.
    // Mutates: input object.
    void (*receive) (ac_input_t *object);

    // Action: Gets string literal from inside the input object.
    // Args type: input object.
    // Returns: string literal.
    const char *(*get) (const ac_input_t *object);

    // Action: Destorys then creates a new input object.
    // Args type: input object.
    // Mutates: input object.
    void (*reset) (ac_input_t *object);

    //// Tracker
    ac_input_t **tracked_list;
    size_t tracked_count;
    size_t tracked_limit;

    void (*destructor) (void);
} AC_INPUT_CLASS;

extern AC_INPUT_CLASS ac_input;

// Action: Makes ac_input functions available.
void ac_lib_init_input(void);

#endif
