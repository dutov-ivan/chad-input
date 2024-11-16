#include <string.h>

#include "../src/input.h"
#include "../unity/src/unity.h"
#include "test.h"

#ifndef TOLERANCE
#define TOLERANCE 1e-20
#endif

// Test for is_long_double_in_range function
void test_is_long_double_in_range_valid_inclusive(void) {
  long double value = 5.0;
  TEST_ASSERT_TRUE(is_long_double_in_range(&value, "number", 10.0, 0.0, 1, 1));
}

void test_is_long_double_in_range_valid_exclusive(void) {
  long double value = 5.0;
  TEST_ASSERT_TRUE(is_long_double_in_range(&value, "number", 10.0, 0.0, 0, 0));
}

void test_is_long_double_in_range_high_exclusive(void) {
  long double value = 10.0;
  TEST_ASSERT_TRUE(!is_long_double_in_range(&value, "number", 10.0, 0.0, 0, 1));
}

void test_is_long_double_in_range_low_exclusive(void) {
  long double value = 0.0;
  TEST_ASSERT_TRUE(!is_long_double_in_range(&value, "number", 10.0, 0.0, 1, 0));
}

void test_is_long_double_in_range_low_inclusive(void) {
  long double value = -1.0;
  TEST_ASSERT_TRUE(!is_long_double_in_range(&value, "number", 10.0, 0.0, 1, 1));
}

// Test: Valid input (unrestricted)
void test_read_long_double_valid_input_unrestricted(void) {
  long double value;
  mock_input("123.456\n");  // Simulate valid input

  int result = read_long_double(&value, "number", "num", 50, 0, 0, 0, 0, 0);
  TEST_ASSERT_EQUAL(0, result);              // Expect success (0)
  TEST_ASSERT_EQUAL_FLOAT(123.456L, value);  // Check the correct value
}

// Test: Valid input (restricted within range, inclusive min and max)
void test_read_long_double_valid_input_restricted(void) {
  long double value;
  mock_input("0.75\n");  // Simulate valid input within range

  int result =
      read_long_double(&value, "precision", "prec", 50, 1, 1.0L, 0.5L, 1, 1);
  TEST_ASSERT_EQUAL(0, result);           // Expect success (0)
  TEST_ASSERT_EQUAL_FLOAT(0.75L, value);  // Check the correct value
}

// Test: Invalid input (non-numeric characters)
void test_read_long_double_invalid_input_non_numeric(void) {
  long double value;
  mock_input("abc\n");  // Simulate invalid input

  int result = read_long_double(&value, "number", "num", 50, 0, 0, 0, 0, 0);
  TEST_ASSERT_EQUAL(1, result);  // Expect failure (1) due to non-numeric input
}

// Test: Input too long (exceeds max_char_count)
void test_read_long_double_input_too_long(void) {
  long double value;
  char long_input[60];  // Create a string longer than max_char_count (50)
  memset(long_input, '1', 59);
  long_input[59] = '\n';

  mock_input(long_input);  // Simulate long input

  int result = read_long_double(&value, "number", "num", 50, 0, 0, 0, 0, 0);
  TEST_ASSERT_EQUAL(1, result);  // Expect failure (1) due to long input
}

// Test: Invalid range (value exceeds max_value, exclusive)
void test_read_long_double_exceeds_max_value_exclusive(void) {
  long double value;
  mock_input("1.5\n");  // Simulate input greater than max_value (1.0)

  int result =
      read_long_double(&value, "precision", "prec", 50, 1, 1.0L, 0.5L, 0, 1);
  TEST_ASSERT_EQUAL(1,
                    result);  // Expect failure (1) due to exceeding max_value
}

// Test: Invalid range (value below min_value, exclusive)
void test_read_long_double_below_min_value_exclusive(void) {
  long double value;
  mock_input("0.4\n");  // Simulate input less than min_value (0.5)

  int result =
      read_long_double(&value, "precision", "prec", 50, 1, 1.0L, 0.5L, 1, 0);
  TEST_ASSERT_EQUAL(1,
                    result);  // Expect failure (1) due to being below min_value
}

// Test: Edge case for max value (exactly max_value, exclusive)
void test_read_long_double_max_value_exclusive(void) {
  long double value;
  mock_input("1.0\n");  // Simulate input exactly at max_value

  int result =
      read_long_double(&value, "precision", "prec", 50, 1, 1.0L, 0.5L, 0, 1);
  TEST_ASSERT_EQUAL(1,
                    result);  // Expect failure (1), as max_value is exclusive
}

