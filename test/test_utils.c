#include <stdlib.h>

#include "../src/test.h"
#include "../unity/src/unity.h"
#include "test.h"

#define SUCCESS 0
#define ERROR 1

// REPLACE COMMAS
void test_replace_commas_with_dots_no_commas() {
  char input[] = "Hello World";
  replace_commas_with_dots(input);
  TEST_ASSERT_EQUAL_STRING("Hello World", input);
}

void test_replace_commas_with_dots_one_comma() {
  char input[] = "Hello, World";
  replace_commas_with_dots(input);
  TEST_ASSERT_EQUAL_STRING("Hello. World", input);
}

void test_replace_commas_with_dots_multiple_commas() {
  char input[] = "1,234,567,890";
  replace_commas_with_dots(input);
  TEST_ASSERT_EQUAL_STRING("1.234.567.890", input);
}

void test_replace_commas_with_dots_empty_string() {
  char input[] = "";
  replace_commas_with_dots(input);
  TEST_ASSERT_EQUAL_STRING("", input);
}

void test_replace_commas_with_dots_all_commas() {
  char input[] = ",,,,,";
  replace_commas_with_dots(input);
  TEST_ASSERT_EQUAL_STRING(".....", input);
}

void test_replace_commas_with_dots_no_alteration() {
  char input[] = "123.456";
  replace_commas_with_dots(input);
  TEST_ASSERT_EQUAL_STRING("123.456", input);
}

// REPEAT

void test_ask_repeat_success() {
  simulate_stdin("+\n");
  TEST_ASSERT_EQUAL(SUCCESS, ask_repeat());
}

void test_ask_repeat_error_non_plus() {
  simulate_stdin("n\n");
  TEST_ASSERT_EQUAL(ERROR, ask_repeat());
}

void test_ask_repeat_error_empty_input() {
  simulate_stdin("\n");
  TEST_ASSERT_EQUAL(ERROR, ask_repeat());
}

void test_ask_repeat_error_long_input() {
  simulate_stdin("+abc\n");
  TEST_ASSERT_EQUAL(ERROR, ask_repeat());
}

void test_ask_repeat_error_no_newline() {
  simulate_stdin("+");
  TEST_ASSERT_EQUAL(ERROR, ask_repeat());
}

// FLOATING INPUT
void test_is_input_floating_point_dot() {
  char input[] = "123.456";
  TEST_ASSERT_TRUE(is_input_floating_point(input));
}

void test_is_input_floating_point_comma() {
  char input[] = "123,456";
  TEST_ASSERT_TRUE(is_input_floating_point(input));
}

void test_is_input_floating_point_exponent_lowercase() {
  char input[] = "1e10";
  TEST_ASSERT_TRUE(is_input_floating_point(input));
}

void test_is_input_floating_point_exponent_uppercase() {
  char input[] = "1E10";
  TEST_ASSERT_TRUE(is_input_floating_point(input));
}

void test_is_input_floating_point_no_floating_point_character() {
  char input[] = "123456";
  TEST_ASSERT_FALSE(is_input_floating_point(input));
}

void test_is_input_floating_point_empty_string() {
  char input[] = "";
  TEST_ASSERT_FALSE(is_input_floating_point(input));
}

void test_is_input_floating_point_multiple_characters() {
  char input[] = "1.2e3";
  TEST_ASSERT_TRUE(is_input_floating_point(input));
}

void test_is_input_floating_point_only_exponent_symbol() {
  char input[] = "E";
  TEST_ASSERT_TRUE(is_input_floating_point(input));
}

void test_is_input_floating_point_special_symbols() {
  char input[] = "!@#$%^&*()";
  TEST_ASSERT_FALSE(is_input_floating_point(input));
}

void test_is_input_floating_point_leading_space() {
  char input[] = "   3.14";
  TEST_ASSERT_TRUE(is_input_floating_point(input));
}

// INPUT PRECISE
void test_is_numeric_input_precise_within_limit() {
  const char *input = "123.45";
  int max_digits = 5;
  TEST_ASSERT_TRUE(is_numeric_input_precise(input, max_digits));
}

void test_is_numeric_input_precise_exceeds_limit() {
  const char *input = "123.456";
  int max_digits = 5;
  TEST_ASSERT_FALSE(is_numeric_input_precise(input, max_digits));
}

void test_is_numeric_input_precise_no_digits() {
  const char *input = "abcdef";
  int max_digits = 3;
  TEST_ASSERT_TRUE(is_numeric_input_precise(input, max_digits));
}

