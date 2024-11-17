#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ac_input.h"

#define AC_GOOD 0
#define AC_BAD 1

AC_INPUT_CLASS ac_input;

// Action: Creates input object.
// Args type: const size_t.
// Args name: limit.
// Returns: input object.
static ac_input_t * create (const size_t limit)
{
    // Alloc input object.
    ac_input_t *object = malloc(sizeof(ac_input_t));
    if (object == NULL) {
        printf("OOM: alloc input object!\n");
        return NULL;
    }

    // Initialize input object.
    object->data = NULL;
    object->lenght = 0;
    object->input_limit = 0;
    object->unlimited_input = 0;

    // Set unlimited input status.
    if (limit == 0) object ->unlimited_input = 1;

    // Set input limit based on input limit taken in.
    if (limit == 0) {
        object->input_limit = 100;
    }
    else if (limit > 0) {
        object->input_limit = limit;
    }

    // Allocate data_block.
    char *data_block = NULL;
    data_block = calloc(object->input_limit + 1, sizeof(char));
    if (data_block == NULL) {
        printf("OOM: alloc input object!\n");
        free(object);
        return NULL;
    }

    // Assign data block.
    object->data = data_block;

    // Enlarge track list if needed.
    if (ac_input.tracked_count + 1 >= ac_input.tracked_limit) {
        size_t tracked_new_limit = ac_input.tracked_limit * 2;

        ac_input_t **new_data_list = realloc(ac_input.tracked_list, tracked_new_limit * sizeof(ac_input_t *));
        if (new_data_list == NULL) {
            printf("OOM: resizing track list!\n");
            free(object);
            return NULL;
        }

        ac_input.tracked_list = new_data_list;
        ac_input.tracked_limit = tracked_new_limit;
    }

    // Add input object to list.
    ac_input.tracked_list[ac_input.tracked_count] = object;
    ac_input.tracked_count++;

    // Exit good.
    return object;
}

// Action: Destroys input object.
// Args type: input object.
// Mutates: input object.
static void destroy (ac_input_t *object)
{
    //Validate input object.
    if (object == NULL) {
        return;
    }

    // Destroy input object.
    object->lenght = 0;
    object->input_limit = 0;
    object->unlimited_input = 0;
    free(object->data);
    free(object);
    object = NULL;

    // Exit good.
    return;
}

// Action: Receives input from stdin.
// Args type: input object.
// Mutates: input object.
static void receive (ac_input_t *object)
{
    // Validate input object.
    if (object == NULL) {
        printf("Null input object!\n");
        return;
    }

    // Get input from stdin.
    int c;
    int received_amount = 0;
    while (1) {
        // Receive next char from stdin.
        c = getc(stdin);

        // Check if we got the end of the input.
        if (c == EOF || c == '\n') break;

        // Check if input is limited or not.
        if (object->unlimited_input == 1) {
            // Enlarge input data if needed. Double it.
            if (received_amount >= object->input_limit) {
                size_t new_limit = object->input_limit * 2;
                char *new_data_block = realloc(object->data, new_limit + 1);
                if (new_data_block == NULL) {
                    printf("OOM: resizing input object!\n");
                    return;
                }

                object->data = new_data_block;
                object->input_limit = new_limit;
            }

            // Add char to input object.
            object->data[received_amount] = c;
            received_amount++;
            object->lenght++;
        }
        else {
            // Exit upon limit reached.
            if (received_amount >= object->input_limit) break;

            // Add char to input object.
            object->data[received_amount] = c;
            received_amount++;
            object->lenght++;
        }
    }

    // Add null terminating char at end.
    object->data[object->lenght] = '\0';

    // Exit good.
    return;
}

// Action: Gets string literal from inside the input object.
// Args type: input object.
// Returns: string literal.
static const char *get (const ac_input_t *object)
{
    // Validate input object.
    if (input == NULL) {
        printf("Null input object!\n");
        return NULL;
    }

    // Return input object data.
    return (const char*)input->data;
}

// Action: Destorys then creates a new input object.
// Args type: input object.
// Mutates: input object.
static void reset (ac_input_t *object)
{
    // Validate input object.
    if (object == NULL) {
        printf("Null input object!\n");
        return;
    }

    // Store input_limit based on unlimited input status.
    size_t input_limit = 0;
    if (object->unlimited_input == 0) {
        input_limit = object->input_limit;
    }

    // Destroy and create input object.
    destroy(object);
    object = create(input_limit);

    // Exit good.
    return;
}

// Action: Calls destroy upon all items that were created.
static void destructor (void)
{
    // Validate track list.
    if (ac_input.tracked_list == NULL) return;

    // Loop.
    for (size_t i = 0; i < ac_input.tracked_count; i++) {
        if (ac_input.tracked_list[i] != NULL) {
            destroy(ac_input.tracked_list[i]);
        }
    }

    // Destroy track list.
    free(ac_input.tracked_list);
    ac_input.tracked_list= NULL;

    // Exit good.
    return;
}

// Action: Makes ac_string functions available.
void ac_lib_init_input(void)
{
    // Assign functions to ac_string class.
    ac_input.create = create;
    ac_input.destroy = destroy;
    ac_input.receive = receive;
    ac_input.get = get;
    ac_input.reset = reset;
    ac_input.destructor = destructor;

    // Init Tracker
    ac_input.tracked_count = 0;
    ac_input.tracked_limit = 4;
    ac_input_t **obj_list = malloc(ac_input.tracked_limit * sizeof(ac_input_t *));
    if (obj_list == NULL) {
        printf("OOM: alloc input list!\n");
        return;
    }

    ac_input.tracked_list = obj_list;

    // Exit good.
    return;
}
