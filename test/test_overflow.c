#include <errno.h>

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
}
