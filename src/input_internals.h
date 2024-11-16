#ifndef INPUT_INTERNALS_H
#define INPUT_INTERNALS_H

#include <stdbool.h>

#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define RESET "\033[0m"

#define SUCCESS 0
#define ERROR 1
#define PIPE 1

typedef enum {
  GREATER_EQUAL,
  GREATER,
  LESS,
  LESS_EQUAL,
  WITHIN_RANGE
} RangeCheckResult;

int display_error(const char *format, ...)
    __attribute__((format(printf, 1, 2)));
int display_warning(const char *format, ...)
    __attribute__((format(printf, 1, 2)));
int display_success(const char *format, ...)
    __attribute__((format(printf, 1, 2)));
int display_warning_not_precise(int max_significant_digits);
int display_error_input_outside_length(const char *name, int max_char_count);
int display_error_not_number(const char *name);

void replace_commas_with_dots(char *string);

bool is_input_floating_point(char *str);
bool is_input_precise(const char *input, int max_significant_digits);
bool is_input_within_length(const char *input);
bool is_input_number_after_conversion(const char *endptr, const char *input);

void clear_input();
int read_input(char *input, int max_char_count, const char *name);
#endif