void test_is_numeric_input_precise_empty_string() {
  const char *input = "";
  int max_digits = 3;
  TEST_ASSERT_TRUE(is_numeric_input_precise(input, max_digits));
}

void test_is_numeric_input_precise_only_digits() {
  const char *input = "123456";
  int max_digits = 6;
  TEST_ASSERT_TRUE(is_numeric_input_precise(input, max_digits));
}

void test_is_numeric_input_precise_only_digits_exceeds_limit() {
  const char *input = "1234567";
  int max_digits = 6;
  TEST_ASSERT_FALSE(is_numeric_input_precise(input, max_digits));
}

void test_is_numeric_input_precise_with_leading_zeros() {
  const char *input = "00001234";
  int max_digits = 8;
  TEST_ASSERT_TRUE(is_numeric_input_precise(input, max_digits));
}

void test_is_numeric_input_precise_special_characters() {
  const char *input = "12.3e45";
  int max_digits = 4;
  TEST_ASSERT_FALSE(is_numeric_input_precise(input, max_digits));
}

void test_is_numeric_input_precise_zero_digits_allowed() {
  const char *input = "123";
  int max_digits = 0;
  TEST_ASSERT_FALSE(is_numeric_input_precise(input, max_digits));
}

// INPUT LENGTH
void test_is_input_within_length_correct_ending_newline() {
  const char *input = "Hello\n";
  TEST_ASSERT_TRUE(is_input_within_length(input));
}

void test_is_input_within_length_no_newline() {
  const char *input = "Hello";
  TEST_ASSERT_FALSE(is_input_within_length(input));
}

void test_is_input_within_length_empty_string() {
  const char *input = "";
  TEST_ASSERT_FALSE(is_input_within_length(input));
}

void test_is_input_within_length_newline_only() {
  const char *input = "\n";
  TEST_ASSERT_TRUE(is_input_within_length(input));
}

void test_is_input_within_length_multiple_newlines() {
  const char *input = "Hello\n\n";
  TEST_ASSERT_TRUE(is_input_within_length(input));
}

void test_is_input_within_length_with_spaces() {
  const char *input = "Hello World \n";
  TEST_ASSERT_TRUE(is_input_within_length(input));
}

void test_is_input_within_length_with_trailing_space() {
  const char *input = "Hello \n";
  TEST_ASSERT_TRUE(is_input_within_length(input));
}

void test_is_input_within_length_with_special_characters() {
  const char *input = "!@#$%^&*\n";
  TEST_ASSERT_TRUE(is_input_within_length(input));
}

void test_is_input_within_length_long_string_without_newline() {
  const char *input =
      "This is a very long string without a newline character at the end";
  TEST_ASSERT_FALSE(is_input_within_length(input));
}

void test_is_input_within_length_long_string_with_newline() {
  const char *input =
      "This is a very long string with a newline character at the end\n";
  TEST_ASSERT_TRUE(is_input_within_length(input));
}

// NUMBER CONVERSION
void test_is_input_number_after_conversion_valid_number() {
  const char *input = "123\n";
  char *endptr;
  strtol(input, &endptr, 10);  // Valid number conversion
  TEST_ASSERT_TRUE(is_input_number_after_conversion(endptr, input));
}

void test_is_input_number_after_conversion_partial_conversion() {
  const char *input = "123abc\n";
  char *endptr;
  strtol(input, &endptr, 10);  // Stops conversion at non-numeric characters
  TEST_ASSERT_FALSE(is_input_number_after_conversion(endptr, input));
}

void test_is_input_number_after_conversion_no_conversion() {
  const char *input = "abc\n";
  char *endptr;
  strtol(input, &endptr, 10);  // No conversion happens
  TEST_ASSERT_FALSE(is_input_number_after_conversion(endptr, input));
}

void test_is_input_number_after_conversion_empty_string() {
  const char *input = "\n";
  char *endptr;
  strtol(input, &endptr, 10);  // No conversion happens
  TEST_ASSERT_FALSE(is_input_number_after_conversion(endptr, input));
}

void test_is_input_number_after_conversion_negative_number() {
  const char *input = "-456\n";
  char *endptr;
  strtol(input, &endptr, 10);  // Valid negative number conversion
  TEST_ASSERT_TRUE(is_input_number_after_conversion(endptr, input));
}

