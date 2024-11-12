#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>

#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define RESET "\033[0m"

#define SUCCESS 0
#define ERROR 1
#define PIPE 1
#define TOLERANCE 1e-7

void clear_input();
bool is_input_floating_point(char *str);
int request_repeat();
int display_error(const char *format, ...)
    __attribute__((format(printf, 1, 2)));
int display_warning(const char *format, ...)
    __attribute__((format(printf, 1, 2)));
int display_success(const char *format, ...)
    __attribute__((format(printf, 1, 2)));

void replace_commas_with_dots(char *string);
bool is_input_precise(const char *input, int max_significant_digits);

int read_int(int *value, const char *full_name, const char *short_name,
             int max_char_count, int is_restricted, int max_value,
             int min_value, int is_max_included, int is_min_included);

bool is_input_length_valid(char *input, int max_char_count, const char *name);
int read_long_double(long double *value, const char *full_name,
                     const char *short_name, int max_char_count,
                     bool is_restricted, long double max_value,
                     long double min_value, bool is_max_included,
                     bool is_min_included);
bool is_int_in_range(int *value, const char *name, int max_value, int min_value,
                     bool is_max_included, bool is_min_included);

bool is_long_double_in_range(long double *value, const char *name,
                             long double max_value, long double min_value,
                             bool is_max_included, bool is_min_included);
int read_input(char *input, int max_char_count, const char *name);
#endif
