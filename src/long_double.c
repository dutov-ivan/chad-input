#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "input.h"
#include "input_internals.h"
#define TOLERANCE LDBL_EPSILON

void prompt_user_input_long_double(const char *name, int is_restricted,
                                   long double min_value,
                                   long double max_value) {
  if (is_restricted == 1) {
    printf("Введіть %s (від %Lg до %Lg): ", name, min_value, max_value);
  } else {
    printf("Введіть %s: ", name);
  }
}

bool is_long_double_in_range(long double *value, const char *name,
                             long double max_value, long double min_value,
                             bool is_max_included, bool is_min_included) {
  if ((is_min_included && *value < min_value - TOLERANCE) ||
      (!is_min_included && *value <= min_value + TOLERANCE)) {
    display_error("%s має бути %s %Lg", name,
                  is_min_included ? "більший-рівний" : "більший за", min_value);
    return false;
  }

  if ((is_max_included && *value > max_value + TOLERANCE) ||
      (!is_max_included && *value >= max_value - TOLERANCE)) {
    display_error("%s має бути %s %Lg", name,
                  is_min_included ? "менший-рівний" : "менший за", min_value);
    return false;
  }

  return true;
}

long double truncate_long_double(long double num, int decimal_places) {
  long double factor = powl(10, decimal_places);
  return truncl(num * factor) / factor;
}

void print_long_double_precise(long double num, int decimal_places) {
  printf("%.*Lf", decimal_places, truncate_long_double(num, decimal_places));
}

bool is_long_double_flow(long double *value, const char *name) {
  return (fabsl(*value) < LDBL_MIN || fabsl(*value) == HUGE_VALL);
}

bool is_long_double_input_valid(const char *input, long double *value,
                                const char *name) {
  char *endptr;
  *value = strtold(input, &endptr);

  if (endptr == input || *endptr != '\n') {
    display_error("%s має бути числом і не містити додаткових символів!", name);
    return false;
  }

  if (errno == ERANGE && is_long_double_flow(value, name) == ERROR) {
    display_error("Повинно бути %Lg < %s < %Lg або %Lg < %s < %Lg", -HUGE_VALL,
                  name, -LDBL_MIN, LDBL_MIN, name, HUGE_VALL);
    return false;
  }
  return true;
}

int read_long_double(long double *value, const char *full_name,
                     const char *short_name, int max_char_count,
                     bool is_restricted, long double max_value,
                     long double min_value, bool is_max_included,
                     bool is_min_included) {
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

  replace_commas_with_dots(input);

  if (!is_long_double_input_valid(input, value, full_name)) {
    return ERROR;
  }

  if (is_restricted &&
      !is_long_double_in_range(value, short_name, max_value, min_value,
                               is_max_included, is_min_included) == ERROR) {
    return ERROR;
  }

  if (!is_input_precise(input, LDBL_DIG)) {
    display_error_not_precise(LDBL_DIG);
  }

  return SUCCESS;
}
