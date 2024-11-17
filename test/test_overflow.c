#include <errno.h>
#include <float.h>

#include "../src/test.h"
#include "../unity/src/unity.h"
#include "test.h"

void test_validate_overflow_int_within_range() {
  TEST_ASSERT_EQUAL(WITHIN_RANGE, validate_overflow_int(0));
  TEST_ASSERT_EQUAL(WITHIN_RANGE, validate_overflow_int(INT_MAX));
  TEST_ASSERT_EQUAL(WITHIN_RANGE, validate_overflow_int(INT_MIN));
}

void test_validate_overflow_int_above_max() {
  TEST_ASSERT_EQUAL(GREATER, validate_overflow_int((long)INT_MAX + 1));
  TEST_ASSERT_EQUAL(GREATER, validate_overflow_int((long)INT_MAX + 1000));
}

void test_validate_overflow_int_below_min() {
  TEST_ASSERT_EQUAL(LESS, validate_overflow_int((long)INT_MIN - 1));
  TEST_ASSERT_EQUAL(LESS, validate_overflow_int((long)INT_MIN - 1000));
}

// OVERFLOW LONG INT
void test_validate_overflow_long_int_within_range() {
  long int value = 12345;
  errno = 0;  // Ensure errno is clear
  TEST_ASSERT_EQUAL(WITHIN_RANGE, validate_overflow_long_int(value));
}

void test_validate_overflow_long_int_overflow() {
  long int value = LONG_MAX;
  errno = ERANGE;  // Simulate overflow condition
  TEST_ASSERT_EQUAL(GREATER, validate_overflow_long_int(value));
}

void test_validate_overflow_long_int_underflow() {
  long int value = LONG_MIN;
  errno = ERANGE;  // Simulate underflow condition
  TEST_ASSERT_EQUAL(LESS, validate_overflow_long_int(value));
}

void test_validate_overflow_long_int_boundary_values() {
  errno = 0;  // Ensure errno is clear

  // Test with LONG_MAX
  long int value = LONG_MAX;
  TEST_ASSERT_EQUAL(WITHIN_RANGE, validate_overflow_long_int(value));

  // Test with LONG_MIN
  value = LONG_MIN;
  TEST_ASSERT_EQUAL(WITHIN_RANGE, validate_overflow_long_int(value));
}

void test_validate_overflow_long_long_int_no_overflow() {
  long long int value = 1000;
  errno = 0;  // Ensure errno is clear

  TEST_ASSERT_EQUAL(WITHIN_RANGE, validate_overflow_long_long_int(value));
}

// Test for overflow greater than the maximum value
void test_validate_overflow_long_long_int_overflow_greater() {
  long long int value = LLONG_MAX;
  errno = ERANGE;  // Simulate overflow condition

  TEST_ASSERT_EQUAL(GREATER, validate_overflow_long_long_int(value));
}

// Test for overflow less than the minimum value
void test_validate_overflow_long_long_int_overflow_less() {
  long long int value = LLONG_MIN;
  errno = ERANGE;  // Simulate overflow condition

  TEST_ASSERT_EQUAL(LESS, validate_overflow_long_long_int(value));
}

// Test for no overflow but errno is set to ERANGE
void test_validate_overflow_long_long_int_no_overflow_but_errno() {
  long long int value = 1000;
  errno = ERANGE;  // Simulate overflow condition (but value is fine)

  TEST_ASSERT_EQUAL(WITHIN_RANGE, validate_overflow_long_long_int(value));
}

// Test case when errno is not set, even if value equals max or min (no
// overflow)
void test_validate_overflow_long_long_int_no_errno() {
  long long int value = LLONG_MAX;
  errno = 0;  // No overflow condition

  TEST_ASSERT_EQUAL(WITHIN_RANGE, validate_overflow_long_long_int(value));

  value = LLONG_MIN;
  TEST_ASSERT_EQUAL(WITHIN_RANGE, validate_overflow_long_long_int(value));
}

void test_validate_overflow_float_within_range() {
  float value = 10.0f;
  errno = 0;  // Reset errno
  RangeCheckResult result = validate_overflow_float(value);
  TEST_ASSERT_EQUAL(WITHIN_RANGE, result);
}

void test_validate_overflow_float_greater_equal_on_overflow() {
  float value = HUGE_VALF;  // Value representing an overflow
  errno = ERANGE;           // Set errno to simulate overflow
  RangeCheckResult result = validate_overflow_float(value);
  TEST_ASSERT_EQUAL(GREATER_EQUAL, result);
}

void test_validate_overflow_float_less_equal_on_underflow() {
  float value =
      FLT_MIN / 2.0f;  // Value less than FLT_MIN to simulate underflow
  errno = ERANGE;      // Set errno to simulate underflow
  RangeCheckResult result = validate_overflow_float(value);
  TEST_ASSERT_EQUAL(LESS_EQUAL, result);
}

void test_validate_overflow_float_no_error() {
  float value = 0.0f;
  errno = 0;  // No error
  RangeCheckResult result = validate_overflow_float(value);
  TEST_ASSERT_EQUAL(WITHIN_RANGE, result);
}

void test_validate_overflow_float_error_without_overflow_or_underflow() {
  float value = FLT_MIN;  // Valid float greater than FLT_MIN, no overflow
  errno = ERANGE;         // Set errno to simulate error state
  RangeCheckResult result = validate_overflow_float(value);
  TEST_ASSERT_EQUAL(WITHIN_RANGE, result);
}

