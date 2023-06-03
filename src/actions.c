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

}

void git_commit(char const *message) {

}

void git_log(bool log_content) {

}

void git_show(char const *commit_id_str) {

}

void git_rebase(char const *commit_id_str) {

}