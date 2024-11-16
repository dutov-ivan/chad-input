#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "input.h"
#include "input_internals.h"

void prompt_user_input_long_long_int(const char *name, bool is_restricted,
                                     long long int min_value,
                                     long long int max_value) {
  if (is_restricted) {
    printf("Введіть %s (від %lld до %lld): ", name, min_value, max_value);
  } else {
    printf("Введіть %s: ", name);
  }
}

bool is_long_long_int_in_range(long long int *value, const char *name,
                               long long int max_value, long long int min_value,
                               bool is_max_included, bool is_min_included) {
  if ((is_min_included && *value < min_value) ||
      (!is_min_included && *value <= min_value)) {
    display_error("%s має бути %s %lld", name,
                  is_min_included ? "більший-рівний" : "більший за", min_value);
    return false;
  }

  if ((is_max_included && *value > max_value) ||
      (!is_max_included && *value >= max_value)) {
    display_error("%s має бути %s %lld", name,
                  is_min_included ? "менший-рівний" : "менший за", min_value);
    return false;
  }

  return true;
}

bool is_long_long_int_flow(long long int num) {
  return (num < LLONG_MIN || num > LLONG_MAX);
}

bool is_long_long_int_input_valid(char *input, long long int *value,
                                  const char *name) {
  if (is_input_floating_point(input)) {
    display_error("%s має бути цілим числом.\n", name);
    return false;
  }

  char *endptr;
  long temp_value = strtoll(input, &endptr, 10);

  if (endptr == input || *endptr != '\n') {
    display_error("%s має бути числом і не містити додаткових символів!\n",
                  name);
    return false;
  }

  if (errno == ERANGE && is_long_long_int_flow(temp_value)) {
    display_error("%s має бути більшим за %d і меншим за %d!", name, LLONG_MIN,
                  LLONG_MAX);
    return false;
  }

  *value = temp_value;

  return true;
}

int read_long_long_int(long long int *value, const char *full_name,
                       const char *short_name, long long int max_char_count,
                       bool is_restricted, long long int max_value,
                       long long int min_value, bool is_max_included,
                       bool is_min_included) {
  prompt_user_input_long_long_int(full_name, is_restricted, min_value,
                                  max_value);

  char input[max_char_count + 2];
  errno = 0;

  if (read_input(input, max_char_count, full_name) == ERROR) {
    return ERROR;
  }

  if (!is_input_within_length(input)) {
    display_error_input_outside_length(full_name, max_char_count);
    clear_input();
    return ERROR;
  }

  if (!is_long_long_int_input_valid(input, value, short_name)) {
    return ERROR;
  }

  if (is_restricted &&
      !is_long_long_int_in_range(value, short_name, max_value, min_value,
                                 is_max_included, is_min_included)) {
    return ERROR;
  }

  return SUCCESS;
}
