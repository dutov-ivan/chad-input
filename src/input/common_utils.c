#include "input.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void mock_input(const char *input) {
  FILE *temp = fopen("test_input.txt", "w");
  if (!temp) {
    perror("fopen");
    exit(EXIT_FAILURE);
  }

  fputs(input, temp);
  fclose(temp);

  temp = freopen("test_input.txt", "r", stdin);
  if (!temp) {
    perror("freopen");
    exit(EXIT_FAILURE);
  }
}

void replace_commas_with_dots(char *string) {
  while (*string) {
    if (*string == ',') {
      *string = '.';
    }
    string++;
  }
}

int validate_input_precision(const char *input, int max_significant_digits) {
  int significant_digits = 0;

  for (size_t i = 0; i < strlen(input); i++) {
    char c = input[i];

    if (c >= '0' && c <= '9') {
      significant_digits++;
    }
  }

  if (significant_digits > max_significant_digits) {
    display_warning("Ввід перевищує максимальну дозволену кількість значущих "
                    "цифр %d. Розрахунки можуть бути неточними",
                    max_significant_digits);
    return 1;
  }

  return 0;
}

int display_error(const char *format, ...) {
  va_list args;
  va_start(args, format);

  printf("\n" RED "ПОМИЛКА! ");
  vprintf(format, args);
  printf(RESET "\n");

  va_end(args);
  return 1;
}

int display_warning(const char *format, ...) {
  va_list args;
  va_start(args, format);

  printf("\n" YELLOW "УВАГА! ");
  vprintf(format, args);
  printf(RESET "\n");

  va_end(args);
  return 1;
}

int display_success(const char *format, ...) {
  va_list args;
  va_start(args, format);

  printf("\n" GREEN "ПЕРЕМОГА! ");
  vprintf(format, args);
  printf(RESET "\n");

  va_end(args);
  return 1;
}
