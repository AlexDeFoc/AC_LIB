#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ac_string.h>

#define AC_GOOD 0
#define AC_BAD 1

AC_STRING_CLASS ac_string;

// Takes in a "char *" aka a "string literal".
// Outputs ac_string_t object.
ac_string_t create(const char *text) {
    struct ac_string_t string = {
        .data = NULL,
        .lenght = 0
    };


    size_t read_lenght = strlen(text);
    if (read_lenght <= 0) {
        printf("No string provided!\n");
        return string;
    }
    string.lenght = read_lenght;

    char *data_block = malloc((read_lenght + 1) * sizeof(char));
    if (data_block == NULL) {
        printf("String too long!\n");
        return string;
    }
    string.data = data_block;


    for (int i = 0; i < read_lenght; ++i) {
        string.data[i] = text[i];
    }
    string.data[read_lenght] = '\0';

    return string;
}

// Takes in a "ac_string_t" object.
// Clears, frees it and destroys it.
void destroy(ac_string_t *string) {
    if (string->lenght == 0) {
        printf("No string found to destroy!\n");
        return;
    }

    string->lenght = 0;
    free(string->data);
    string->data = NULL;
}

// Takes in a "ac_string_t" object.
// Doesn't modify the object.
// Returns "const char *" aka "const string literal".
const char* get(const ac_string_t *string) {
    if (string->lenght == 0) {
        printf("No string to provide!\n");
        return NULL; 
    }

    return (const char *)string->data;
}

int match_multiple_char_string(const ac_string_t *text, const ac_string_t *match) {
    // Validate text & match strings.
    if (match->lenght <= 0) {
        printf("No matching string provided!\n");
        return AC_BAD;
    }
    if (text->lenght <= 0) {
        printf("No text provided!\n");
        return AC_BAD;
    }
    if (match->lenght > text->lenght) {
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
    for (int i = 0; i < text->lenght; i++) {
        if (text->data[i] == match->data[match_end_index]) {
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
    for (int i = 0; i < text->lenght; i++) {
        if (text->data[i] == match->data[match_end_index]) {
            ends_index[dummy_index] = i;
            dummy_index++;
        }
    }

    // Check if start is matching based on end.
    int found_start_index = -1;
    for (int i = 0; i < ends_found_count; i++) {
        int start_edge = text->lenght - match->lenght - ends_index[i] - 1;
        if (text->data[start_edge] == match->data[0]) {
            found_start_index = start_edge;
            break;
        }
    }
    // Exit if start not found.
    if (found_start_index == -1) return AC_BAD;


    // Check each char between ends.
    for (int i = 0; i < match->lenght; i++) {
        if (text->data[found_start_index + i] != match->data[i]) return AC_BAD;
    }

    // Exit good.
    free(ends_index);
    return AC_GOOD;
}

int match_single_char_string(const ac_string_t *text, const ac_string_t *match) {
    // Validate text & match strings.
    if (match->lenght <= 0) {
        printf("No matching string provided!\n");
        return AC_BAD;
    }
    if (text->lenght <= 0) {
        printf("No text provided!\n");
        return AC_BAD;
    }
    if (match->lenght > 1) {
        printf("Match string longer then supported!\n");
        return AC_BAD;
    }

    // Find char in text.
    char matching_char = match->data[0];
    for (int i = 0; i < text->lenght; i++) {
        if (text->data[i] == matching_char) {
            return AC_GOOD;
        }
    }

    return AC_BAD;
}

// Takes in two "const ac_string_t" object.
// Doesn't modify either object.
// Returns 0 for 'found' | 1 for 'not found'.
int match (const ac_string_t *text, const ac_string_t *match) {
    int result = -1;
    if (match->lenght > 1) {
        result = match_multiple_char_string(text, match);
    } else {
        result = match_single_char_string(text, match);
    }

    return result;
}

// Takes in a "ac_string_t" object, "const char *" aka a "cosnt string literal".
// Doesn't modify the "const char *" primitive.
// Modifies the "ac_string_t" object.
void change (ac_string_t *string, const char *text) {
    if (string->lenght <= 0) {
        printf("No matching string provided!\n");
        return;
    }
    size_t text_len = strlen(text);
    if (text_len <= 0) {
        printf("No text provided!\n");
        return;
    }

    char *new_block = malloc(text_len * sizeof(char));
    if (new_block == NULL) {
        printf("No memory for changing string contents!\n");
        return;
    }
    free(string->data);
    string->data = new_block;

    return;
}

void __attribute__((constructor)) init_AC_STRING_CLASS(void) {
    ac_string.create = create;
    ac_string.destroy = destroy;
    ac_string.get = get;
    ac_string.match = match;
}
