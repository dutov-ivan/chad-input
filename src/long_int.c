#include <errno.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "common.h"
#include "input.h"

#define MAX_VALUE LONG_MAX
#define MIN_VALUE LONG_MIN

void prompt_user_input_long_int(const char *name, bool is_restricted,
                                long int min_value, long int max_value) {
  if (is_restricted) {
    printf("Введіть %s (від %ld до %ld): ", name, min_value, max_value);
  } else {
    printf("Введіть %s: ", name);
  }
}

int show_range_error_long_int(const char *name, RangeCheckResult result,
                              long int min_value, long int max_value) {
  switch (result) {
    case LESS:
      show_error("%s має бути більший-рівний %ld.\n", name, min_value);
      break;
    case LESS_EQUAL:
      show_error("%s має бути більший за %ld.\n", name, min_value);
      break;
    case GREATER:
      show_error("%s має бути менший-рівний %ld.\n", name, max_value);
      break;
    case GREATER_EQUAL:
      show_error("%s має бути менший за %ld.\n", name, max_value);
      break;
    default:
      break;
  }
  return PIPE;
}

// Range Checking Functions
RangeCheckResult validate_range_long_int(long int value, long int min_value,
                                         long int max_value,
                                         bool is_min_included,
                                         bool is_max_included) {
  if (is_min_included && value < min_value) return LESS;
  if (!is_min_included && value <= min_value) return LESS_EQUAL;
  if (is_max_included && value > max_value) return GREATER;
  if (!is_max_included && value >= max_value) return GREATER_EQUAL;
  return WITHIN_RANGE;
}

RangeCheckResult validate_overflow_long_int(long int value) {
  if (errno == ERANGE) {
    // Max and min are overflow values
    if (value == MAX_VALUE) return GREATER;
    if (value == MIN_VALUE) return LESS;
  }
  return WITHIN_RANGE;
}

int read_long_int_and_validate(long int *value, const char *full_name,
                  const char *short_name, long int max_char_count,
                  bool is_restricted, long int max_value, long int min_value,
                  bool is_max_included, bool is_min_included) {
  prompt_user_input_long_int(full_name, is_restricted, min_value, max_value);

  char input[max_char_count + 2];
  errno = 0;

  if (read_input(input, max_char_count, full_name) == ERROR) {
    return ERROR;
  }

  if (!is_input_within_length(input)) {
    show_error_overlength(full_name, max_char_count);
    clear_stdin();
    return ERROR;
  }

  char *endptr;
  *value = strtol(input, &endptr, 10);

  if (!is_input_number_after_conversion(endptr, input)) {
    show_error_not_number(full_name);
    return ERROR;
  }

  RangeCheckResult global_check = validate_overflow_long_int(*value);
  if (global_check != WITHIN_RANGE) {
    show_range_error_long_int(short_name, global_check, min_value, max_value);
    return ERROR;
  }

  if (is_restricted) {
    RangeCheckResult range_check = validate_range_long_int(
        *value, min_value, max_value, is_min_included, is_max_included);
    if (range_check != WITHIN_RANGE) {
      show_range_error_long_int(full_name, range_check, min_value, max_value);
      return ERROR;
    }
  }

  return SUCCESS;
}
