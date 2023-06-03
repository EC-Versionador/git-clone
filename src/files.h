#ifndef GIT_CLONE_FILES_H
#define GIT_CLONE_FILES_H

#include "data_structures.h"
#include <stdbool.h>

bool file_exists(char const *path);

char *read_file(char const *path);

int write_to_file(char const *path, char const *content);

int append_to_file(char const *path, char const *content);

int create_folder(char const *path);

CharVector *read_lines(char const *path);

#endif // GIT_CLONE_FILES_H
