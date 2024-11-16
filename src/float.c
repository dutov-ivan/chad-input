#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "input.h"

void prompt_user_input_float(const char *name, int is_restricted,
                             float min_value, float max_value) {
  if (is_restricted == 1) {
    printf("Введіть %s (від %g до %g): ", name, min_value, max_value);
  } else {
    printf("Введіть %s: ", name);
  }
}

bool is_float_in_range(float *value, const char *name, float max_value,
                       float min_value, bool is_max_included,
                       bool is_min_included) {
  if ((is_min_included && *value < min_value - TOLERANCE) ||
      (!is_min_included && *value <= min_value + TOLERANCE)) {
    display_error("%s має бути %s %g", name,
                  is_min_included ? "більший-рівний" : "більший за", min_value);
    return false;
  }

  if ((is_max_included && *value > max_value + TOLERANCE) ||
      (!is_max_included && *value >= max_value - TOLERANCE)) {
    display_error("%s має бути %s %g", name,
                  is_min_included ? "менший-рівний" : "менший за", min_value);
    return false;
  }

  return true;
}

float truncate_float(float num, int decimal_places) {
  float factor = powf(10, decimal_places);
  return truncf(num * factor) / factor;
}

bool is_float_input_precise(const char *input) {
  return is_input_precise(input, FLT_DIG);
}

void print_float_precise(float num, int decimal_places) {
  printf("%.*f", decimal_places, truncate_float(num, decimal_places));
}

bool is_float_flow(float *value, const char *name) {
  return (fabsl(*value) < FLT_MIN || fabsl(*value) == FLT_MAX);
}

bool is_float_input_valid(const char *input, float *value, const char *name) {
  char *endptr;
  *value = strtof(input, &endptr);

  if (endptr == input || *endptr != '\n') {
    display_error("%s має бути числом і не містити додаткових символів!", name);
    return false;
  }

  if (errno == ERANGE && is_float_flow(value, name) == ERROR) {
    display_error("Повинно бути %g < %s < %g або %g < %s < %g", -HUGE_VALF,
                  name, -FLT_MIN, FLT_MIN, name, HUGE_VALF);
    return false;
  }
  return true;
}

int read_float(float *value, const char *full_name, const char *short_name,
               int max_char_count, bool is_restricted, float max_value,
               float min_value, bool is_max_included, bool is_min_included) {
  char input[max_char_count + 2];
  errno = 0;

  if (read_input(input, max_char_count, full_name) == ERROR) {
    return ERROR;
  }

  if (!is_input_length_valid(input, max_char_count, full_name)) {
    return ERROR;
  }

  replace_commas_with_dots(input);

  if (!is_float_input_valid(input, value, full_name)) {
    return ERROR;
  }

  if (is_restricted &&
      !is_float_in_range(value, short_name, max_value, min_value,
                         is_max_included, is_min_included) == ERROR) {
    return ERROR;
  }

  is_float_input_precise(input);

  return SUCCESS;
}
