#include <string.h>

#include "input.h"

int validate_float_input_precision(const char *input, float value,
                                   int max_significant_digits,
                                   const char *short_name) {
  if (value < 1e-6f && value > -1e-6f && value != 0) {
    display_warning(
        "%s має значення з більш ніж 6 знаками після коми. "
        "Точність може бути втрачена.",
        short_name);
    return 1;
  }

  char *dot = strchr(input, '.');
  if (dot != NULL) {
    int decimal_places = 0;
    for (char *p = dot + 1; *p != '\0' && *p != '\n' && *p != 'e' && *p != 'E';
         p++) {
      if (*p >= '0' && *p <= '9') {
        decimal_places++;
      }
    }
    if (decimal_places > max_significant_digits) {
      display_warning(
          "%s має значення з більш ніж %d знаками після коми. "
          "Точність може бути втрачена.",
          short_name, max_significant_digits);
      return 1;
    }
  }
  return 0;
}
