#include "serialize.h"
#include "data_structures.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *serialize_file(File const *file) {
  // initializes file string
  char *text = malloc(sizeof(char));
  if (text == NULL)
    return NULL;
  strcpy(text, "");

  // appends file path to the file string
  char *path_text = malloc(sizeof(char) * 128);
  if (path_text == NULL) {
    free(text);
    return NULL;
  }
  sprintf(path_text, "path:%s\n", file->path);
  if (path_text == NULL) {
    free(text);
    return NULL;
  }
  text = append_to_string(text, path_text);
  if (text == NULL)
    return NULL;

  // appends file start to the file string
  char *start_text = malloc(sizeof(char) * 128);
  if (start_text == NULL) {
    free(text);
    return NULL;
  }
  sprintf(start_text, "start:%d\n", file->start);
  if (start_text == NULL) {
    free(text);
    return NULL;
  }
  text = append_to_string(text, start_text);
  if (text == NULL)
    return NULL;

  // appends file end to the file string
  char *end_text = malloc(sizeof(char) * 128);
  if (end_text == NULL) {
    free(text);
    return NULL;
  }
  sprintf(end_text, "end:%d\n", file->end);
  if (end_text == NULL) {
    free(text);
    return NULL;
  }
  text = append_to_string(text, end_text);
  if (text == NULL)
    return NULL;

  return text;
}

char *serialize_commit(Commit const *commit) {
  // initializes commit string
  char *text = malloc(sizeof(char));
  if (text == NULL)
    return NULL;
  strcpy(text, "");

  // appends commit id to the commit string
  char *id_text = malloc(sizeof(char) * 128);
  if (id_text == NULL) {
    free(text);
    return NULL;
  }
  sprintf(id_text, "id:%d\n", commit->id);
  if (id_text == NULL) {
    free(text);
    return NULL;
  }
  text = append_to_string(text, id_text);
  if (text == NULL)
    return NULL;

  // appends commit message to the commit string
  char *message_text = malloc(sizeof(char) * 128);
  if (message_text == NULL) {
    free(text);
    return NULL;
  }
  sprintf(message_text, "message:%s\n", commit->message);
  if (message_text == NULL) {
    free(text);
    return NULL;
  }
  text = append_to_string(text, message_text);
  if (text == NULL)
    return NULL;

  // for each file in commit serializes it and appends it to the commit string
  File *file = commit->head_file;
  while (file != NULL) {
    char *file_text = serialize_file(file);
    if (file_text == NULL) {
      free(text);
      return NULL;
    }
    text = append_to_string(text, file_text);
    if (text == NULL)
      return NULL;
    file = file->next;
  }
  return text;
}

char *serialize_repository(Repository const *repository) {
  // initializes the repository string
  char *text = malloc(sizeof(char));
  if (text == NULL) {
    return NULL;
  }
  strcpy(text, "");

  // for each commit serializes it and append to the repository string
  Commit *commit = repository->head_commit;
  while (commit != NULL) {
    char *commit_text = serialize_commit(commit);
    if (commit_text == NULL) {
      free(text);
      return NULL;
    }
    text = append_to_string(text, commit_text);
    commit = commit->next;
  }
  return text;
}