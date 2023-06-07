#include "actions.h"
#include "validations.h"
#include <stdbool.h>
#include <string.h>

int main(int argc, char const *argv[]) {
  bool is_valid = validate_arguments(argc, argv);
  if (!is_valid)
    return 1;
  char const *action = argv[1];

  bool is_init = strcmp(action, INIT) == 0;
  bool is_add = strcmp(action, ADD) == 0;
  bool is_commit = strcmp(action, COMMIT) == 0;
  bool is_log = strcmp(action, LOG) == 0;
  bool is_show = strcmp(action, SHOW) == 0;
  bool is_checkout = strcmp(action, CHECKOUT) == 0;

  if (is_init) {
    git_init();
    return 0;
  }
  if (is_add) {
    git_add(argv[2]);
    return 0;
  }
  if (is_commit) {
    git_commit(argv[3]);
    return 0;
  }
  if (is_log) {
    git_log(argc == 3);
    return 0;
  }
  if (is_show) {
    git_show(argv[2]);
    return 0;
  }
  if (is_checkout) {
    git_checkout(argv[2]);
    return 0;
  }

  return 0;
}