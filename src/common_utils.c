#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "input.h"

void replace_commas_with_dots(char *string) {
  while (*string) {
    if (*string == ',') {
      *string = '.';
    }
    string++;
  }
}

int check_if_floating_point(char *str) {
  while (*str) {
    switch (*str) {
      case '.':
      case ',':
      case 'e':
      case 'E':
        return 1;
      default:
        break;
    }
    str++;
  }
  return 0;
}

void clear_input() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
}

int request_repeat() {
  char choice[3];
  printf(
      "Продовжити? Введіть '+' для продовження або будь-яку іншу клавішу, якщо "
      "не погоджуєтесь: ");

  if (!fgets(choice, sizeof(choice), stdin)) {
    printf("Помилка читання вводу.\n");
    return 1;
  }

  if (choice[0] == '+' && choice[1] == '\n') {
    return 0;
  }

  clear_input();

  return 1;
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
    display_warning(
        "Ввід перевищує максимальну дозволену кількість значущих "
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

int read_input_and_validate_length(char *input, int max_char_count,
                                   const char *name) {
  if (!fgets(input, max_char_count + 2, stdin)) {
    display_error("Не вдалося прочитати ввід для %s.\n", name);
    return ERROR;
  }
  if (input[strlen(input) - 1] != '\n') {
    display_error("Довжина %s в символах має бути меншою за %d.\n", name,
                  max_char_count);
    clear_input();
    return ERROR;
  }
  return SUCCESS;
}
