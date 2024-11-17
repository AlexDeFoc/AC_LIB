#include "ac_vector.h"

#include <stdlib.h>
#include <stdio.h>

AC_VECTOR_CLASS ac_vector;

#define AC_GOOD 0
#define AC_BAD 1

/* Dictionary:
'OOM': Out of memory.
'OOB': Out of bounds.
*/

// Action: Creates vector.
// Returns: address to vector.
static ac_vector_t * create (void)
{
    // Alloc vector object.
    ac_vector_t *object = malloc(sizeof(ac_vector_t));
    if (object == NULL) {
        printf("OOM: alloc vector object!\n");
        return NULL;
    }

    // Init & alloc vector items.
    object->item_limit = 4;
    object->item_count = 0;
    object->item_data = malloc(object->item_limit * sizeof(void *));
    if (object->item_data == NULL) {
        printf("OOM: alloc vector items!\n");
        free(object);
        return NULL;
    }

    // Enlarge track list if needed.
    if (ac_vector.tracked_count + 1 >= ac_vector.tracked_limit) {
        size_t tracked_new_limit = ac_vector.tracked_limit * 2;

        ac_vector_t **new_data_list = realloc(ac_vector.tracked_list, tracked_new_limit * sizeof(ac_vector_t *));
        if (new_data_list == NULL) {
            printf("OOM: resizing track list!\n");
            free(object);
            return NULL;
        }

        ac_vector.tracked_list = new_data_list;
        ac_vector.tracked_limit = tracked_new_limit;
    }

    // Add vector to list.
    ac_vector.tracked_list[ac_vector.tracked_count] = object;
    ac_vector.tracked_count++;

    // Exit good.
    return object;
}

// Action: Destroys object.
// Args type: vector.
// Mutates: vector.
static void destroy (ac_vector_t *object)
{
    // Validate vector.
    if (object == NULL) {
        return;
    }

    // Destroy vector.
    free(object->item_data);
    object->item_count = 0;
    object->item_limit = 0;
    free(object);

    // Exit good.
    return;
}

// Action: Adds address at end of vector.
// Args type: vector, const void *.
// Args order: object, address.
// Mutates: vector.
static void push (ac_vector_t *object, const void *address)
{
    // Validate vector.
    if (object == NULL) {
        printf("Null vector object!\n");
        return;
    }

    // Resize vector if needed.
    if (object->item_count >= object->item_limit) {
        object->item_limit *= 2;
        void **new_data = realloc(object->item_data, object->item_limit * sizeof(void *));
        if (new_data == NULL) {
            printf("OOM: resizing vector object!\n");
            free(object->item_data);
            return;
        }
        object->item_data = new_data;
    }

    // Add address.
    object->item_data[object->item_count] = (void *)address;
    object->item_count++;

    // Exit good.
    return;
}

// Action: Removes last address in the vector.
// Args type: vector.
// Mutates: vector.
static void pop (ac_vector_t *object)
{
    // Validate vector & vector item count over 0.
    if (object == NULL) {
        printf("Null vector object!\n");
        return;
    }
    if (object->item_count <= 0) {
        printf("Empty vector object!\n");
        return;
    }

    // Clear the last item.
    object->item_data[object->item_count - 1] = NULL;

    // Decrement item count.
    object->item_count--;

    //Resize when the count is less than a quarter of the limit.
    if (object->item_count < object->item_limit / 4) {
        size_t new_limit = object->item_limit / 2;
        void **new_data = realloc(object->item_data, new_limit * sizeof(void *));
        if (new_data != NULL) {
            object->item_data = new_data;
            object->item_limit = new_limit;
        }
    }

    // Exit good.
    return;
}

// Action: Gets the address at index from inside the vector.
// Args type: const vector, const size_t.
// Args order: object, index.
// Returns: void *.
static void * get (const ac_vector_t *object, const size_t index)
{
    // Validate vector & index.
    if (object == NULL) {
        printf("Null vector object!\n");
        return NULL;
    }
    if (index >= object->item_count) {
        printf("OOB: invalid index!\n");
        return NULL;
    }

    // Return address at index.
    return object->item_data[index];
}

// Action: Changes the address at index from inside the vector.
// Args type: vector, const size_t, const void *.
// Args order: object, index, address.
// Mutates: vector.
static void change (ac_vector_t *object, const size_t index, const void *address)
{
    // Validate vector, index & address.
    if (object == NULL) {
        printf("Null vector object!\n");
        return;
    }
    if (index >= object->item_count) {
        printf("OOB: invalid index!\n");
        return;
    }
    if (address == NULL) {
        printf("Null data address!\n");
        return;
    }

    // Modify address at index inside vector.
    object->item_data[index] = (void *)address;

    // Exit good.
    return;
}

// Action: Calls destroy upon all items that were created.
static void destructor (void)
{
    // Validate track list.
    if (ac_vector.tracked_list == NULL) return;

    // Loop.
    for (size_t i = 0; i < ac_vector.tracked_count; i++) {
        if (ac_vector.tracked_list[i] != NULL) {
            destroy(ac_vector.tracked_list[i]);
        }
    }

    // Destroy track list.
    free(ac_vector.tracked_list);
    ac_vector.tracked_list= NULL;

    // Exit good.
    return;
}

// Action: Makes ac_vector functions available.
void ac_lib_init_vector(void)
{
    // Assign functions to ac_vector class.
    ac_vector.create = create;
    ac_vector.destroy = destroy;
    ac_vector.push = push;
    ac_vector.pop = pop;
    ac_vector.get = get;
    ac_vector.change = change;
    ac_vector.destructor = destructor;

    // Init Tracker
    ac_vector.tracked_count = 0;
    ac_vector.tracked_limit = 4;
    ac_vector_t **obj_list = malloc(ac_vector.tracked_limit * sizeof(ac_vector_t *));
    if (obj_list == NULL) {
        printf("OOM: alloc vector list!\n");
        return;
    }

    ac_vector.tracked_list = obj_list;

    // Exit good.
    return;
}
