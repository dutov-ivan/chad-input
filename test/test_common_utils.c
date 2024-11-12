#include "../src/input.h"
#include "../unity/src/unity.h"
#include "test_input.h"

void test_replace_commas_with_dots_basic(void) {
  char input[] = "1,234.56";
  replace_commas_with_dots(input);
  TEST_ASSERT_EQUAL_STRING("1.234.56", input);  // Expect "1.234.56"
}

// Test: No commas in the input string
void test_replace_commas_with_dots_no_commas(void) {
  char input[] = "123.456";
  replace_commas_with_dots(input);
  TEST_ASSERT_EQUAL_STRING("123.456", input);  // Expect "123.456"
}

// Test: Multiple commas in the input string
void test_replace_commas_with_dots_multiple_commas(void) {
  char input[] = "1,23,45,67.89";
  replace_commas_with_dots(input);
  TEST_ASSERT_EQUAL_STRING("1.23.45.67.89", input);  // Expect "1.23.45.67.89"
}

// Test: Valid input (within limit)
void test_validate_input_precision_valid_input(void) {
  int result = validate_input_precision("12345.678", 15);
  TEST_ASSERT_EQUAL(0, result);  // Expect success (0)
}

// Test: Exceeding significant digits
void test_validate_input_precision_exceeding_digits(void) {
  int result = validate_input_precision("1234567890123456", 15);
  TEST_ASSERT_EQUAL(1, result);  // Expect failure (1)
}

// Test: Input with zero significant digits
void test_validate_input_precision_zero_digits(void) {
  int result = validate_input_precision("0.0000000", 0);
  TEST_ASSERT_EQUAL(1, result);  // Expect failure (1)
}

// Test: Input with no digits
void test_validate_input_precision_no_digits(void) {
  int result = validate_input_precision("....", 15);
  TEST_ASSERT_EQUAL(0, result);  // Expect success (0)
}

void test_common_utils() {
  RUN_TEST(test_replace_commas_with_dots_basic);
  RUN_TEST(test_replace_commas_with_dots_no_commas);
  RUN_TEST(test_replace_commas_with_dots_multiple_commas);

  RUN_TEST(test_validate_input_precision_valid_input);
  RUN_TEST(test_validate_input_precision_exceeding_digits);
  RUN_TEST(test_validate_input_precision_zero_digits);
  RUN_TEST(test_validate_input_precision_no_digits);
}
