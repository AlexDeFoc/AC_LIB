#include "ac_vector.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define AC_GOOD 0
#define AC_BAD 1

AC_VECTOR_CLASS ac_vector;

// Action: Creates vector object.
// Arguments: Takes in "size_t" primitive.
// Desc: The primitive represents the size of each item in bits. Indended use with sizeof().
// Warning: Unexpected behaviour if negative value provided. Expected behaviour: underflows.
// Returns: vector object.
static ac_vector_t create (size_t item_data_size)
{
    // Initialize empty vector.
    ac_vector_t vector = {
        .item_data_size = 0,
        .item_count = 0,
        .data = NULL
    };

    // Check if good item data size provided.
    if (item_data_size == 0) {
        printf("Invalid item data size!\n");
        return vector;
    }

    // Return vector.
    vector.item_data_size = item_data_size;
    return vector;
}

// Action: Pushes data into vector object.
// Arguments: Takes in vector, "const void *" primitive.
// Desc: The primitive represents the "data" that will be pushed into the vector.
// Changes: Doesn't modify the data taken in.
// Changes: Modifies the vector object.
static void push (ac_vector_t *vector, const void *data)
{
    // Validate vector & data.
    if (data == NULL) {
        printf("No item provided!\n");
        return;
    }

    // Check if we are adding the first item or a new one.
    if (vector->item_count == 0) {
        // We are adding the first item.
        void *data_block = calloc(1, vector->item_data_size);
        if (data_block == NULL) {
            printf("Not enough memory for adding item!\n");
            return;
        }

        vector->data = data_block;
        vector->item_count = vector->item_count + 1;
        memcpy(vector->data, data, vector->item_data_size);
    }
    else {
        // We are adding another item on top of the others.
        void *data_block = realloc(vector->data, (vector->item_count + 1) * vector->item_data_size);
        if (data_block == NULL) {
            printf("Not enough memory for adding item!\n");
            return;
        }

        vector->data = data_block;
        memcpy((char *)vector->data + (vector->item_count * vector->item_data_size), data, vector->item_data_size);
        vector->item_count = vector->item_count + 1;
    }

    return;
}

// Action: Returns the address for the item in the vector at index.
// Arguments: Takes in vector object, "const int" primititve.
// Desc: The primitive represents the index. Vector is zero-indexed.
// Changes: Neither arguments taken in are modified.
static void * get(const ac_vector_t *vector, const int index)
{
    // Initialize empty item address.
    void *item = NULL;

    // Valid vector & index.
    if (vector == NULL) {
        printf("No vector provided!\n");
        return NULL;
    }
    if (vector->data == NULL) {
        printf("Empty vector provided!\n");
        return NULL;
    }
    if (index < 0) {
        printf("Invalid index provided!\n");
        return NULL;
    }
    if (index >= vector->item_count) {
        printf("Index out of range!\n");
        return NULL;
    }

    // Get item from vector.
    item = (char *)vector->data + (index * vector->item_data_size);

    return item;
}

// Action: Changes item data at index.
// Arguments: Takes in vector object, "const int" primitive, "const void *" primitive.
// Desc: The "const int" primitive represents the index of the item to modify.
// Desc: The "const void *" primitive represents the new data to be inserted into the item.
// Changes: Doesn't modify either the index or new data taken in.
// Changes: Modifies the vector object.
static void change (ac_vector_t *vector, const int index, const void *new_data)
{
    // Validate vector & new_data & index.
    if (vector == NULL) {
        printf("No vector provided!\n");
        return;
    }
    if (vector->data == NULL) {
        printf("Empty vector provided!\n");
        return;
    }
    if (index < 0) {
        printf("Invalid index provided!\n");
        return;
    }
    if (index >= vector->item_count) {
        printf("Index out of range!\n");
        return;
    }
    if (new_data == NULL) {
        printf("No new item provided!\n");
        return;
    }

    // Get item address which we'll modify it's data.
    void *item = get(vector, index);

    // Change old_item to new_item.
    memcpy((char *)vector->data + (index * vector->item_data_size), new_data, vector->item_data_size);

    return;
}

// Action: Removes the last item in the vector.
// Arguments: Takes in vector object.
// Changes: Modifies the vector object.
static void pop (ac_vector_t *vector)
{
    // Validate vector object.
    if (vector == NULL) {
        printf("No vector provided!\n");
        return;
    }
    if (vector->item_count == 0) {
        printf("Empty vector provided!\n");
        return;
    }

    // Shorten vector data block.
    void *new_block = realloc(vector->data, (vector->item_count - 1) * vector->item_data_size);
    if (new_block == NULL) {
        printf("Not enough memory for poping out the last item!\n");
        return;
    }

    // Assign shorter data block;
    vector->data = new_block;
    vector->item_count = vector->item_count - 1;

    return;
}

// Action: Frees all memory inside it and nulls the addresses.
// Arguments: Takes in vector object.
// Changes: Modifies the vector object.
static void destroy (ac_vector_t *vector)
{
    // Validate vector object.
    if (vector == NULL) {
        printf("No vector provided!\n");
        return;
    }
    if (vector->data == NULL) {
        printf("Vector already null!\n");
        return;
    }

    // Destroy vector object.
    free(vector->data);
    vector->item_count = 0;
    vector->item_data_size = 0;

    return;
}

// Action: Makes ac_vector functions available.
void ac_lib_init_vector(void)
{
    ac_vector.create = create;
    ac_vector.push = push;
    ac_vector.get = get;
    ac_vector.change = change;
    ac_vector.pop = pop;
    ac_vector.destroy = destroy;
    return;
}
