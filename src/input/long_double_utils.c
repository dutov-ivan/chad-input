#include <errno.h>
#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "input.h"

int check_long_double_meets_restrictions(long double *value, const char *name,
                                         long double max_value,
                                         long double min_value,
                                         int is_max_included,
                                         int is_min_included) {
  if (is_min_included) {
    if (*value < min_value - TOLERANCE) {
      display_error("%s має бути більший-рівний %Lg.", name, min_value);
      return ERROR;
    }
  } else {
    if (*value <= min_value + TOLERANCE) {
      display_error("%s має бути більший за %Lg.", name, min_value);
      return ERROR;
    }
  }

  if (is_max_included) {
    if (*value > max_value + TOLERANCE) {
      display_error("%s має бути менший-рівний %Lg.", name, max_value);
      return ERROR;
    }
  } else {
    if (*value >= max_value - TOLERANCE) {
      display_error("%s має бути менший за %Lg.", name, max_value);
      return ERROR;
    }
  }
  return SUCCESS;
}

int check_long_double_flow(long double *value, const char *name) {
  if (fabsl(*value) < LDBL_MIN) {
    display_error(
        "Значення %s настільки мале, що неприпустиме для "
        "використання.",
        name);
    return ERROR;
  } else if (*value == HUGE_VALL || *value == -HUGE_VALL) {
    display_error(
        "Значення %s настільки абсолютно велике, що неприпустиме для "
        "використання.",
        name);
    return ERROR;
  }
  return SUCCESS;
}

int read_long_double(long double *value, const char *full_name,
                     const char *short_name, int max_char_count,
                     int is_restricted, long double max_value,
                     long double min_value, int is_max_included,
                     int is_min_included) {
  if (is_restricted == 1) {
    printf("Введіть %s (від %Lg до %Lg): ", full_name, min_value, max_value);
  } else {
    printf("Введіть %s: ", full_name);
  }

  char input[max_char_count + 2];
  char *endptr;
  errno = 0;

  if (!fgets(input, max_char_count + 2, stdin)) {
    display_error("Не вдалося прочитати ввід для %s.", full_name);
    return ERROR;
  }

  if (input[strlen(input) - 1] != '\n') {
    display_error("Довжина %s в символах має бути меншою за %u.", short_name,
                  max_char_count);
    clear_input();
    return ERROR;
  }

  replace_commas_with_dots(input);

  *value = strtold(input, &endptr);

  if (endptr == input || *endptr != '\n') {
    display_error("%s має бути числом і не містити додаткових символів!",
                  short_name);
    return ERROR;
  }

  if (errno == ERANGE && check_long_double_flow(value, short_name) == ERROR) {
    return ERROR;
  }

  if (is_restricted == 1 && check_long_double_meets_restrictions(
                                value, short_name, max_value, min_value,
                                is_max_included, is_min_included) == ERROR) {
    return ERROR;
  }

  return SUCCESS;
}
