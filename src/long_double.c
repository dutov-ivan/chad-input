#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "input.h"
#include "test.h"

#define TOLERANCE LDBL_EPSILON
#define MIN_ABSOLUTE_VALUE LDBL_MIN
#define MAX_ABSOLUTE_VALUE LDBL_MAX
#define OVERFLOW_ABSOLUTE_VALUE HUGE_VALL
#define MAX_SIGNIFICANT_DIGITS LDBL_DIG

// Show Functions
void prompt_user_for_long_double(const char *name, bool is_restricted,
                                 long double min_value, long double max_value) {
  if (is_restricted) {
    printf("Введіть %s (від %Lg до %Lg): ", name, min_value, max_value);
  } else {
    printf("Введіть %s: ", name);
  }
}

void show_range_error_long_double(const char *name, RangeCheckResult result,
                                  long double min_value,
                                  long double max_value) {
  switch (result) {
    case LESS:
      show_error("%s має бути більший-рівний %Lg.\n", name, min_value);
      break;
    case LESS_EQUAL:
      show_error("%s має бути більший за %Lg.\n", name, min_value);
      break;
    case GREATER:
      show_error("%s має бути менший-рівний %Lg.\n", name, max_value);
      break;
    case GREATER_EQUAL:
      show_error("%s має бути менший за %Lg.\n", name, max_value);
      break;
    default:
      break;
  }
}

// Range Checking Functions
RangeCheckResult validate_range_long_double(long double value,
                                            long double min_value,
                                            long double max_value,
                                            bool is_min_included,
                                            bool is_max_included) {
  if (is_min_included && value < min_value - TOLERANCE) return LESS;
  if (!is_min_included && value <= min_value + TOLERANCE) return LESS_EQUAL;
  if (is_max_included && value > max_value + TOLERANCE) return GREATER;
  if (!is_max_included && value >= max_value - TOLERANCE) return GREATER_EQUAL;
  return WITHIN_RANGE;
}

RangeCheckResult validate_overflow_long_double(long double value) {
  if (errno == ERANGE) {
    if (fabsl(value) == OVERFLOW_ABSOLUTE_VALUE) return GREATER_EQUAL;
    if (fabsl(value) < MIN_ABSOLUTE_VALUE) return LESS_EQUAL;
  }
  return WITHIN_RANGE;
}

// Utility Functions
long double truncate_to_precision_long_double(long double num,
                                              int decimal_places) {
  long double factor = powl(10, decimal_places);
  return truncl(num * factor) / factor;
}

void print_truncated_long_double(long double num, int decimal_places) {
  printf("%.*Lf", decimal_places,
         truncate_to_precision_long_double(num, decimal_places));
}

// Main Read Function
int read_long_double(long double *value, const char *full_name,
                     const char *short_name, int max_char_count,
                     bool is_restricted, long double max_value,
                     long double min_value, bool is_max_included,
                     bool is_min_included) {
  char input[max_char_count + 2];
  errno = 0;

  prompt_user_for_long_double(full_name, is_restricted, min_value, max_value);

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

  RangeCheckResult global_check = validate_overflow_long_double(*value);
  if (global_check != WITHIN_RANGE) {
    show_range_error_long_double(short_name, global_check, min_value,
                                 max_value);
    return ERROR;
  }

  if (is_restricted) {
    RangeCheckResult range_check = validate_range_long_double(
        *value, min_value, max_value, is_min_included, is_max_included);
    if (range_check != WITHIN_RANGE) {
      show_range_error_long_double(full_name, range_check, min_value,
                                   max_value);
      return ERROR;
    }
  }

  if (!is_numeric_input_precise(input, MAX_SIGNIFICANT_DIGITS)) {
    show_warning_not_precise(MAX_SIGNIFICANT_DIGITS);
  }

  return SUCCESS;
}
