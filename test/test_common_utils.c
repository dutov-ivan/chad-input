#include "../src/input.h"
#include "../unity/src/unity.h"
#include "test.h"

void test_replace_commas_with_dots_basic(void) {
  char input[] = "1,234.56";
  replace_commas_with_dots(input);
  TEST_ASSERT_EQUAL_STRING("1.234.56", input);
}

void test_replace_commas_with_dots_no_commas(void) {
  char input[] = "123.456";
  replace_commas_with_dots(input);
  TEST_ASSERT_EQUAL_STRING("123.456", input);
}

void test_replace_commas_with_dots_multiple_commas(void) {
  char input[] = "1,23,45,67.89";
  replace_commas_with_dots(input);
  TEST_ASSERT_EQUAL_STRING("1.23.45.67.89", input);
}

void test_is_input_precise_valid_input(void) {
  TEST_ASSERT_TRUE(is_input_precise("12345.678", 15));
}

void test_is_input_precise_exceeding_digits(void) {
  TEST_ASSERT_TRUE(!is_input_precise("1234567890123456", 15));
}

void test_is_input_precise_zero_digits(void) {
  TEST_ASSERT_TRUE(!is_input_precise("0.0000000", 0));
}

void test_common_utils() {
  RUN_TEST(test_replace_commas_with_dots_basic);
  RUN_TEST(test_replace_commas_with_dots_no_commas);
  RUN_TEST(test_replace_commas_with_dots_multiple_commas);

  RUN_TEST(test_is_input_precise_valid_input);
  RUN_TEST(test_is_input_precise_exceeding_digits);
  RUN_TEST(test_is_input_precise_zero_digits);
}