void test_validate_overflow_float_edge_case_huge_valf() {
  float value = HUGE_VALF;  // Exactly the overflow value
  errno = ERANGE;           // Set errno to simulate overflow
  RangeCheckResult result = validate_overflow_float(value);
  TEST_ASSERT_EQUAL(GREATER_EQUAL, result);
}

void test_validate_overflow_float_edge_case_min_underflow() {
  float value = FLT_MIN / 10.0f;  // Small value smaller than FLT_MIN
  errno = ERANGE;                 // Set errno to simulate underflow
  RangeCheckResult result = validate_overflow_float(value);
  TEST_ASSERT_EQUAL(LESS_EQUAL, result);
}

void test_validate_overflow_float_no_errno() {
  float value = 1.0f;
  errno = 0;  // No error, simulate normal behavior
  RangeCheckResult result = validate_overflow_float(value);
  TEST_ASSERT_EQUAL(WITHIN_RANGE, result);
}

// DOUBLE
void test_validate_overflow_double_no_error(void) {
  errno = 0;
  double value = 1.0;
  RangeCheckResult result = validate_overflow_double(value);
  TEST_ASSERT_EQUAL(WITHIN_RANGE, result);
}

void test_validate_overflow_double_greater_equal(void) {
  errno = ERANGE;
  double value = HUGE_VAL;
  RangeCheckResult result = validate_overflow_double(value);
  TEST_ASSERT_EQUAL(GREATER_EQUAL, result);
}

void test_validate_overflow_double_less_equal(void) {
  errno = ERANGE;
  double value = DBL_MIN / 10;  // Simulate a very small underflowed value
  RangeCheckResult result = validate_overflow_double(value);
  TEST_ASSERT_EQUAL(LESS_EQUAL, result);
}

void test_validate_overflow_double_negative_greater_equal(void) {
  errno = ERANGE;
  double value = -HUGE_VAL;
  RangeCheckResult result = validate_overflow_double(value);
  TEST_ASSERT_EQUAL(GREATER_EQUAL, result);
}

void test_validate_overflow_double_negative_less_equal(void) {
  errno = ERANGE;
  double value =
      -DBL_MIN / 10;  // Simulate a very small negative underflowed value
  RangeCheckResult result = validate_overflow_double(value);
  TEST_ASSERT_EQUAL(LESS_EQUAL, result);
}

// LONG DOUBLE

void test_validate_overflow_long_double_greater_equal(void) {
  errno = ERANGE;
  long double value = HUGE_VALL;
  RangeCheckResult result = validate_overflow_long_double(value);
  TEST_ASSERT_EQUAL(GREATER_EQUAL, result);
}

void test_validate_overflow_long_double_less_equal(void) {
  errno = ERANGE;
  long double value = LDBL_MIN / 2;
  RangeCheckResult result = validate_overflow_long_double(value);
  TEST_ASSERT_EQUAL(LESS_EQUAL, result);
}

void test_validate_overflow_long_double_within_range(void) {
  errno = 0;
  long double value = 1.0L;
  RangeCheckResult result = validate_overflow_long_double(value);
  TEST_ASSERT_EQUAL(WITHIN_RANGE, result);
}

void test_overflow() {
  RUN_TEST(test_validate_overflow_int_within_range);
  RUN_TEST(test_validate_overflow_int_above_max);
  RUN_TEST(test_validate_overflow_int_below_min);

  RUN_TEST(test_validate_overflow_long_int_within_range);
  RUN_TEST(test_validate_overflow_long_int_overflow);
  RUN_TEST(test_validate_overflow_long_int_underflow);
  RUN_TEST(test_validate_overflow_long_int_boundary_values);

  RUN_TEST(test_validate_overflow_long_long_int_no_overflow);
  RUN_TEST(test_validate_overflow_long_long_int_overflow_greater);
  RUN_TEST(test_validate_overflow_long_long_int_overflow_less);
  RUN_TEST(test_validate_overflow_long_long_int_no_overflow_but_errno);
  RUN_TEST(test_validate_overflow_long_long_int_no_errno);

  RUN_TEST(test_validate_overflow_float_within_range);
  RUN_TEST(test_validate_overflow_float_greater_equal_on_overflow);
  RUN_TEST(test_validate_overflow_float_less_equal_on_underflow);
  RUN_TEST(test_validate_overflow_float_no_error);
  RUN_TEST(test_validate_overflow_float_error_without_overflow_or_underflow);
  RUN_TEST(test_validate_overflow_float_edge_case_huge_valf);
  RUN_TEST(test_validate_overflow_float_edge_case_min_underflow);
  RUN_TEST(test_validate_overflow_float_no_errno);

  RUN_TEST(test_validate_overflow_double_no_error);
  RUN_TEST(test_validate_overflow_double_greater_equal);
  RUN_TEST(test_validate_overflow_double_less_equal);
  RUN_TEST(test_validate_overflow_double_negative_greater_equal);
  RUN_TEST(test_validate_overflow_double_negative_less_equal);

  RUN_TEST(test_validate_overflow_long_double_greater_equal);
  RUN_TEST(test_validate_overflow_long_double_less_equal);
  RUN_TEST(test_validate_overflow_long_double_within_range);
}
