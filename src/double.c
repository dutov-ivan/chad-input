#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "input.h"

#define TOLERANCE DBL_EPSILON
#define MIN_ABSOLUTE_VALUE DBL_MIN
#define MAX_ABSOLUTE_VALUE DBL_MAX
#define OVERFLOW_ABSOLUTE_VALUE HUGE_VAL
#define MAX_SIGNIFICANT_DIGITS DBL_DIG

// Show Functions
void prompt_user_for_double(const char *name, bool is_restricted,
                            double min_value, double max_value) {
  if (is_restricted) {
    printf("Введіть %s (від %lg до %lg): ", name, min_value, max_value);
  } else {
    printf("Введіть %s: ", name);
  }
}

int show_range_error_double(const char *name, RangeCheckResult result,
                            double min_value, double max_value) {
  switch (result) {
    case LESS:
      show_error("%s має бути більший-рівний %lg.\n", name, min_value);
      break;
    case LESS_EQUAL:
      show_error("%s має бути більший за %lg.\n", name, min_value);
      break;
    case GREATER:
      show_error("%s має бути менший-рівний %lg.\n", name, max_value);
      break;
    case GREATER_EQUAL:
      show_error("%s має бути менший за %lg.\n", name, max_value);
      break;
    default:
      break;
  }
  return PIPE;
}

// Range Checking Functions
RangeCheckResult validate_range_double(double value, double min_value,
                                       double max_value, bool is_min_included,
                                       bool is_max_included) {
  if (is_min_included && value < min_value - TOLERANCE) return LESS;
  if (!is_min_included && value <= min_value + TOLERANCE) return LESS_EQUAL;
  if (is_max_included && value > max_value + TOLERANCE) return GREATER;
  if (!is_max_included && value >= max_value - TOLERANCE) return GREATER_EQUAL;
  return WITHIN_RANGE;
}

RangeCheckResult validate_overflow_double(double value) {
  if (errno == ERANGE) {
    if (fabs(value) == OVERFLOW_ABSOLUTE_VALUE) return GREATER_EQUAL;
    if (fabs(value) < MIN_ABSOLUTE_VALUE) return LESS_EQUAL;
  }
  return WITHIN_RANGE;
}

// Utility Functions
double truncate_to_precision_double(double num, int decimal_places) {
  double factor = pow(10, decimal_places);
  return trunc(num * factor) / factor;
}

void print_truncated_double(double num, int decimal_places) {
  printf("%.*lf", decimal_places,
         truncate_to_precision_double(num, decimal_places));
}

// Main Read Function
int read_double_and_validate(double *value, const char *full_name,
                             const char *short_name, int max_char_count,
                             bool is_restricted, double max_value,
                             double min_value, bool is_max_included,
                             bool is_min_included) {
  char input[max_char_count + 2];
  errno = 0;

  prompt_user_for_double(full_name, is_restricted, min_value, max_value);

  if (read_input(input, max_char_count, full_name) == ERROR) {
    return ERROR;
  }

  if (!is_input_within_length(input)) {
    show_error_overlength(full_name, max_char_count);
    clear_stdin();
    return ERROR;
  }

  replace_commas_with_dots(input);

  // Parse value
  char *endptr;
  *value = strtod(input, &endptr);

  if (!is_input_number_after_conversion(endptr, input)) {
    show_error_not_number(full_name);
    return ERROR;
  }

  RangeCheckResult global_check = validate_overflow_double(*value);
  if (global_check != WITHIN_RANGE) {
    show_range_error_double(short_name, global_check, min_value, max_value);
    return ERROR;
  }

  if (is_restricted) {
    RangeCheckResult range_check = validate_range_double(
        *value, min_value, max_value, is_min_included, is_max_included);
    if (range_check != WITHIN_RANGE) {
      show_range_error_double(full_name, range_check, min_value, max_value);
      return ERROR;
    }
  }

  if (!is_numeric_input_precise(input, MAX_SIGNIFICANT_DIGITS)) {
    show_warning_not_precise(MAX_SIGNIFICANT_DIGITS);
    if (ask_repeat() == ERROR) {
      return ERROR;
    }
  }

  return SUCCESS;
}
