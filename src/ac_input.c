#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ac_input.h"

#define AC_GOOD 0
#define AC_BAD 1

AC_INPUT_CLASS ac_input;

// Action: Creates input object.
// Arguments: Takes in "const size_t" primitive.
// Desc: The primitive represents the input limit.
// Desc: The input limit can be 0 or over 0. If given 0 then it means there is not limit.
// Warning: Size_t is an unsigned type meaning if a negative value is given it underflows.
// Changes: The primitive is not modified.
// Returns: address to input object.
static ac_input_t *create (const size_t input_limit)
{
    // Init empty object on the heap.
    ac_input_t *input = malloc(sizeof(ac_input_t));
    if (input == NULL) {
        printf("Not enough memory for creating input object!\n");
        return NULL;
    }

    // Initialize empty input object.
    input->data = NULL;
    input->lenght = 0;
    input->input_limit = 0;
    input->unlimited_input = 0;

    // Validate arguments.
    if (input_limit < 0) {
        printf("Invalid input limit!\n");
        return input;
    }

    // Set unlimited input status.
    if (input_limit == 0) input->unlimited_input = 1;

    // Set input limit based on input limit taken in.
    if (input_limit == 0) {
        input->input_limit = 100;
    }
    else if (input_limit > 0) {
        input->input_limit = input_limit;
    }

    // Allocate data_block.
    char *data_block = NULL;
    data_block = calloc(input->input_limit + 1, sizeof(char));
    if (data_block == NULL) {
        printf("Not enough memory for allocating space for input object!\n");
        return input;
    }

    // Assign data block.
    input->data = data_block;

    // Track input object in class object list;
    // Enlarge list if needed.
    if (ac_input.tracked_objects_amount + 1 >= ac_input.tracking_objects_limit) {
        ac_input_t **new_data_list = realloc(ac_input.tracked_objects_list, ac_input.tracking_objects_limit * 2 * sizeof(ac_input_t *));
        if (new_data_list == NULL) {
            printf("Not enough memory to widen tracking objects list!\n");
            return input;
        }

        ac_input.tracked_objects_list = new_data_list;
        ac_input.tracking_objects_limit *= 2;
    }

    // Add input object to list.
    ac_input.tracked_objects_list[ac_input.tracked_objects_amount] = input;
    ac_input.tracked_objects_amount++;

    // Exit good.
    return input;
}

// Action: Destroys input object.
// Arguments: Takes in input object.
// Changes: Modifies the input object taken in.
static void destroy (ac_input_t *input)
{
    //Validate input object.
    if (input == NULL) {
        printf("No input object provided!\n");
        return;
    }
    if (input->data == NULL) {
        return;
    }

    // Destroy input object.
    input->lenght = 0;
    input->input_limit = 0;
    input->unlimited_input = 0;
    free(input->data);
    input->data = NULL;
    free(input);
    input = NULL;

    // Exit good.
    return;
}

// Action: Starts receiving input from stdin until a certain limit or until end of line found.
// Arguments: Takes in input object.
// Changes: Modifies the input object taken in.
static void receive (ac_input_t *input)
{
    // Validate input object.
    if (input == NULL) {
        printf("No input object provided!\n");
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
        if (input->unlimited_input == 1) {
            // Widen input data block if we need. Double the input_limit.
            if (received_amount >= input->input_limit) {
                char *new_data_block = realloc(input->data, (input->input_limit * 2) + 1);
                if (new_data_block == NULL) {
                    printf("Not enough memory to widen the input data block!\n");
                    return;
                }

                input->data = new_data_block;
                input->input_limit *= 2;
            }

            // Add char to input object.
            input->data[received_amount] = c;
            received_amount++;
            input->lenght++;
        }
        else {
            // Exit upon limit reached.
            if (received_amount >= input->input_limit) break;

            // Add char to input object.
            input->data[received_amount] = c;
            received_amount++;
            input->lenght++;
        }
    }

    // Add null terminating char at end.
    input->data[input->lenght] = '\0';

    // Exit good.
    return;
}

// Action: Gets the input contents from the input object.
// Arguments: Takes in input object.
// Changes: Doesn't change the input object taken in.
// Returns: address to string literal inside input object.
static const char *get (const ac_input_t *input)
{
    char *input_contents = NULL;

    // Validate input object.
    if (input == NULL) {
        printf("No input object provided!\n");
        return input_contents;
    }
    if (input->data == NULL) {
        printf("Empty input object provided!\n");
        return input_contents;
    }

    // Get input contents from input object.
    input_contents = input->data;

    // Exit good.
    return (const char*) input_contents;
}

// Action: Resets input object. It calls destory then create without having to reenter the input limit.
// Arguments: Takes in input object.
// Changes: Modifies the input object.
static void reset (ac_input_t *input)
{
    // Validate input object.
    if (input == NULL) {
        printf("No input object provided!\n");
        return;
    }
    if (input->data == NULL) {
        printf("Empty input object provided!\n");
        return;
    }

    // Store input_limit based on unlimited input status.
    size_t input_limit = 0;
    if (input->unlimited_input == 0) {
        input_limit = input->input_limit;
    }

    // Destroy and create input object.
    destroy(input);
    input = create(input_limit);

    // Exit good.
    return;
}

// Action: Calls destroy function for each tracked (created) object that isnt already destroyed.
static void destructor (void)
{
    for (size_t i = 0; i < ac_input.tracked_objects_amount; i++) {
        if (ac_input.tracked_objects_list[i] != NULL) {
            destroy(ac_input.tracked_objects_list[i]);
        }
    }

    free(ac_input.tracked_objects_list);

    return;
}

// Action: Makes ac_input functions available.
void ac_lib_init_input(void)
{
    // Assign functions to ac_input class.
    ac_input.create = create;
    ac_input.destroy = destroy;
    ac_input.receive = receive;
    ac_input.get = get;
    ac_input.reset = reset;
    ac_input.destructor = destructor;

    // Initialize values and allocate memory for ac_input class.
    ac_input.tracked_objects_amount = 0;
    ac_input.tracking_objects_limit = 4;
    ac_input_t **data_list = malloc(ac_input.tracking_objects_limit * sizeof(ac_input_t *));
    if (data_list == NULL) {
        printf("Not enough memory for creating tracking objects list!\n");
        return;
    }
    ac_input.tracked_objects_list = data_list;

    return;
}
