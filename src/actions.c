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
  // make validations
  bool is_valid = validate_repository();
  if (!is_valid)
    return;

  // parse files.txt into repository
  CharVector *files_txt_lines = read_lines(FILES_TXT);
  if (files_txt_lines == NULL) {
    printf("Error reading %s\n", FILES_TXT);
    return;
  }
  Repository *repository = parse_repository(files_txt_lines);
  free_vector(files_txt_lines);

  // get open commit
  Commit *on_going_commit = repository->tail_commit;
  if (on_going_commit == NULL) {
    printf("Open commit not found.\n");
    free_repository(repository, true, true);
    return;
  }

  // for each file in open commit add its contents to contents.txt and get
  // its starting and ending positions in the contents.txt file and registers
  // it on the repository struct
  File *file = on_going_commit->tail_file;
  CharVector *contents_txt_lines;
  int start;
  int end;
  char *file_content;
  while (file != NULL) {
    if (!file_exists(file->path)) {
      file = file->prev;
      continue;
    }
    contents_txt_lines = read_lines(CONTENTS_TXT);
    if (contents_txt_lines == NULL) {
      printf("Error reading %s\n", CONTENTS_TXT);
      return;
    }
    start = contents_txt_lines->size + 1;
    file_content = read_file(file->path);
    if (file_content == NULL) {
      printf("Error reading %s\n", file->path);
      free_repository(repository, true, true);
      free_vector(contents_txt_lines);
      return;
    }
    append_to_file(CONTENTS_TXT, "\n");
    append_to_file(CONTENTS_TXT, file_content);
    free(file_content);
    contents_txt_lines = read_lines(CONTENTS_TXT);
    if (contents_txt_lines == NULL) {
      printf("Error reading %s\n", CONTENTS_TXT);
      free_repository(repository, true, true);
      return;
    }
    end = contents_txt_lines->size;
    file->start = start;
    file->end = end;
    file = file->prev;
  }
  if (on_going_commit->message == NULL) {
    on_going_commit->message = malloc(128 * sizeof(char));
    if (on_going_commit->message == NULL) {
      printf("Error allocating memory\n");
      free_repository(repository, true, true);
      return;
    }
  }
  // set commit message
  strcpy(on_going_commit->message, message);

  // serializes repository into string and writes it to files.txt
  char const *files_txt_content = serialize_repository(repository);
  if (files_txt_content == NULL) {
    printf("Error serializing repository\n");
    free_repository(repository, true, true);
    return;
  }
  int err = write_to_file(FILES_TXT, files_txt_content);
  if (err != 0) {
    printf("Error writing to %s\n", FILES_TXT);
    free_repository(repository, true, true);
    return;
  }

  // create new open commit
  char *on_going_commit_text = malloc(128 * sizeof(char));
  if (on_going_commit_text == NULL) {
    printf("Error allocating memory\n");
    free_repository(repository, true, true);
    return;
  }
  sprintf(on_going_commit_text, "id:%d\n", on_going_commit->id + 1);
  if (on_going_commit_text == NULL) {
    printf("Error allocating memory\n");
    free_repository(repository, true, true);
    return;
  }
  append_to_file(FILES_TXT, on_going_commit_text);
  free_repository(repository, true, true);
  free(on_going_commit_text);
}

void git_log(bool log_content) {
  // make validations
  bool is_valid = validate_repository();
  if (!is_valid)
    return;

  // parse files.txt into repository
  CharVector *files_txt_lines = read_lines(FILES_TXT);
  if (files_txt_lines == NULL) {
    printf("Error reading %s\n", FILES_TXT);
    return;
  }
  Repository *repository = parse_repository(files_txt_lines);
  free_vector(files_txt_lines);
  if (repository == NULL) {
    printf("Error parsing repository\n");
    return;
  }
  // read contents.txt lines
  CharVector *contents_txt_lines = read_lines(CONTENTS_TXT);
  if (contents_txt_lines == NULL) {
    printf("Error reading %s\n", CONTENTS_TXT);
    free_repository(repository, true, true);
    return;
  }
  // print repository
  print_repository(repository, log_content, contents_txt_lines->data);
  free_vector(contents_txt_lines);
}

void git_show(char const *commit_id_str) {

}

void git_rebase(char const *commit_id_str) {

}