#ifndef GIT_CLONE_PARSE_H
#define GIT_CLONE_PARSE_H

#include "data_structures.h"

Repository *parse_repository(CharVector const *files_txt_lines);

#endif // GIT_CLONE_PARSE_H
