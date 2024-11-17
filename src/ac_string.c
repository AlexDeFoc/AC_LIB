#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ac_string.h"

#define AC_GOOD 0
#define AC_BAD 1

AC_STRING_CLASS ac_string;

// Action: Creates string object on the heap.
// Argumens: string literal.
// Returns: address to string object.
static ac_string_t * create (const char *string_literal)
{ 
    // Check if we got null string literal.
    if (string_literal == NULL) {
        printf("No string provided!\n");
        return NULL;
    }
    // Check if size is lower or equal to zero.
    size_t read_lenght = strlen(string_literal);
    if (read_lenght <= 0) {
        printf("No string provided!\n");
        return NULL;
    }

    // Allocate memory for string object.
    ac_string_t *object = malloc(sizeof(ac_string_t));
    if (object == NULL) {
        printf("Not enough memory for creating string object!\n");
        return NULL;
    }

    // Initializing string object.
    object->data = NULL;
    object->lenght = read_lenght;

    // Allocate size for string literal.
    char *data_block = malloc((read_lenght + 1) * sizeof(char));
    if (data_block == NULL) {
        printf("String too long!\n");
        return NULL;
    }
    object->data = data_block;

    // Copy each letter into string object.
    for (int i = 0; i < read_lenght; ++i) {
        object->data[i] = string_literal[i];
    }
    object->data[read_lenght] = '\0';

    // Track input object in class object list;
    // Enlarge list if needed.
    if (ac_string.tracked_objects_amount + 1 >= ac_string.tracking_objects_limit) {
        ac_string_t **new_data_list = realloc(ac_string.tracked_objects_list, ac_string.tracking_objects_limit * 2 * sizeof(ac_string_t *));
        if (new_data_list == NULL) {
            printf("Not enough memory to widen tracking objects list!\n");
            return NULL;
        }

        ac_string.tracked_objects_list = new_data_list;
        ac_string.tracking_objects_limit *= 2;
    }

    // Add input object to list.
    ac_string.tracked_objects_list[ac_string.tracked_objects_amount] = object;
    ac_string.tracked_objects_amount++;

    // Exit good.
    return object;
}

// Action: Frees and sets to null string object.
// Arguments: string object.
// Mutation: string object.
static void destroy (ac_string_t *object)
{
    // Validate string object.
    if (object ->lenght == 0) {
        printf("No string found to destroy!\n");
        return;
    }

    // Destroy string object.
    object->lenght = 0;
    free(object->data);
    object->data = NULL;
}

// Action: Gets address of string literal from inside string object.
// Arguments: const string object.
// Returns: address to const string literal.
const char * get (const ac_string_t *object)
{
    // Validate string object.
    if (object == NULL) {
        printf("No string object provided!\n");
        return NULL;
    }
    if (object ->lenght == 0) {
        printf("String object is empty!\n");
        return NULL; 
    }

    // Return string literal from string object.
    return (const char *)(object->data);
}

// Action: Used in match function. Ran when match func received string longer then 1 char.
int match_multiple_char_string (const ac_string_t *object, const ac_string_t *match)
{
    // Validate text & match strings.
    if (match->lenght <= 0) {
        printf("No matching string provided!\n");
        return AC_BAD;
    }
    if (object->lenght <= 0) {
        printf("No text provided!\n");
        return AC_BAD;
    }
    if (match->lenght > object->lenght) {
        printf("Match string longer text!\n");
        return AC_BAD;
    }
    if (match->lenght == 1) {
        printf("Match string not supported!\n");
        return AC_BAD;
    }

    
    // Find edge instances found.
    int match_end_index = match->lenght - 1;
    int ends_found_count = 0;
    for (int i = 0; i < object->lenght; i++) {
        if (object->data[i] == match->data[match_end_index]) {
            ends_found_count++;
        }
    }
    // Exit if no ends found.
    if (ends_found_count == 0) return AC_BAD;


    // Store indexes of ends found.
    int *ends_index = calloc(ends_found_count, sizeof(int));
    if (ends_index == NULL) {
        printf("Not enough memory for storing ends indexes!\n");
        return AC_BAD;
    }
    int dummy_index = 0;
    for (int i = 0; i < object->lenght; i++) {
        if (object->data[i] == match->data[match_end_index]) {
            ends_index[dummy_index] = i;
            dummy_index++;
        }
    }

    // Check if start is matching based on end.
    int found_start_index = -1;
    for (int i = 0; i < ends_found_count; i++) {
        int start_edge = object->lenght - match->lenght - ends_index[i] - 1;
        if (object->data[start_edge] == match->data[0]) {
            found_start_index = start_edge;
            break;
        }
    }
    // Exit if start not found.
    if (found_start_index == -1) return AC_BAD;


    // Check each char between ends.
    for (int i = 0; i < match->lenght; i++) {
        if (object->data[found_start_index + i] != match->data[i]) return AC_BAD;
    }

    // Exit good.
    free(ends_index);
    return AC_GOOD;
}

