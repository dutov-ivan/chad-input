#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "input.h"

int check_int_meets_restrictions(int *value, const char *name, int max_value,
                                 int min_value, int is_max_included,
                                 int is_min_included) {
  if (is_min_included) {
    if (*value < min_value) {
      display_error("%s має бути більший-рівний %d.", name, min_value);
      return ERROR;
    }
  } else {
    if (*value <= min_value) {
      display_error("%s має бути більший за %d.", name, min_value);
      return ERROR;
    }
  }

  if (is_max_included) {
    if (*value > max_value) {
      display_error("%s має бути менший-рівний %d.", name, max_value);
      return ERROR;
    }
  } else {
    if (*value >= max_value) {
      display_error("%s має бути менший за %d.", name, max_value);
      return ERROR;
    }
  }

  return SUCCESS;
}

int check_int_flow(long int *value, char *name) {
  if (*value > (long)INT_MAX) {
    display_error(
        "Значення %s настільки велике, що неприпустиме для "
        "використання.",
        name);
    return ERROR;
  }
  if (*value < (long)INT_MIN) {
    display_error(
        "Значення %s настільки мале, що неприпустиме для використання.", name);
    return ERROR;
  }
  return SUCCESS;
}

int read_int(int *value, const char *full_name, const char *short_name,
             int max_char_count, int is_restricted, int max_value,
             int min_value, int is_max_included, int is_min_included) {
  if (is_restricted) {
    printf("Введіть %s (від %d до %d): ", full_name, min_value, max_value);
  } else {
    printf("Введіть %s: ", full_name);
  }

  char input[max_char_count + 2];
  char *endptr;

  if (!fgets(input, max_char_count + 2, stdin)) {
    display_error("Не вдалося прочитати ввід для %s.\n", full_name);
    return ERROR;
  }
  if (input[strlen(input) - 1] != '\n') {
    display_error("Довжина %s в символах має бути меншою за %d.\n", short_name,
                  max_char_count);
    clear_input();
    return ERROR;
  }

  if (check_if_floating_point(input) == ERROR) {
    display_error("%s має бути цілим числом.\n", short_name);
    return ERROR;
  }

  long temp_value = strtol(input, &endptr, 10);

  if (temp_value > INT_MAX || temp_value < INT_MIN) {
    display_error("%s значення перевищує допустимі межі для int.\n",
                  short_name);
    return ERROR;
  }

  if (endptr == input || *endptr != '\n') {
    display_error("%s має бути числом і не містити додаткових символів!\n",
                  short_name);
    return ERROR;
  }

  *value = (int)temp_value;

  if (is_restricted &&
      check_int_meets_restrictions(value, short_name, max_value, min_value,
                                   is_max_included, is_min_included)) {
    return ERROR;
  }

  return SUCCESS;
}
