#include "utils.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool is_numeric(char const *string) {
  for (int i = 0; i < strlen(string); i++)
    if (string[i] < '0' || string[i] > '9')
      return false;
  return true;
}

bool starts_with(const char *string, const char *prefix) {
  size_t prefix_length = strlen(prefix);
  bool string_is_shorter = strlen(string) < prefix_length;
  bool string_does_not_start_with_prefix =
      strncmp(string, prefix, prefix_length) != 0;
  return !string_is_shorter && !string_does_not_start_with_prefix;
}

char *slice_string(char const *string, int start, int end) {
  char *result = malloc(strlen(string) - start);
  if (result == NULL)
    return NULL;
  int slice_length = end - start + 1;
  strncpy(result, string + start, slice_length);
  result[slice_length] = '\0';
  return result;
}

int slice_and_parse(char const *string, int start, int end) {
  // slice string and parse to int
  char *result = slice_string(string, start, end);
  if (result == NULL)
    return -1;
  int parsed = (int)strtol(result, NULL, 10);
  free(result);
  return parsed;
}

char *append_to_string(char *string, char *suffix) {
  size_t new_size = strlen(string) + strlen(suffix) + 1;
  char *result = malloc(new_size * sizeof(char));
  if (result == NULL)
    return NULL;
  strcpy(result, string);
  strcat(result, suffix);
  free(string);
  free(suffix);
  return result;
}
