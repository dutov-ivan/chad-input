#ifndef COMMON_H
#define COMMON_H

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

int show_error(const char *format, ...) __attribute__((format(printf, 1, 2)));
int show_warning(const char *format, ...) __attribute__((format(printf, 1, 2)));
int show_success(const char *format, ...) __attribute__((format(printf, 1, 2)));
int show_warning_not_precise(int max_significant_digits);
int show_error_overlength(const char *name, int max_char_count);
int show_error_not_number(const char *name);
int show_error_NaN(const char *name);

void replace_commas_with_dots(char *string);

bool is_input_floating_point(char *str);
bool is_numeric_input_precise(const char *input, int max_significant_digits);
bool is_input_within_length(const char *input);
bool is_input_number_after_conversion(const char *endptr, const char *input);

void clear_stdin();
int read_input(char *input, int max_char_count, const char *name);
#endif
