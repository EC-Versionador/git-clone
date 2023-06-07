#ifndef GIT_CLONE_ACTIONS_H
#define GIT_CLONE_ACTIONS_H

#include <stdbool.h>

#define INIT "init"
#define ADD "add"
#define COMMIT "commit"
#define LOG "log"
#define SHOW "show"
#define CHECKOUT "checkout"

void git_init();

void git_add(char const *file_path);

void git_commit(char const *message);

void git_log(bool log_content);

void git_show(char const *commit_id_str);

void git_checkout(char const *commit_id_str);

#endif // GIT_CLONE_ACTIONS_H
