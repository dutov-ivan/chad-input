#ifndef INPUT_INTERNALS_H
#define INPUT_INTERNALS_H

#include <stdbool.h>

#include "common.h"

// Utils
void replace_commas_with_dots(char *string);
int ask_repeat();

void clear_stdin();

// Input checks
bool is_input_floating_point(char *str);
bool is_numeric_input_precise(const char *input, int max_significant_digits);
bool is_input_within_length(const char *input);
bool is_input_number_after_conversion(const char *endptr, const char *input);

// Checking how ranges are shown.
#define show_range_error(name, result, min_value, max_value)              \
  _Generic((min_value),                                                   \
      int: show_range_error_int,                                          \
      long int: show_range_error_long_int,                                \
      long long int: show_range_error_long_long_int,                      \
      float: show_range_error_float,                                      \
      double: show_range_error_double,                                    \
      long double: show_range_error_long_double)(name, result, min_value, \
                                                 max_value)

int show_range_error_int(const char *name, RangeCheckResult result,
                         int min_value, int max_value);
int show_range_error_long_int(const char *name, RangeCheckResult result,
                              long int min_value, long int max_value);
int show_range_error_long_long_int(const char *name, RangeCheckResult result,
                                   long long int min_value,
                                   long long int max_value);
int show_range_error_float(const char *name, RangeCheckResult result,
                           float min_value, float max_value);
int show_range_error_double(const char *name, RangeCheckResult result,
                            double min_value, double max_value);
int show_range_error_long_double(const char *name, RangeCheckResult result,
                                 long double min_value, long double max_value);

// Checking if value is in range
#define validate_range(value, min_value, max_value, is_min_included, \
                       is_max_included)                              \
  _Generic((value),                                                  \
      int: validate_range_int,                                       \
      long int: validate_range_long_int,                             \
      long long int: validate_range_long_long_int,                   \
      float: validate_range_float,                                   \
      double: validate_range_double,                                 \
      long double: validate_range_long_double)(                      \
      value, min_value, max_value, is_min_included, is_max_included)

RangeCheckResult validate_range_int(int value, int min_value, int max_value,
                                    bool is_min_included, bool is_max_included);
RangeCheckResult validate_range_long_int(long int value, long int min_value,
                                         long int max_value,
                                         bool is_min_included,
                                         bool is_max_included);
RangeCheckResult validate_range_long_long_int(long long int value,
                                              long long int min_value,
                                              long long int max_value,
                                              bool is_min_included,
                                              bool is_max_included);
RangeCheckResult validate_range_float(float value, float min_value,
                                      float max_value, bool is_min_included,
                                      bool is_max_included);
RangeCheckResult validate_range_double(double value, double min_value,
                                       double max_value, bool is_min_included,
                                       bool is_max_included);
RangeCheckResult validate_range_long_double(long double value,
                                            long double min_value,
                                            long double max_value,
                                            bool is_min_included,
                                            bool is_max_included);

// Overflow checks
#define validate_overflow(value)                      \
  _Generic((value),                                   \
      int: validate_overflow_int,                     \
      long int: validate_overflow_long_int,           \
      long long int: validate_overflow_long_long_int, \
      float: validate_overflow_float,                 \
      double: validate_overflow_double,               \
      long double: validate_overflow_long_double)(value)

RangeCheckResult validate_overflow_int(long int value);
RangeCheckResult validate_overflow_long_int(long int value);
RangeCheckResult validate_overflow_long_long_int(long long int value);
RangeCheckResult validate_overflow_float(float value);
RangeCheckResult validate_overflow_double(double value);
RangeCheckResult validate_overflow_long_double(long double value);

// Truncation
float truncate_to_precision_float(float num, int decimal_places);
double truncate_to_precision_double(double num, int decimal_places);
long double truncate_to_precision_long_double(long double num,
                                              int decimal_places);

#define print_truncated(num, decimal_places) \
  _Generic((num),                            \
      float: print_truncated_float,          \
      double: print_truncated_double,        \
      long double: print_truncated_long_double)(num, decimal_places)

void print_truncated_float(float num, int decimal_places);
void print_truncated_double(double num, int decimal_places);
void print_truncated_long_double(long double num, int decimal_places);

// Reading valid input
#define read_input_and_validate(value, full_name, short_name, max_char_count, \
                                is_restricted, max_value, min_value,          \
                                is_max_included, is_min_included)             \
  _Generic((value),                                                           \
      int *: read_int_and_validate,                                           \
      long int *: read_long_int_and_validate,                                 \
      long long int *: read_long_long_int_and_validate,                       \
      float *: read_float_and_validate,                                       \
      double *: read_double_and_validate,                                     \
      long double *: read_long_double_and_validate)(                          \
      value, full_name, short_name, max_char_count, is_restricted, max_value, \
      min_value, is_max_included, is_min_included)

int read_int_and_validate(int *value, const char *full_name,
                          const char *short_name, int max_char_count,
                          bool is_restricted, int max_value, int min_value,
                          bool is_max_included, bool is_min_included);

int read_long_int_and_validate(long int *value, const char *full_name,
                               const char *short_name, long int max_char_count,
                               bool is_restricted, long int max_value,
                               long int min_value, bool is_max_included,
                               bool is_min_included);
int read_long_long_int_and_validate(long long int *value, const char *full_name,
                                    const char *short_name,
                                    long long int max_char_count,
                                    bool is_restricted, long long int max_value,
                                    long long int min_value,
                                    bool is_max_included, bool is_min_included);
int read_float_and_validate(float *value, const char *full_name,
                            const char *short_name, int max_char_count,
                            bool is_restricted, float max_value,
                            float min_value, bool is_max_included,
                            bool is_min_included);
int read_double_and_validate(double *value, const char *full_name,
                             const char *short_name, int max_char_count,
                             bool is_restricted, double max_value,
                             double min_value, bool is_max_included,
                             bool is_min_included);
int read_long_double_and_validate(long double *value, const char *full_name,
                                  const char *short_name, int max_char_count,
                                  bool is_restricted, long double max_value,
                                  long double min_value, bool is_max_included,
                                  bool is_min_included);
#endif
