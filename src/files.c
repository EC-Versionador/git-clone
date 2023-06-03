#include "files.h"
#include "data_structures.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

bool file_exists(char const *path) {
  FILE *file = fopen(path, "r");
  if (file == NULL)
    return false;
  fclose(file);
  return true;
}

char *read_file(char const *path) {
  char *buffer;
  long length;
  int error;
  FILE *file = fopen(path, "rb");
  if (file == NULL)
    return NULL;
  error = fseek(file, 0, SEEK_END);
  if (error != 0)
    return NULL;
  length = ftell(file);
  error = fseek(file, 0, SEEK_SET);
  if (error != 0)
    return NULL;
  buffer = malloc(length);
  if (buffer)
    fread(buffer, 1, length, file);
  fclose(file);
  return buffer;
}

CharVector *read_lines(char const *path) {
  // creates a dynamic array of strings which are the lines of the file
  FILE *file;
  char *line = NULL;
  size_t len = 0;
  file = fopen(path, "r");
  if (file == NULL)
    return NULL;
  CharVector *lines = new_vector();
  if (lines == NULL) {
    fclose(file);
    return NULL;
  }
  while (getline(&line, &len, file) != -1) {
    push_to_vector(lines, line);
  }
  fclose(file);
  return lines;
}

int write_to_file(char const *path, char const *content) {
  // overrides file
  FILE *file = fopen(path, "w");
  if (file == NULL)
    return 1;
  fprintf(file, "%s", content);
  fclose(file);
  return 0;
}

int append_to_file(char const *path, char const *content) {
  // writes to the end of the file
  FILE *file = fopen(path, "a");
  if (file == NULL)
    return 1;
  fprintf(file, "%s", content);
  fclose(file);
  return 0;
}

int create_folder(char const *path) {
  int error = mkdir(path, 0777);
  if (error != 0)
    return 1;
  return 0;
}