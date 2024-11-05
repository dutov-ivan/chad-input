#include "input.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_long_double_meets_restrictions(long double *value, const char *name,
                                         long double max_value,
                                         long double min_value,
                                         int is_max_included,
                                         int is_min_included,
                                         long double tolerance) {

  if (is_min_included) {
    if (*value < min_value - tolerance) {
      display_error("%s має бути більший-рівний %Lg.", name, min_value);
      return 1;
    }
  } else {
    if (*value <= min_value + tolerance) {
      display_error("%s має бути більший за %Lg.", name, min_value);
      return 1;
    }
  }

  if (is_max_included) {
    if (*value > max_value + tolerance) {
      display_error("%s має бути менший-рівний %Lg.", name, max_value);
      return 1;
    }
  } else {
    if (*value >= max_value - tolerance) {
      display_error("%s має бути менший за %Lg.", name, max_value);
      return 1;
    }
  }

  return 0;
}

int read_long_double(long double *value, const char *full_name,
                     const char *short_name, int max_char_count,
                     int is_restricted, int is_quiet_mode,
                     long double max_value, long double min_value,
                     int is_max_included, int is_min_included,
                     long double tolerance) {
  if (is_quiet_mode == 1) {
    printf("%s: ", short_name);
  } else if (is_restricted == 1) {
    printf("Введіть %s (від %Lg до %Lg): ", full_name, min_value, max_value);
  } else {
    printf("Введіть %s: ", full_name);
  }

  char input[max_char_count + 2];
  char *endptr;

  if (!fgets(input, max_char_count + 2, stdin)) {
    display_error("Не вдалося прочитати ввід для %s.", full_name);
    return 1;
  }

  if (input[strlen(input) - 1] != '\n') {
    display_error("Довжина %s в символах має бути меншою за %u.", short_name,
                  max_char_count);
    fflush(stdin);
    return 1;
  }

  replace_commas_with_dots(input);

  *value = strtold(input, &endptr);
  if (endptr == input || *endptr != '\n') {
    display_error("%s має бути числом і не містити додаткових символів!",
                  short_name);
    return 1;
  }

  if (is_restricted == 1 &&
      check_long_double_meets_restrictions(value, short_name, max_value,
                                           min_value, is_max_included,
                                           is_min_included, tolerance) == 1) {
    return 1;
  }

  return 0;
}
