#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "input.h"

void prompt_user_input_double(const char *name, int is_restricted,
                              double min_value, double max_value) {
  if (is_restricted == 1) {
    printf("Введіть %s (від %lg до %lg): ", name, min_value, max_value);
  } else {
    printf("Введіть %s: ", name);
  }
}

bool is_double_in_range(double *value, const char *name, double max_value,
                        double min_value, bool is_max_included,
                        bool is_min_included) {
  if ((is_min_included && *value < min_value - TOLERANCE) ||
      (!is_min_included && *value <= min_value + TOLERANCE)) {
    display_error("%s має бути %s %lg", name,
                  is_min_included ? "більший-рівний" : "більший за", min_value);
    return false;
  }

  if ((is_max_included && *value > max_value + TOLERANCE) ||
      (!is_max_included && *value >= max_value - TOLERANCE)) {
    display_error("%s має бути %s %lg", name,
                  is_min_included ? "менший-рівний" : "менший за", min_value);
    return false;
  }

  return true;
}

double truncate_double(double num, int decimal_places) {
  double factor = pow(10, decimal_places);
  return trunc(num * factor) / factor;
}

bool is_double_input_precise(const char *input) {
  return is_input_precise(input, DBL_DIG);
}

void print_double_precise(double num, int decimal_places) {
  printf("%.*lf", decimal_places, truncate_double(num, decimal_places));
}

bool is_double_flow(double *value, const char *name) {
  return (fabs(*value) < DBL_MIN || fabs(*value) == HUGE_VALL);
}

bool is_double_input_valid(const char *input, double *value, const char *name) {
  char *endptr;
  *value = strtod(input, &endptr);

  if (endptr == input || *endptr != '\n') {
    display_error("%s має бути числом і не містити додаткових символів!", name);
    return false;
  }

  if (errno == ERANGE && is_double_flow(value, name) == ERROR) {
    display_error("Повинно бути %lg < %s < %lg або %lg < %s < %lg", -HUGE_VAL,
                  name, -DBL_MIN, DBL_MIN, name, HUGE_VAL);
    return false;
  }
  return true;
}

int read_double(double *value, const char *full_name, const char *short_name,
                int max_char_count, bool is_restricted, double max_value,
                double min_value, bool is_max_included, bool is_min_included) {
  char input[max_char_count + 2];
  errno = 0;

  if (read_input(input, max_char_count, full_name) == ERROR) {
    return ERROR;
  }

  if (!is_input_length_valid(input, max_char_count, full_name)) {
    return ERROR;
  }

  replace_commas_with_dots(input);

  if (!is_double_input_valid(input, value, full_name)) {
    return ERROR;
  }

  if (is_restricted &&
      !is_double_in_range(value, short_name, max_value, min_value,
                          is_max_included, is_min_included) == ERROR) {
    return ERROR;
  }

  is_double_input_precise(input);

  return SUCCESS;
}
