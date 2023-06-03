#include "parse.h"
#include "data_structures.h"
#include "utils.h"
#include <stdbool.h>
#include <string.h>

Repository *parse_repository(CharVector const *files_txt_lines) {
  // initializes new repository
  Repository *repository = new_repository();
  if (repository == NULL)
    return NULL;

  // auxiliary commit and file to keep track
  Commit *last_seen_commit = new_commit(-1, NULL);
  if (last_seen_commit == NULL) {
    free_repository(repository, false, false);
    return NULL;
  }
  File *last_seen_file = new_file(NULL, -1, -1);
  if (last_seen_file == NULL) {
    free_repository(repository, false, false);
    free_commit(last_seen_commit, false);
    return NULL;
  }

  int err = 0;
  for (size_t i = 0; i < files_txt_lines->size; i++) {
    char const *line = files_txt_lines->data[i];
    bool starts_with_id = starts_with(line, "id:");
    bool starts_with_message = starts_with(line, "message:");
    bool starts_with_path = starts_with(line, "path:");
    bool starts_with_start = starts_with(line, "start:");
    bool starts_with_end = starts_with(line, "end:");
    bool is_new_commit = last_seen_commit->id != -1 && starts_with_id;

    // adds last_seen_commit to repository and creates a new last_seen_commit
    // with id
    if (is_new_commit) {
      push_commit_to_repository(repository, last_seen_commit);
      int id = slice_and_parse(line, 3, (int)strlen(line) - 2);
      if (id == -1)
        err = 1;
      last_seen_commit = new_commit(id, "");
    }
    // adds id to last_seen_commit
    if (starts_with_id) {
      int id = slice_and_parse(line, 3, (int)strlen(line) - 2);
      last_seen_commit->id = id;
    }
    // adds message to last_seen_commit
    if (starts_with_message) {
      char *new_message = slice_string(line, 8, (int)strlen(line) - 2);
      if (new_message == NULL)
        err = 1;
      last_seen_commit->message = new_message;
    }
    // adds file to last_seen_commit
    if (starts_with_path) {
      char *path = slice_string(line, 5, (int)strlen(line) - 2);
      if (path == NULL)
        err = 1;
      last_seen_file->path = path;
    }
    // adds start to last_seen_file
    if (starts_with_start) {
      int start = slice_and_parse(line, 6, (int)strlen(line) - 2);
      last_seen_file->start = start;
    }
    // adds end to last_seen_file and since it's the last field of a file,
    // pushes it to last_seen_commit and creates a new last_seen_file
    if (starts_with_end) {
      int end = slice_and_parse(line, 4, (int)strlen(line) - 2);
      last_seen_file->end = end;

      push_file_to_commit(last_seen_commit, last_seen_file);
      last_seen_file = new_file(NULL, -1, -1);
      if (last_seen_file == NULL)
        err = 1;
    }
    if (err == 0)
      continue;

    // if invalid token
    free_repository(repository, true, true);
    free_commit(last_seen_commit, false);
    free_file(last_seen_file);
    return NULL;
  }

  // pushes the last commit to repository
  push_commit_to_repository(repository, last_seen_commit);
  return repository;
}