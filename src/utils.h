#ifndef GIT_CLONE_UTILS_H
#define GIT_CLONE_UTILS_H

#include <stdbool.h>

bool is_numeric(char const *string);

bool starts_with(const char *string, const char *prefix);

char *slice_string(char const *string, int start, int end);

int slice_and_parse(char const *string, int start, int end);

char *append_to_string(char *string, char *suffix);

#endif // GIT_CLONE_UTILS_H
