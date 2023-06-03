#include "actions.h"
#include "archives.h"
#include "data_structures.h"
#include "files.h"
#include "parse.h"
#include "serialize.h"
#include "validations.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void git_init() {
  if (!file_exists(GIT_FOLDER))
    create_folder(GIT_FOLDER);
  if (!file_exists(FILES_TXT))
    append_to_file(FILES_TXT, "");
  if (!file_exists(CONTENTS_TXT))
    append_to_file(CONTENTS_TXT, "");

  // parse file into repository
  CharVector const *files_txt_lines = read_lines(FILES_TXT);
  if (files_txt_lines == NULL) {
    printf("Error reading %s\n", FILES_TXT);
    return;
  }
  Repository *repository = parse_repository(files_txt_lines);

  if (!on_going_commit_exists(repository))
    append_to_file(FILES_TXT, "id:0\n");

  free_repository(repository, true, true);
}

void git_add(char const *file_path) {
  // make validations
  bool is_valid = validate_repository();
  if (!is_valid)
    return;
  file_exists(file_path);

  // parses files.txt into repository
  CharVector *files_txt_lines = read_lines(FILES_TXT);
  if (files_txt_lines == NULL) {
    printf("Error reading %s\n", FILES_TXT);
    return;
  }
  Repository *repository = parse_repository(files_txt_lines);
  free_vector(files_txt_lines);

  // check if file is already added
  Commit *on_going_commit = repository->tail_commit;
  if (on_going_commit == NULL) {
    printf("Open commit not found\n");
    free_repository(repository, true, true);
    return;
  }
  if (file_in_commit(on_going_commit, file_path)) {
    printf("File already added\n");
    free_repository(repository, true, true);
    return;
  }
  free_repository(repository, false, false);

  // add file to repository
  char *file_text = malloc(128 * sizeof(char));
  if (file_text == NULL) {
    printf("Error allocating memory\n");
    return;
  }
  sprintf(file_text, "path:%s\nstart:-1\nend:-1\n", file_path);
  if (file_text == NULL) {
    printf("Error allocating memory\n");
    return;
  }
  int err = append_to_file(FILES_TXT, file_text);
  if (err != 0) {
    printf("Error appending to %s\n", FILES_TXT);
    free(file_text);
    return;
  }
  free(file_text);
}

void git_commit(char const *message) {

}

void git_log(bool log_content) {

}

void git_show(char const *commit_id_str) {

}

void git_rebase(char const *commit_id_str) {

}