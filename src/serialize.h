#ifndef GIT_CLONE_SERIALIZE_H
#define GIT_CLONE_SERIALIZE_H

#include "data_structures.h"

char *serialize_repository(Repository const *repository);

char *serialize_commit(Commit const *commit);

char *serialize_file(File const *file);

#endif // GIT_CLONE_SERIALIZE_H
