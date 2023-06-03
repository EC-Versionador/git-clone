#include "data_structures.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

CharVector *new_vector() {
  CharVector *vector = malloc(sizeof(CharVector));
  if (vector == NULL)
    return NULL;
  vector->size = 0;
  vector->capacity = 1;
  vector->data = malloc(sizeof(char *));
  if (vector->data == NULL) {
    free(vector);
    return NULL;
  }
  return vector;
}

File *new_file(char const *path, int start, int end) {
  File *file = malloc(sizeof(File));
  if (file == NULL)
    return NULL;
  if (path != NULL) {
    file->path = malloc(strlen(path) + 1);
    strcpy(file->path, path);
  }
  file->start = start;
  file->end = end;
  file->next = NULL;
  file->prev = NULL;
  return file;
}

Commit *new_commit(int id, char const *message) {
  Commit *commit = malloc(sizeof(Commit));
  if (commit == NULL)
    return NULL;
  commit->id = id;
  if (message != NULL) {
    commit->message = malloc(strlen(message) + 1);
    strcpy(commit->message, message);
  } else
    commit->message = NULL;
  commit->next = NULL;
  commit->prev = NULL;
  commit->head_file = NULL;
  commit->tail_file = NULL;
  return commit;
}

Repository *new_repository() {
  Repository *repository = malloc(sizeof(Repository));
  if (repository == NULL)
    return NULL;
  repository->head_commit = NULL;
  repository->tail_commit = NULL;
  return repository;
}

void free_vector(CharVector *vector) {
  for (int i = 0; i < vector->size; i++)
    free(vector->data[i]);
  free(vector->data);
  free(vector);
}

void free_file(File *file) {
  free(file->path);
  free(file);
}

void free_commit(Commit *commit, bool free_files) {
  File *file = commit->head_file;
  free(commit);
  if (!free_files)
    return;
  while (file != NULL) {
    File *next = file->next;
    free_file(file);
    file = next;
  }
}
void free_repository(Repository *repository, bool free_commits,
                     bool free_files) {
  Commit *commit = repository->head_commit;
  free(repository);
  if (!free_commits)
    return;
  while (commit != NULL) {
    Commit *next = commit->next;
    free_commit(commit, free_files);
    commit = next;
  }
}

void push_to_vector(CharVector *vector, char const *data) {
  // append to end
  if (vector->size < vector->capacity) {
    vector->data[vector->size] = malloc(strlen(data) + 1);
    strcpy(vector->data[vector->size], data);
    vector->size++;
    return;
  }
  vector->capacity *= 2;
  char **vector_data = realloc(vector->data, vector->capacity * sizeof(char *));
  if (vector_data == NULL) {
    free_vector(vector);
    return;
  }
  vector->data = vector_data;
  vector->data[vector->size] = malloc(strlen(data) + 1);
  strcpy(vector->data[vector->size], data);
  vector->size++;
}

void push_file_to_commit(Commit *commit, File *file) {
  // append to end
  if (commit->head_file == NULL) {
    commit->head_file = file;
    commit->tail_file = file;
    return;
  }
  commit->tail_file->next = file;
  file->prev = commit->tail_file;
  commit->tail_file = file;
}

void push_commit_to_repository(Repository *repository, Commit *commit) {
  // append to end
  if (repository->head_commit == NULL) {
    repository->head_commit = commit;
    repository->tail_commit = commit;
    return;
  }
  repository->tail_commit->next = commit;
  commit->prev = repository->tail_commit;
  repository->tail_commit = commit;
}

bool file_in_commit(Commit *commit, char const *path) {
  File *file = commit->head_file;
  while (file != NULL) {
    bool paths_are_equal = strcmp(file->path, path) == 0;
    if (paths_are_equal)
      return true;
    file = file->next;
  }
  return false;
}

void print_file(File *file, bool log_content, char **contents_txt_lines) {
  printf("File: %s\n", file->path);
  if (!log_content)
    return;
  // if log content, for each line in contents.txt in range determined by
  // start and end in file struct print it
  for (int i = file->start - 1; i <= file->end - 1; i++)
    printf("%s", contents_txt_lines[i]);
}

void print_commit(Commit *commit, bool log_content, char **contents_txt_lines) {
  printf("Commit %d: %s\n", commit->id, commit->message);
  File *file = commit->tail_file;
  // for each file print it
  while (file != NULL) {
    print_file(file, log_content, contents_txt_lines);
    file = file->prev;
  }
}

void print_repository(Repository *repository, bool log_content,
                      char **contents_txt_lines) {
  // skip open commit
  Commit *commit = repository->tail_commit->prev;
  // for each commit print it
  while (commit != NULL) {
    print_commit(commit, log_content, contents_txt_lines);
    commit = commit->prev;
  }
}

bool on_going_commit_exists(Repository const *repository) {
  // open commit is tail if it has no message
  if (repository->tail_commit == NULL)
    return false;
  if (repository->tail_commit->id == -1)
    return false;
  if (repository->tail_commit->message != NULL &&
      strcmp(repository->tail_commit->message, "") != 0)
    return false;
  return true;
}