void test_is_input_number_after_conversion_leading_whitespace() {
  const char *input = "   789\n";
  char *endptr;
  strtol(input, &endptr, 10);  // Skips leading whitespace for conversion
  TEST_ASSERT_TRUE(is_input_number_after_conversion(endptr, input));
}

void test_is_input_number_after_conversion_only_whitespace() {
  const char *input = "   \n";
  char *endptr;
  strtol(input, &endptr, 10);  // No conversion happens
  TEST_ASSERT_FALSE(is_input_number_after_conversion(endptr, input));
}

void test_is_input_number_after_conversion_large_number() {
  const char *input = "9876543210\n";
  char *endptr;
  strtol(input, &endptr, 10);  // Successfully converts large number
  TEST_ASSERT_TRUE(is_input_number_after_conversion(endptr, input));
}

void test_is_input_number_after_conversion_trailing_space_after_number() {
  const char *input = "123 \n";
  char *endptr;
  strtol(input, &endptr, 10);  // Stops conversion at space
  TEST_ASSERT_FALSE(is_input_number_after_conversion(endptr, input));
}

void test_utils(void) {
  RUN_TEST(test_replace_commas_with_dots_no_commas);
  RUN_TEST(test_replace_commas_with_dots_one_comma);
  RUN_TEST(test_replace_commas_with_dots_multiple_commas);
  RUN_TEST(test_replace_commas_with_dots_empty_string);
  RUN_TEST(test_replace_commas_with_dots_all_commas);
  RUN_TEST(test_replace_commas_with_dots_no_alteration);

  RUN_TEST(test_ask_repeat_success);
  RUN_TEST(test_ask_repeat_error_non_plus);
  RUN_TEST(test_ask_repeat_error_empty_input);
  RUN_TEST(test_ask_repeat_error_long_input);
  RUN_TEST(test_ask_repeat_error_no_newline);

  RUN_TEST(test_is_input_floating_point_dot);
  RUN_TEST(test_is_input_floating_point_comma);
  RUN_TEST(test_is_input_floating_point_exponent_lowercase);
  RUN_TEST(test_is_input_floating_point_exponent_uppercase);
  RUN_TEST(test_is_input_floating_point_no_floating_point_character);
  RUN_TEST(test_is_input_floating_point_empty_string);
  RUN_TEST(test_is_input_floating_point_multiple_characters);
  RUN_TEST(test_is_input_floating_point_only_exponent_symbol);
  RUN_TEST(test_is_input_floating_point_special_symbols);
  RUN_TEST(test_is_input_floating_point_leading_space);

  RUN_TEST(test_is_numeric_input_precise_within_limit);
  RUN_TEST(test_is_numeric_input_precise_exceeds_limit);
  RUN_TEST(test_is_numeric_input_precise_no_digits);
  RUN_TEST(test_is_numeric_input_precise_empty_string);
  RUN_TEST(test_is_numeric_input_precise_only_digits);
  RUN_TEST(test_is_numeric_input_precise_only_digits_exceeds_limit);
  RUN_TEST(test_is_numeric_input_precise_with_leading_zeros);
  RUN_TEST(test_is_numeric_input_precise_special_characters);
  RUN_TEST(test_is_numeric_input_precise_zero_digits_allowed);

  RUN_TEST(test_is_input_within_length_correct_ending_newline);
  RUN_TEST(test_is_input_within_length_no_newline);
  RUN_TEST(test_is_input_within_length_empty_string);
  RUN_TEST(test_is_input_within_length_newline_only);
  RUN_TEST(test_is_input_within_length_multiple_newlines);
  RUN_TEST(test_is_input_within_length_with_spaces);
  RUN_TEST(test_is_input_within_length_with_trailing_space);
  RUN_TEST(test_is_input_within_length_with_special_characters);
  RUN_TEST(test_is_input_within_length_long_string_without_newline);
  RUN_TEST(test_is_input_within_length_long_string_with_newline);

  RUN_TEST(test_is_input_number_after_conversion_valid_number);
  RUN_TEST(test_is_input_number_after_conversion_partial_conversion);
  RUN_TEST(test_is_input_number_after_conversion_no_conversion);
  RUN_TEST(test_is_input_number_after_conversion_empty_string);
  RUN_TEST(test_is_input_number_after_conversion_negative_number);
  RUN_TEST(test_is_input_number_after_conversion_leading_whitespace);
  RUN_TEST(test_is_input_number_after_conversion_only_whitespace);
  RUN_TEST(test_is_input_number_after_conversion_large_number);
  RUN_TEST(test_is_input_number_after_conversion_trailing_space_after_number);
}
