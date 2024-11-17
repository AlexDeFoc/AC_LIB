#ifndef AC_LIB_VECTOR_MODULE
#define AC_LIB_VECTOR_MODULE

typedef struct ac_vector_t {
    size_t item_data_size;
    size_t item_count;
    void * data;
} ac_vector_t;

typedef struct AC_VECTOR_CLASS {
    // Action: Creates vector object.
    // Arguments: Takes in "size_t" primitive.
    // Desc: The primitive represents the size of each item in bits. Indended use with sizeof().
    // Warning: Unexpected behaviour if negative value provided. Expected behaviour: underflows.
    // Returns: vector object.
    ac_vector_t (*create)(size_t item_data_size);

    // Action: Pushes data into vector object.
    // Arguments: Takes in vector, "const void *" primitive.
    // Desc: The primitive represents the "data" that will be pushed into the vector.
    // Changes: Doesn't modify the data taken in.
    // Changes: Modifies the vector object.
    void (*push) (ac_vector_t *vector, const void *data);

    // Action: Returns the address for the item in the vector at index.
    // Arguments: Takes in vector object, "const int" primititve.
    // Desc: The primitive represents the index. Vector is zero-indexed.
    // Changes: Neither arguments taken in are modified.
    void *(*get) (const ac_vector_t *vector, const int index);

    // Action: Changes item data at index.
    // Arguments: Takes in vector object, "const int" primitive, "const void *" primitive.
    // Desc: The "const int" primitive represents the index of the item to modify.
    // Desc: The "const void *" primitive represents the new data to be inserted into the item.
    // Changes: Doesn't modify either the index or new data taken in.
    // Changes: Modifies the vector object.
    void (*change) (ac_vector_t *vector, const int index, const void *new_data);

    // Action: Removes the last item in the vector.
    // Arguments: Takes in vector object.
    // Changes: Modifies the vector object.
    void (*pop) (ac_vector_t *vector);

    // Action: Frees all memory inside it and nulls the addresses.
    // Arguments: Takes in vector object.
    // Changes: Modifies the vector object.
    void (*destroy) (ac_vector_t *vector);
} AC_VECTOR_CLASS;

extern AC_VECTOR_CLASS ac_vector;

// Action: Makes ac_vector functions available.
void ac_lib_init_vector(void);

#endif
