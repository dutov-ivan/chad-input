#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include "common.h"
#include "input.h"
#include "test.h"

int show_error(const char *format, ...) {
  va_list args;
  va_start(args, format);

  printf("\n" RED "ПОМИЛКА! ");
  vprintf(format, args);
  printf(RESET "\n");

  va_end(args);
  return PIPE;
}

int show_warning(const char *format, ...) {
  va_list args;
  va_start(args, format);

  printf("\n" YELLOW "УВАГА! ");
  vprintf(format, args);
  printf(RESET "\n");

  va_end(args);
  return PIPE;
}

int show_success(const char *format, ...) {
  va_list args;
  va_start(args, format);

  printf("\n" GREEN "ПЕРЕМОГА! ");
  vprintf(format, args);
  printf(RESET "\n");

  va_end(args);
  return PIPE;
}

int show_error_overlength(const char *name, int max_char_count) {
  show_error("Довжина %s в символах має бути меншою за %d.\n", name,
             max_char_count);
  return PIPE;
}

int show_warning_not_precise(int max_significant_digits) {
  show_warning(
      "Кількість значущих цифр перевищує максимальну дозволену кількість цифр "
      "%d. Розрахунки можуть бути неточними",
      max_significant_digits);
  return PIPE;
}

void clear_stdin() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF);
}

void replace_commas_with_dots(char *string) {
  while (*string) {
    if (*string == ',') {
      *string = '.';
    }
    string++;
  }
}

bool is_input_floating_point(char *str) {
  while (*str) {
    switch (*str) {
      case '.':
      case ',':
      case 'e':
      case 'E':
        return true;
      default:
        break;
    }
    str++;
  }
  return false;
}

int show_error_not_number(const char *name) {
  show_error("%s має бути числом і не містити додаткових символів!", name);
  return PIPE;
}

bool is_input_within_length(const char *input) {
  // Last character should be '\n' if input is withing length
  return (input[strlen(input) - 1] == '\n');
}

bool is_numeric_input_precise(const char *input, int max_significant_digits) {
  int significant_digits = 0;

  for (size_t i = 0; i < strlen(input); i++) {
    char c = input[i];

    if (c >= '0' && c <= '9') {
      significant_digits++;
    }

    if (significant_digits > max_significant_digits) {
      return false;
    }
  }

  return true;
}

bool is_input_number_after_conversion(const char *endptr, const char *input) {
  return (endptr != input && *endptr == '\n');
}

int read_input(char *input, int max_char_count, const char *name) {
  if (!fgets(input, max_char_count + 2, stdin)) {
    show_error("Не вдалося прочитати ввід для %s.\n", name);
    return ERROR;
  }
  return SUCCESS;
}

int ask_repeat() {
  char choice[3];
  printf(
      "Продовжити? Введіть '+' для продовження або будь-яку іншу клавішу, якщо "
      "не погоджуєтесь: ");

  if (!fgets(choice, sizeof(choice), stdin)) {
    printf("Помилка читання вводу.\n");
    return ERROR;
  }

  if (choice[0] == '+' && choice[1] == '\n') {
    return SUCCESS;
  }

  clear_stdin();

  return ERROR;
}
