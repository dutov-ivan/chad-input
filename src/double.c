#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "input_internals.h"
#define TOLERANCE DBL_EPSILON
#define MIN_ABSOLUTE_VALUE DBL_MIN
#define MAX_ABSOLUTE_VALUE DBL_MAX
#define OVERFLOW_ABSOLUTE_VALUE HUGE_VAL
#define MAX_SIGNIFICANT_DIGITS DBL_DIG

void display_prompt_user_input_double(const char *name, int is_restricted,
                                      double min_value, double max_value) {
  if (is_restricted == 1) {
    printf("Введіть %s (від %lg до %lg): ", name, min_value, max_value);
  } else {
    printf("Введіть %s: ", name);
  }
}

RangeCheckResult check_range_double(double *value, const char *name,
                                    double max_value, double min_value,
                                    bool is_max_included,
                                    bool is_min_included) {
  if (is_min_included && *value < min_value - TOLERANCE) return LESS;
  if (!is_min_included && *value <= min_value + TOLERANCE) return LESS_EQUAL;

  if (is_max_included && *value > max_value + TOLERANCE) return GREATER;
  if (!is_max_included && *value >= max_value - TOLERANCE) return GREATER_EQUAL;
  return WITHIN_RANGE;
}

void display_range_error(RangeCheckResult result, const char *name,
                         double min_value, double max_value) {
  switch (result) {
    case LESS:
      display_error("%s має бути більший-рівний %lg.\n", name, min_value);
      break;
    case LESS_EQUAL:
      display_error("%s має бути більший за %lg.\n", name, min_value);
      break;
    case GREATER:
      display_error("%s має бути менший-рівний %lg.\n", name, max_value);
      break;
    case GREATER_EQUAL:
      display_error("%s має бути менший за %lg.\n", name, max_value);
      break;
    case WITHIN_RANGE:
      break;
  }
}

double truncate_double(double num, int decimal_places) {
  double factor = pow(10, decimal_places);
  return trunc(num * factor) / factor;
}

void print_double_precise(double num, int decimal_places) {
  printf("%.*lf", decimal_places, truncate_double(num, decimal_places));
}

bool is_double_overflow(double *value) {
  return (fabs(*value) == OVERFLOW_ABSOLUTE_VALUE);
}

bool is_double_underflow(double *value) {
  return (fabs(*value) < MIN_ABSOLUTE_VALUE);
}

RangeCheckResult check_double_within_global_bounds(const char *input,
                                                   double *value,
                                                   const char *name) {
  RangeCheckResult check_result = WITHIN_RANGE;
  if (is_double_overflow(value)) {
    check_result = GREATER_EQUAL;
  } else if (is_double_underflow(value)) {
    check_result = LESS_EQUAL;
  }
  return check_result;
}

int read_double(double *value, const char *full_name, const char *short_name,
                int max_char_count, bool is_restricted, double max_value,
                double min_value, bool is_max_included, bool is_min_included) {
  char input[max_char_count + 2];

  display_prompt_user_input_double(full_name, is_restricted, min_value,
                                   max_value);
  if (read_input(input, max_char_count, full_name) == ERROR) {
    return ERROR;
  }

  if (!is_input_within_length(input)) {
    display_error_input_outside_length(full_name, max_char_count);
    clear_input();
    return ERROR;
  }

  replace_commas_with_dots(input);

  char *endptr;
  *value = strtod(input, &endptr);

  if (is_input_number_after_conversion(endptr, input)) {
    display_error_not_number(full_name);
  }

  RangeCheckResult global_bounds_check =
      check_double_within_global_bounds(input, value, full_name);

  if (global_bounds_check != WITHIN_RANGE) {
    display_range_error(global_bounds_check, short_name, min_value, max_value);
    return ERROR;
  }

  if (is_restricted) {
    RangeCheckResult min_max_check =
        check_range_double(value, short_name, max_value, min_value,
                           is_max_included, is_min_included);
    if (min_max_check != WITHIN_RANGE) {
      display_range_error(min_max_check, full_name, min_value, max_value);
      return ERROR;
    }
  }

  if (!is_input_precise(input, MAX_SIGNIFICANT_DIGITS)) {
    display_warning_not_precise(MAX_SIGNIFICANT_DIGITS);
  }

  return SUCCESS;
}
