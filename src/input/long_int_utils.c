#include <limits.h>

#include "input.h"

int check_long_int_flow(long *value, const char *name) {
  if (*value >= LONG_MAX) {
    display_error(
        "Значення %s настільки мале, що неприпустиме для "
        "використання.",
        name);
    return ERROR;
  }
  if (*value <= LONG_MIN) {
    display_error(
        "Значення %s настільки мале, що неприпустиме для "
        "використання.",
        name);
    return ERROR;
  }
  return SUCCESS;
}
