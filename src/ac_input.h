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
    //// Functions for ac_input_t object.
    // Action: Creates input object.
    // Arguments: Takes in "const size_t" primitive.
    // Desc: The primitive represents the input limit.
    // Desc: The input limit can be 0 or over 0. If given 0 then it means there is not limit.
    // Warning: Size_t is an unsigned type meaning if a negative value is given it underflows.
    // Changes: The primitive is not modified.
    // Returns: address input object.
    ac_input_t *(*create)(size_t input_limit);

    // Action: Destroys input object.
    // Arguments: Takes in input object.
    // Changes: Modifies the input object taken in.
    void (*destroy) (ac_input_t *input);

    // Action: Starts receiving input from stdin until a certain limit or until end of line found.
    // Arguments: Takes in input object.
    // Changes: Modifies the input object taken in.
    void (*receive) (ac_input_t *input);

    // Action: Gets the input contents from the input object.
    // Arguments: Takes in input object.
    // Changes: Doesn't change the input object taken in.
    // Returns: address to string literal inside input object.
    const char *(*get) (const ac_input_t *input);

    // Action: Resets input object. It calls destory then create without having to reenter the input limit.
    // Arguments: Takes in input object.
    // Changes: Modifies the input object.
    void (*reset) (ac_input_t *input);

    //// Tracking created objects.
    ac_input_t **tracked_objects_list;
    size_t tracked_objects_amount;
    size_t tracking_objects_limit;

    // Action: Calls destroy function for each tracked (created) object that isnt already destroyed.
    void (*destructor) (void);
} AC_INPUT_CLASS;

extern AC_INPUT_CLASS ac_input;

// Action: Makes ac_input functions available.
void ac_lib_init_input(void);

#endif
