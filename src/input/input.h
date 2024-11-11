#ifndef INPUT_H
#define INPUT_H

#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define RESET "\033[0m"
#define SUCCESS 0
#define ERROR 1
#define TOLERANCE 1e-7

void clear_input();
int request_repeat();
int display_error(const char *format, ...)
    __attribute__((format(printf, 1, 2)));
int display_warning(const char *format, ...)
    __attribute__((format(printf, 1, 2)));
int display_success(const char *format, ...)
    __attribute__((format(printf, 1, 2)));

void replace_commas_with_dots(char *string);
int validate_input_precision(const char *input, int max_significant_digits);

#define read_input(value, full_name, short_name, max_char_count,              \
                   is_restricted, max_value, min_value, is_max_included,      \
                   is_min_included)                                           \
  _Generic((value), long double *: read_long_double, int *: read_int)(        \
      value, full_name, short_name, max_char_count, is_restricted, max_value, \
      min_value, is_max_included, is_min_included)

int read_int(int *value, const char *full_name, const char *short_name,
             int max_char_count, int is_restricted, int max_value,
             int min_value, int is_max_included, int is_min_included);

int read_long_double(long double *value, const char *full_name,
                     const char *short_name, int max_char_count,
                     int is_restricted, long double max_value,
                     long double min_value, int is_max_included,
                     int is_min_included);

#define check_meets_restrictions(value, name, max_value, min_value,           \
                                 is_max_included, is_min_included)            \
  _Generic((value),                                                           \
      long double *: check_long_double_meets_restrictions,                    \
      int *: check_int_meets_restrictions)(value, name, max_value, min_value, \
                                           is_max_included, is_min_included)

int check_long_double_meets_restrictions(long double *value, const char *name,
                                         long double max_value,
                                         long double min_value,
                                         int is_max_included,
                                         int is_min_included);

int check_int_meets_restrictions(int *value, const char *name, int max_value,
                                 int min_value, int is_max_included,
                                 int is_min_included);

int check_long_double_flow(long double *value, const char *name);
int check_long_int_flow(long int *value, const char *name);
int check_if_floating_point(char *str);

#endif
