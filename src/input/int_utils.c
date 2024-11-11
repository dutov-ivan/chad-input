#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "input.h"

int check_int_meets_restrictions(int *value, const char *name, int max_value,
                                 int min_value, int is_max_included,
                                 int is_min_included) {
  if ((is_min_included && *value < min_value) ||
      (!is_min_included && *value <= min_value)) {
    display_error("%s має бути %s %d", name,
                  is_min_included ? "більший-рівний" : "більший за", min_value);
    return ERROR;
  }

  if ((is_max_included && *value > max_value) ||
      (!is_max_included && *value >= max_value)) {
    display_error("%s має бути %s %d", name,
                  is_min_included ? "менший-рівний" : "менший за", min_value);
    return ERROR;
  }

  return SUCCESS;
}

void prompt_user_input_int(const char *name, int is_restricted, int min_value,
                           int max_value) {
  if (is_restricted) {
    printf("Введіть %s (від %d до %d): ", name, min_value, max_value);
  } else {
    printf("Введіть %s: ", name);
  }
}

int convert_and_validate_int(const char *input, int *value, const char *name) {
  char *endptr;
  long temp_value = strtol(input, &endptr, 10);

  if (endptr == input || *endptr != '\n') {
    display_error("%s має бути числом і не містити додаткових символів!\n",
                  name);
    return ERROR;
  }

  *value = temp_value;

  return SUCCESS;
}

int read_int(int *value, const char *full_name, const char *short_name,
             int max_char_count, int is_restricted, int max_value,
             int min_value, int is_max_included, int is_min_included) {
  prompt_user_input_int(full_name, is_restricted, min_value, max_value);

  char input[max_char_count + 2];

  if (read_input_and_validate_length(input, max_char_count, full_name) ==
      ERROR) {
    return ERROR;
  }

  if (check_if_floating_point(input) == ERROR) {
    display_error("%s має бути цілим числом.\n", short_name);
    return ERROR;
  }

  if (convert_and_validate_int(input, value, short_name) == ERROR) {
    return ERROR;
  }

  if (is_restricted &&
      check_int_meets_restrictions(value, short_name, max_value, min_value,
                                   is_max_included, is_min_included) == ERROR) {
    return ERROR;
  }

  return SUCCESS;
}