// Action: Used in match function. Ran when match func received string 1 char long.
int match_single_char_string (const ac_string_t *object, const ac_string_t *match)
{
    // Validate text & match strings.
    if (match->lenght <= 0) {
        printf("No matching string provided!\n");
        return AC_BAD;
    }
    if (object->lenght <= 0) {
        printf("No text provided!\n");
        return AC_BAD;
    }
    if (match->lenght > 1) {
        printf("Match string longer then supported!\n");
        return AC_BAD;
    }

    // Find char in text.
    char matching_char = match->data[0];
    for (int i = 0; i < object->lenght; i++) {
        if (object->data[i] == matching_char) {
            return AC_GOOD;
        }
    }

    // Exit bad. We haven't found match in object.
    return AC_BAD;
}

// Action: Checks if match string object is present in text string object.
// Arguments: 2 string objects.
// Args order: [object, match].
// Returns: 0 for 'found' | 1 for 'not found'.
static int match (const ac_string_t *object, const ac_string_t *match)
{
    int result = -1;

    // Redirect to correct function based on match string object lenght.
    if (match->lenght > 1) {
        result = match_multiple_char_string(object, match);
    } else {
        result = match_single_char_string(object, match);
    }

    // Return result.
    return result;
}

// Action: Changes text inside string object.
// Arguments: string object, string literal.
// Args order: [object, literal]
// Mutation: string object.
static void change (ac_string_t *object, const char *string_literal)
{
    // Validate string object, string literal.
    if (object->lenght <= 0) {
        printf("No matching string provided!\n");
        return;
    }
    if (string_literal == NULL) {
        printf("No text provided!\n");
        return;
    }
    size_t text_len = strlen(string_literal);
    if (text_len <= 0) {
        printf("No text provided!\n");
        return;
    }

    // Allocate new data block for string literal, free previous block, assign.
    char *new_block = malloc(text_len * sizeof(char));
    if (new_block == NULL) {
        printf("No memory for changing string contents!\n");
        return;
    }
    free(object->data);
    object->data = new_block;

    // Exit good.
    return;
}

// Action: Calls destroy function for each tracked (created) object that isnt already destroyed.
static void destructor (void)
{
    // Loop through each created object and call destroy on it.
    for (size_t i = 0; i < ac_string.tracked_objects_amount; i++) {
        if (ac_string.tracked_objects_list[i] != NULL) {
            destroy(ac_string.tracked_objects_list[i]);
        }
    }

    // Destroy objects list.
    free(ac_string.tracked_objects_list);

    // Exit good.
    return;
}

// Action: Makes ac_string functions available.
void ac_lib_init_string(void)
{
    // Assign functions to ac_string class.
    ac_string.create = create;
    ac_string.destroy = destroy;
    ac_string.get = get;
    ac_string.match = match;
    ac_string.destructor = destructor;

    // Initialize values and allocate memory for ac_string class.
    ac_string.tracked_objects_amount = 0;
    ac_string.tracking_objects_limit = 4;
    ac_string_t **data_list = malloc(ac_string.tracking_objects_limit * sizeof(ac_string_t *));
    if (data_list == NULL) {
        printf("Not enough memory for creating tracking objects list!\n");
        return;
    }
    ac_string.tracked_objects_list = data_list;

    // Exit good.
    return;
}
