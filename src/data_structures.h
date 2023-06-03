#ifndef GIT_CLONE_DATA_STRUCTURES_H
#define GIT_CLONE_DATA_STRUCTURES_H

#include <stdbool.h>

typedef struct char_vector CharVector;

typedef struct file File;

typedef struct commit Commit;

typedef struct repository Repository;

struct char_vector {
  int size;
  int capacity;
  char **data;
};

struct file {
  char *path;
  int start;
  int end;
  File *next;
  File *prev;
};

struct commit {
  int id;
  char *message;
  Commit *next;
  Commit *prev;
  File *head_file;
  File *tail_file;
};

struct repository {
  Commit *head_commit;
  Commit *tail_commit;
};

CharVector *new_vector();

File *new_file(char const *path, int start, int end);

Commit *new_commit(int id, char const *message);

Repository *new_repository();

void free_vector(CharVector *vector);

void free_file(File *file);

void free_commit(Commit *commit, bool free_files);

void free_repository(Repository *repository, bool free_commits,
                     bool free_files);

void push_to_vector(CharVector *vector, char const *data);

void push_file_to_commit(Commit *commit, File *file);

void push_commit_to_repository(Repository *repository, Commit *commit);

bool file_in_commit(Commit *commit, char const *path);

void print_file(File *file, bool log_content, char **contents_txt_lines);

void print_commit(Commit *commit, bool log_content, char **contents_txt_lines);

void print_repository(Repository *repository, bool log_content,
                      char **contents_txt_lines);

bool on_going_commit_exists(Repository const *repository);

#endif // GIT_CLONE_DATA_STRUCTURES_H
