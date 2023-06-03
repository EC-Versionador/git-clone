#ifndef GIT_CLONE_VALIDATIONS_H
#define GIT_CLONE_VALIDATIONS_H

#include <stdbool.h>

bool validate_arguments(int argc, char const *argv[]);

bool validate_repository();

#endif // GIT_CLONE_VALIDATIONS_H