// Test: Edge case for min value (exactly min_value, exclusive)
void test_read_long_double_min_value_exclusive(void) {
  long double value;
  mock_input("0.5\n");  // Simulate input exactly at min_value

  int result =
      read_long_double(&value, "precision", "prec", 50, 1, 1.0L, 0.5L, 1, 0);
  TEST_ASSERT_EQUAL(1,
                    result);  // Expect failure (1), as min_value is exclusive
}

// Test: Edge case for max value (exactly max_value, inclusive)
void test_read_long_double_max_value_inclusive(void) {
  long double value;
  mock_input("1.0\n");  // Simulate input exactly at max_value

  int result =
      read_long_double(&value, "precision", "prec", 50, 1, 1.0L, 0.5L, 1, 1);
  TEST_ASSERT_EQUAL(0,
                    result);  // Expect success (0), as max_value is inclusive
}

// Test: Edge case for min value (exactly min_value, inclusive)
void test_read_long_double_min_value_inclusive(void) {
  long double value;
  mock_input("0.5\n");  // Simulate input exactly at min_value

  int result =
      read_long_double(&value, "precision", "prec", 50, 1, 1.0L, 0.5L, 1, 1);
  TEST_ASSERT_EQUAL(0,
                    result);  // Expect success (0), as min_value is inclusive
}

void test_read_long_double_overflow(void) {
  long double value;
  mock_input("1e4933\n");
  int result = read_long_double(&value, "number", "num", 10, 0, 0, 0, 0, 0);

  TEST_ASSERT_EQUAL(1, result);
}

void test_read_long_double_underflow(void) {
  long double value;
  mock_input("1e-4933\n");
  int result = read_long_double(&value, "number", "num", 10, 0, 0, 0, 0, 0);

  TEST_ASSERT_EQUAL(1, result);
}

void test_truncate_positive_numbers(void) {
  TEST_ASSERT_EQUAL_DOUBLE(
      3.1415926535L,
      truncate_long_double(3.14159265358979323846L,
                           10));  // Truncate to 10 decimal places
  TEST_ASSERT_EQUAL_DOUBLE(123.45678L,
                           truncate_long_double(123.456789012345L, 5));
}

void test_truncate_negative_numbers(void) {
  TEST_ASSERT_EQUAL_DOUBLE(
      -3.1415926535L,
      truncate_long_double(-3.14159265358979323846L,
                           10));  // Truncate to 10 decimal places
  TEST_ASSERT_EQUAL_DOUBLE(-123.45678L,
                           truncate_long_double(-123.456789012345L, 5));
}

void test_truncate_zero(void) {
  TEST_ASSERT_EQUAL_DOUBLE(0.0L, truncate_long_double(0.0L, 5));
}

void test_truncate_small_values(void) {
  TEST_ASSERT_EQUAL_DOUBLE(1e-10L,
                           truncate_long_double(1.234567890123456789e-10L, 10));
}

void test_truncate_large_values(void) {
  TEST_ASSERT_EQUAL_DOUBLE(
      1.234567890123456789e+100L,
      truncate_long_double(1.234567890123456789e+100L, 15));
}

void test_truncate_no_decimal_places(void) {
  TEST_ASSERT_EQUAL_DOUBLE(123.0L, truncate_long_double(123.456789012345L, 0));
}

void test_long_double() {
  RUN_TEST(test_is_long_double_in_range_valid_inclusive);
  RUN_TEST(test_is_long_double_in_range_valid_exclusive);
  RUN_TEST(test_is_long_double_in_range_high_exclusive);
  RUN_TEST(test_is_long_double_in_range_low_exclusive);
  RUN_TEST(test_is_long_double_in_range_low_inclusive);

  RUN_TEST(test_read_long_double_valid_input_unrestricted);
  RUN_TEST(test_read_long_double_valid_input_restricted);
  RUN_TEST(test_read_long_double_invalid_input_non_numeric);
  RUN_TEST(test_read_long_double_input_too_long);
  RUN_TEST(test_read_long_double_exceeds_max_value_exclusive);
  RUN_TEST(test_read_long_double_below_min_value_exclusive);
  RUN_TEST(test_read_long_double_max_value_exclusive);
  RUN_TEST(test_read_long_double_min_value_exclusive);
  RUN_TEST(test_read_long_double_max_value_inclusive);
  RUN_TEST(test_read_long_double_min_value_inclusive);
  RUN_TEST(test_read_long_double_overflow);
  RUN_TEST(test_read_long_double_underflow);
  RUN_TEST(test_truncate_positive_numbers);
  RUN_TEST(test_truncate_negative_numbers);
  RUN_TEST(test_truncate_zero);
  RUN_TEST(test_truncate_small_values);
  RUN_TEST(test_truncate_large_values);
  RUN_TEST(test_truncate_no_decimal_places);
}
