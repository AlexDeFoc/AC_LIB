#include "ac_string.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

AC_STRING_CLASS ac_string;

#define AC_GOOD 0
#define AC_BAD 1

// Action: Creates string object.
// Args type: const char *. [string literal].
// Returns: address to string object.
static ac_string_t * create (const char *string_literal)
{ 
    // Check if we got null string literal.
    if (string_literal == NULL) {
        printf("Null string literal!\n");
        return NULL;
    }

    // Check if string literal size is lower or equal to zero.
    size_t read_lenght = strlen(string_literal);
    if (read_lenght <= 0) {
        printf("No string provided!\n");
        return NULL;
    }

    // Allocate memory for string object.
    ac_string_t *object = malloc(sizeof(ac_string_t));
    if (object == NULL) {
        printf("OOM: alloc string object!\n");
        return NULL;
    }

    // Initializing string object.
    object->data = NULL;
    object->lenght = read_lenght;

    // Allocate size for string literal.
    char *data_block = malloc((read_lenght + 1) * sizeof(char));
    if (data_block == NULL) {
        printf("String literal too long!\n");
        free(object);
        return NULL;
    }
    object->data = data_block;

    // Copy each letter into string object.
    for (int i = 0; i < read_lenght; ++i) {
        object->data[i] = string_literal[i];
    }
    object->data[read_lenght] = '\0';

    // Enlarge track list if needed.
    if (ac_string.tracked_count + 1 >= ac_string.tracked_limit) {
        size_t tracked_new_limit = ac_string.tracked_limit * 2;

        ac_string_t **new_data_list = realloc(ac_string.tracked_list, tracked_new_limit * sizeof(ac_string_t *));
        if (new_data_list == NULL) {
            printf("OOM: resizing track list!\n");
            free(object);
            return NULL;
        }

        ac_string.tracked_list = new_data_list;
        ac_string.tracked_limit = tracked_new_limit;
    }

    // Add string object to list.
    ac_string.tracked_list[ac_string.tracked_count] = object;
    ac_string.tracked_count++;

    // Exit good.
    return object;
}

// Action: Destroyes string object.
// Args type: string object.
// Mutates: string object.
static void destroy (ac_string_t *object)
{
    // Validate string object.
    if (object == NULL) {
        printf("Null string object!\n");
        return;
    }

    // Destroy string object.
    object->lenght = 0;
    free(object->data);
    free(object);
    object = NULL;
}

// Action: Gets string literal from string object.
// Args type: const string object.
// Returns: string literal.
const char * get (const ac_string_t *object)
{
    // Validate string object.
    if (object == NULL) {
        printf("Null string object!\n");
        return NULL;
    }
    if (object->lenght == 0) {
        printf("Empty string object!\n");
        return NULL; 
    }

    // Return string literal from inside the string object.
    return (const char *)(object->data);
}

// Action: Used in match function. Ran when match func received string longer then 1 char.
int match_multiple_char_string (const ac_string_t *object, const ac_string_t *match)
{
    // Find match end char instances.
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

// Action: Checks if match string object is present in string object.
// Args type: string object, string object.
// Args order: object, match.
// Returns: 0 for 'found' | 1 for 'not found'.
static int match (const ac_string_t *object, const ac_string_t *match)
{
    // Validate text & match strings.
    if (object == NULL) {
        printf("Null string object!\n");
        return AC_BAD;
    }
    if (match == NULL) {
        printf("Null match string object!\n");
        return AC_BAD;
    }
    if (match->lenght > object->lenght) {
        printf("Match string longer text!\n");
        return AC_BAD;
    }

    // Store result from match funcs.
    int result = 0;

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
// Args type: string object, const char *.
// Args order: object, string literal.
// Mutates: string object.
static void change (ac_string_t *object, const char *string_literal)
{
    // Validate string object, string literal.
    if (object == NULL) {
        printf("Null string object!\n");
        return;
    }
    if (string_literal == NULL) {
        printf("Null string literal!\n");
        return;
    }

    // Get string_literal lenght.
    size_t text_len = strlen(string_literal);
    if (text_len <= 0) {
        printf("Empty string literal!\n");
        return;
    }

    // Change text inside string object.
    char *new_block = malloc(text_len * sizeof(char));
    if (new_block == NULL) {
        printf("OOM: changing string literal inside string object!\n");
        return;
    }
    free(object->data);
    object->data = new_block;

    // Exit good.
    return;
}

// Action: Calls destroy upon all items that were created.
static void destructor (void)
{
    // Validate track list.
    if (ac_string.tracked_list == NULL) return;

    // Loop.
    for (size_t i = 0; i < ac_string.tracked_count; i++) {
        if (ac_string.tracked_list[i] != NULL) {
            destroy(ac_string.tracked_list[i]);
        }
    }

    // Destroy track list.
    free(ac_string.tracked_list);
    ac_string.tracked_list= NULL;

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

    // Init Tracker
    ac_string.tracked_count = 0;
    ac_string.tracked_limit = 4;
    ac_string_t **obj_list = malloc(ac_string.tracked_limit * sizeof(ac_string_t *));
    if (obj_list == NULL) {
        printf("OOM: vector list!\n");
        return;
    }

    ac_string.tracked_list = obj_list;

    // Exit good.
    return;
}
