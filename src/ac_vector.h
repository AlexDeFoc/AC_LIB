#ifndef AC_LIB_VECTOR_MODULE
#define AC_LIB_VECTOR_MODULE

typedef struct ac_vector_t {
    void ** item_data;
    size_t item_count;
    size_t item_limit;
} ac_vector_t;

typedef struct AC_VECTOR_CLASS {
    // Action: Creates vector.
    // Returns: address to vector.
    ac_vector_t * (*create) (void);

    // Action: Destroys object.
    // Args type: vector.
    // Mutates: vector.
    void (*destroy) (ac_vector_t *object);

    // Action: Adds address at end of vector.
    // Args type: vector, const void *.
    // Args order: object, address.
    // Mutates: vector.
    void (*push) (ac_vector_t *object, const void *address);

    // Action: Removes last address in the vector.
    // Args type: vector.
    // Mutates: vector.
    void (*pop) (ac_vector_t *object);

    // Action: Gets the address at index from inside the vector.
    // Args type: const vector, const size_t.
    // Args order: object, index.
    // Returns: void *.
    void * (*get) (const ac_vector_t *object, const size_t index);

    // Action: Changes the address at index from inside the vector.
    // Args type: vector, const size_t, const void *.
    // Args order: object, index, address.
    // Mutates: vector.
    void (*change) (ac_vector_t *object, const size_t index, const void *address);

    //// Tracker
    ac_vector_t **tracked_list;
    size_t tracked_count;
    size_t tracked_limit;

    void (*destructor) (void);
} AC_VECTOR_CLASS;

extern AC_VECTOR_CLASS ac_vector;

// Action: Makes ac_vector functions available.
void ac_lib_init_vector(void);

#endif
