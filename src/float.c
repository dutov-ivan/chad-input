#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "errno.h"
#include "input.h"
#include "test.h"

#define TOLERANCE FLT_EPSILON
#define MIN_ABSOLUTE_VALUE FLT_MIN
#define MAX_ABSOLUTE_VALUE FLT_MAX
#define OVERFLOW_ABSOLUTE_VALUE HUGE_VALF
#define MAX_SIGNIFICANT_DIGITS FLT_DIG

// Show Functions
void prompt_user_for_float(const char *name, bool is_restricted,
                           float min_value, float max_value) {
  if (is_restricted) {
    printf("Введіть %s (від %g до %g): ", name, min_value, max_value);
  } else {
    printf("Введіть %s: ", name);
  }
}

void show_range_error_float(const char *name, RangeCheckResult result,
                            float min_value, float max_value) {
  switch (result) {
    case LESS:
      show_error("%s має бути більший-рівний %g.\n", name, min_value);
      break;
    case LESS_EQUAL:
      show_error("%s має бути більший за %g.\n", name, min_value);
      break;
    case GREATER:
      show_error("%s має бути менший-рівний %g.\n", name, max_value);
      break;
    case GREATER_EQUAL:
      show_error("%s має бути менший за %g.\n", name, max_value);
      break;
    default:
      break;
  }
}

// Range Checking Functions
RangeCheckResult validate_range_float(float value, float min_value,
                                      float max_value, bool is_min_included,
                                      bool is_max_included) {
  if (is_min_included && value < min_value - TOLERANCE) return LESS;
  if (!is_min_included && value <= min_value + TOLERANCE) return LESS_EQUAL;
  if (is_max_included && value > max_value + TOLERANCE) return GREATER;
  if (!is_max_included && value >= max_value - TOLERANCE) return GREATER_EQUAL;
  return WITHIN_RANGE;
}

RangeCheckResult validate_overflow_float(float value) {
  if (errno == ERANGE) {
    if (fabsf(value) == OVERFLOW_ABSOLUTE_VALUE) return GREATER_EQUAL;
    if (fabsf(value) < MIN_ABSOLUTE_VALUE) return LESS_EQUAL;
  }
  return WITHIN_RANGE;
}

// Utility Functions
float truncate_to_precision_float(float num, int decimal_places) {
  float factor = powf(10, decimal_places);
  return truncf(num * factor) / factor;
}

void print_truncated_float(float num, int decimal_places) {
  printf("%.*f", decimal_places,
         truncate_to_precision_float(num, decimal_places));
}

// Main Read Function
int read_float(float *value, const char *full_name, const char *short_name,
               int max_char_count, bool is_restricted, float max_value,
               float min_value, bool is_max_included, bool is_min_included) {
  char input[max_char_count + 2];
  errno = 0;

  prompt_user_for_float(full_name, is_restricted, min_value, max_value);

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
  *value = strtof(input, &endptr);

  if (!is_input_number_after_conversion(endptr, input)) {
    show_error_not_number(full_name);
    return ERROR;
  }

  RangeCheckResult global_check = validate_overflow_float(*value);
  if (global_check != WITHIN_RANGE) {
    show_range_error_float(short_name, global_check, min_value, max_value);
    return ERROR;
  }

  if (is_restricted) {
    RangeCheckResult range_check = validate_range_float(
        *value, min_value, max_value, is_min_included, is_max_included);
    if (range_check != WITHIN_RANGE) {
      show_range_error_float(full_name, range_check, min_value, max_value);
      return ERROR;
    }
  }

  if (!is_numeric_input_precise(input, MAX_SIGNIFICANT_DIGITS)) {
    show_warning_not_precise(MAX_SIGNIFICANT_DIGITS);
  }

  return SUCCESS;
}
