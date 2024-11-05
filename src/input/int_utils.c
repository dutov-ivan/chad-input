#include "input.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_int_meets_restrictions(int *value, const char *name, int max_value,
                                 int min_value, int is_max_included,
                                 int is_min_included) {

  if (is_min_included) {
    if (*value < min_value) {
      display_error("%s має бути більший-рівний %d.", name, min_value);
      return 1;
    }
  } else {
    if (*value <= min_value) {
      display_error("%s має бути більший за %d.", name, min_value);
      return 1;
    }
  }

  if (is_max_included) {
    if (*value > max_value) {
      display_error("%s має бути менший-рівний %d.", name, max_value);
      return 1;
    }
  } else {
    if (*value >= max_value) {
      display_error("%s має бути менший за %d.", name, max_value);
      return 1;
    }
  }

  return 0;
}

int read_int(int *value, const char *full_name, const char *short_name,
             int max_char_count, int is_restricted, int is_quiet_mode,
             int max_value, int min_value, int is_max_included,
             int is_min_included) {

  if (is_quiet_mode == 1) {
    printf("%s: ", short_name);
  } else if (is_restricted == 1) {
    printf("Введіть %s (від %d до %d): ", full_name, min_value, max_value);
  } else {
    printf("Введіть %s: ", full_name);
  }

  char input[max_char_count + 2];
  char *endptr;

  if (!fgets(input, max_char_count + 2, stdin)) {
    display_error("Не вдалося прочитати ввід для %s.\n", full_name);
    return 1;
  }
  if (input[strlen(input) - 1] != '\n') {
    display_error("Довжина %s в символах має бути меншою за %d.\n", short_name,
                  max_char_count);
    fflush(stdin);
    return 1;
  }

  replace_commas_with_dots(input);

  long double input_num = strtold(input, &endptr);
  if (endptr == input || *endptr != '\n') {
    display_error("%s має бути числом і не містити додаткових символів!\n",
                  short_name);
    return 1;
  }

  if (floor(input_num) != input_num) {
    display_error("%s має бути цілим числом.\n", short_name);
    return 1;
  }

  *value = (int)input_num;

  if (is_restricted == 1 &&
      check_int_meets_restrictions(value, short_name, max_value, min_value,
                                   is_max_included, is_min_included)) {
    return 1;
  }

  return 0;
}
