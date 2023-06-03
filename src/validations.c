#include "validations.h"
#include "actions.h"
#include "archives.h"
#include "files.h"
#include "parse.h"
#include "utils.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool validate_arguments(int argc, char const *argv[]) {
  if (argc < 2) {
    printf("No action provided\n");
    exit(1);
  }
  char const *action = argv[1];

  bool is_init = strcmp(action, INIT) == 0;
  bool is_add = strcmp(action, ADD) == 0;
  bool is_commit = strcmp(action, COMMIT) == 0;
  bool is_log = strcmp(action, LOG) == 0;
  bool is_show = strcmp(action, SHOW) == 0;
  bool is_rebase = strcmp(action, REBASE) == 0;

  // if invalid action
  if (!is_init && !is_add && !is_commit && !is_log && !is_show && !is_rebase) {
    printf("Invalid action\n");
    return false;
  }
  // if init and has arguments
  if (is_init && argc != 2) {
    printf("Init receives no arguments!\n");
    return false;
  }
  // if add and does not have one singular argument
  if (is_add && argc != 3) {
    printf("Add receives one argument (the file path)!\n");
    return false;
  }
  // if commit and does not have two arguments
  if (is_commit && argc != 4) {
    printf("Commit receives two arguments (-m and the message)!\n");
    return false;
  }
  // if commit and middle argument is not -m or --message
  if (is_commit &&
      ((strcmp(argv[2], "-m") != 0) && (strcmp(argv[2], "--message") != 0))) {
    printf("Commit receives two arguments (-m and the message)!\n");
    return false;
  }
  // if log and has more than one argument
  if (is_log && argc != 2 && argc != 3) {
    printf("Log receives no arguments or --content!\n");
    return false;
  }
  // if log and has more than one argument and it is not --content
  if (is_log && argc == 3 && (strcmp(argv[2], "-c") != 0) &&
      (strcmp(argv[2], "--content") != 0)) {
    printf("Log receives no arguments or -c!\n");
    return false;
  }
  // if show and has more than one argument
  if (is_show && argc != 3) {
    printf("Show receives one numeric argument (the commit id)!\n");
    return false;
  }
  // if show and argument is not numeric
  if (is_show && !is_numeric(argv[2])) {
    printf("Show receives one numeric argument (the commit id)!\n");
    return false;
  }
  // if rebase and has more than one argument
  if (is_rebase && argc != 3) {
    printf("Rebase receives one numeric argument (the commit id)!\n");
    return false;
  }
  // if rebase and argument is not numeric
  if (is_rebase && !is_numeric(argv[2])) {
    printf("Rebase receives one numeric argument (the commit id)!\n");
    return false;
  }
  return true;
}

bool validate_repository() {
  if (!file_exists(GIT_FOLDER)) {
    printf("Git folder not found.\n");
    return false;
  }
  if (!file_exists(FILES_TXT)) {
    printf("Files.txt not found.\n");
    return false;
  }
  if (!file_exists(CONTENTS_TXT)) {
    printf("Contents.txt not found.\n");
    return false;
  }

  // convert file into vector of lines
  CharVector *files_txt_lines = read_lines(FILES_TXT);
  if (files_txt_lines == NULL) {
    printf("Error reading %s\n", FILES_TXT);
    return false;
  }
  // parse lines into repository
  Repository const *repository = parse_repository(files_txt_lines);
  free_vector(files_txt_lines);
  if (repository == NULL) {
    printf("Error parsing %s\n", FILES_TXT);
    return false;
  }
  // check if there is an open commit
  if (!on_going_commit_exists(repository)) {
    printf("Open commit not found.\n");
    return false;
  }
  return true;
}