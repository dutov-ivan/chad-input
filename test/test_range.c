#include <float.h>

#include "../src/test.h"
#include "../unity/src/unity.h"
#include "test.h"

// INT
void test_validate_range_int_within_range_inclusive() {
  TEST_ASSERT_EQUAL(WITHIN_RANGE, validate_range_int(5, 1, 10, true, true));
}

void test_validate_range_int_within_range_exclusive() {
  TEST_ASSERT_EQUAL(WITHIN_RANGE, validate_range_int(5, 1, 10, false, false));
}

void test_validate_range_int_at_min_inclusive() {
  TEST_ASSERT_EQUAL(WITHIN_RANGE, validate_range_int(1, 1, 10, true, true));
}

void test_validate_range_int_at_min_exclusive() {
  TEST_ASSERT_EQUAL(LESS_EQUAL, validate_range_int(1, 1, 10, false, true));
}

void test_validate_range_int_below_min_inclusive() {
  TEST_ASSERT_EQUAL(LESS, validate_range_int(0, 1, 10, true, true));
}

void test_validate_range_int_below_min_exclusive() {
  TEST_ASSERT_EQUAL(LESS_EQUAL, validate_range_int(0, 1, 10, false, true));
}

void test_validate_range_int_at_max_inclusive() {
  TEST_ASSERT_EQUAL(WITHIN_RANGE, validate_range_int(10, 1, 10, true, true));
}

void test_validate_range_int_at_max_exclusive() {
  TEST_ASSERT_EQUAL(GREATER_EQUAL, validate_range_int(10, 1, 10, true, false));
}

void test_validate_range_int_above_max_inclusive() {
  TEST_ASSERT_EQUAL(GREATER, validate_range_int(11, 1, 10, true, true));
}

void test_validate_range_int_above_max_exclusive() {
  TEST_ASSERT_EQUAL(GREATER_EQUAL, validate_range_int(11, 1, 10, true, false));
}

// LONG INT
void test_validate_range_long_int_min_included() {
  TEST_ASSERT_EQUAL(WITHIN_RANGE,
                    validate_range_long_int(10, 10, 20, true, true));
  TEST_ASSERT_EQUAL(LESS, validate_range_long_int(9, 10, 20, true, true));
  TEST_ASSERT_EQUAL(WITHIN_RANGE,
                    validate_range_long_int(15, 10, 20, true, true));
}

void test_validate_range_long_int_min_excluded() {
  TEST_ASSERT_EQUAL(LESS_EQUAL,
                    validate_range_long_int(10, 10, 20, false, true));
  TEST_ASSERT_EQUAL(WITHIN_RANGE,
                    validate_range_long_int(11, 10, 20, false, true));
  TEST_ASSERT_EQUAL(LESS_EQUAL,
                    validate_range_long_int(9, 10, 20, false, true));
}

void test_validate_range_long_int_max_included() {
  TEST_ASSERT_EQUAL(WITHIN_RANGE,
                    validate_range_long_int(20, 10, 20, true, true));
  TEST_ASSERT_EQUAL(GREATER, validate_range_long_int(21, 10, 20, true, true));
  TEST_ASSERT_EQUAL(WITHIN_RANGE,
                    validate_range_long_int(15, 10, 20, true, true));
}

void test_validate_range_long_int_max_excluded() {
  TEST_ASSERT_EQUAL(GREATER_EQUAL,
                    validate_range_long_int(20, 10, 20, true, false));
  TEST_ASSERT_EQUAL(WITHIN_RANGE,
                    validate_range_long_int(19, 10, 20, true, false));
  TEST_ASSERT_EQUAL(GREATER_EQUAL,
                    validate_range_long_int(21, 10, 20, true, false));
}

void test_validate_range_long_int_full_inclusive() {
  TEST_ASSERT_EQUAL(WITHIN_RANGE,
                    validate_range_long_int(10, 10, 20, true, true));
  TEST_ASSERT_EQUAL(WITHIN_RANGE,
                    validate_range_long_int(20, 10, 20, true, true));
  TEST_ASSERT_EQUAL(WITHIN_RANGE,
                    validate_range_long_int(15, 10, 20, true, true));
}

void test_validate_range_long_int_full_exclusive() {
  TEST_ASSERT_EQUAL(LESS_EQUAL,
                    validate_range_long_int(10, 10, 20, false, false));
  TEST_ASSERT_EQUAL(GREATER_EQUAL,
                    validate_range_long_int(20, 10, 20, false, false));
  TEST_ASSERT_EQUAL(WITHIN_RANGE,
                    validate_range_long_int(15, 10, 20, false, false));
}

void test_validate_range_long_int_edge_cases() {
  TEST_ASSERT_EQUAL(LESS,
                    validate_range_long_int(LONG_MIN, -100, 100, true, true));
  TEST_ASSERT_EQUAL(WITHIN_RANGE,
                    validate_range_long_int(0, -100, 100, true, true));
  TEST_ASSERT_EQUAL(GREATER,
                    validate_range_long_int(LONG_MAX, -100, 100, true, true));
}

void test_validate_range_long_int_large_values() {
  TEST_ASSERT_EQUAL(WITHIN_RANGE,
                    validate_range_long_int(999999999999, 999999999998,
                                            999999999999, true, true));
  TEST_ASSERT_EQUAL(LESS, validate_range_long_int(999999999997, 999999999998,
                                                  999999999999, true, true));
  TEST_ASSERT_EQUAL(GREATER,
                    validate_range_long_int(1000000000000, 999999999998,
                                            999999999999, true, true));
}

void test_validate_range_long_int_same_min_max() {
  TEST_ASSERT_EQUAL(WITHIN_RANGE,
                    validate_range_long_int(100, 100, 100, true, true));
  TEST_ASSERT_EQUAL(LESS_EQUAL,
                    validate_range_long_int(99, 100, 100, false, true));
  TEST_ASSERT_EQUAL(GREATER_EQUAL,
                    validate_range_long_int(101, 100, 100, true, false));
}

void test_validate_range_long_int_negative_ranges() {
  TEST_ASSERT_EQUAL(WITHIN_RANGE,
                    validate_range_long_int(-50, -100, -10, true, true));
  TEST_ASSERT_EQUAL(LESS, validate_range_long_int(-101, -100, -10, true, true));
  TEST_ASSERT_EQUAL(GREATER,
                    validate_range_long_int(-5, -100, -10, true, true));
}

// LONG LONG INT

void test_validate_range_long_long_int_less_than_min() {
  long long int value = -5;
  long long int min_value = 0;
  long long int max_value = 10;
  bool is_min_included = true;
  bool is_max_included = true;

  TEST_ASSERT_EQUAL(
      LESS, validate_range_long_long_int(value, min_value, max_value,
                                         is_min_included, is_max_included));
}

void test_validate_range_long_long_int_equal_to_min() {
  long long int value = 0;
  long long int min_value = 0;
  long long int max_value = 10;

  // Case: is_min_included == true
  TEST_ASSERT_EQUAL(WITHIN_RANGE, validate_range_long_long_int(
                                      value, min_value, max_value, true, true));

  // Case: is_min_included == false
  TEST_ASSERT_EQUAL(LESS_EQUAL, validate_range_long_long_int(
                                    value, min_value, max_value, false, true));
}

void test_validate_range_long_long_int_greater_than_max() {
  long long int value = 15;
  long long int min_value = 0;
  long long int max_value = 10;
  bool is_min_included = true;
  bool is_max_included = true;

  TEST_ASSERT_EQUAL(
      GREATER, validate_range_long_long_int(value, min_value, max_value,
                                            is_min_included, is_max_included));
}

void test_validate_range_long_long_int_equal_to_max() {
  long long int value = 10;
  long long int min_value = 0;
  long long int max_value = 10;

  // Case: is_max_included == true
  TEST_ASSERT_EQUAL(WITHIN_RANGE, validate_range_long_long_int(
                                      value, min_value, max_value, true, true));

  // Case: is_max_included == false
  TEST_ASSERT_EQUAL(
      GREATER_EQUAL,
      validate_range_long_long_int(value, min_value, max_value, true, false));
}

void test_validate_range_long_long_int_within_range() {
  long long int value = 5;
  long long int min_value = 0;
  long long int max_value = 10;
  bool is_min_included = true;
  bool is_max_included = true;

  TEST_ASSERT_EQUAL(WITHIN_RANGE, validate_range_long_long_int(
                                      value, min_value, max_value,
                                      is_min_included, is_max_included));
}

// Test cases
void test_validate_range_float_within_range() {
  float value = 5.0f;
  float min_value = 3.0f;
  float max_value = 7.0f;
  RangeCheckResult result =
      validate_range_float(value, min_value, max_value, true, true);
  TEST_ASSERT_EQUAL(WITHIN_RANGE, result);
}

void test_validate_range_float_less_than_min() {
  float value = 2.9f;  // Slightly less than the min_value (3.0f) with TOLERANCE
  float min_value = 3.0f;
  float max_value = 7.0f;
  RangeCheckResult result =
      validate_range_float(value, min_value, max_value, true, true);
  TEST_ASSERT_EQUAL(LESS, result);
}

void test_validate_range_float_greater_than_max() {
  float value = 7.1f;  // Slightly more than the max_value (7.0f) with TOLERANCE
  float min_value = 3.0f;
  float max_value = 7.0f;
  RangeCheckResult result =
      validate_range_float(value, min_value, max_value, true, true);
  TEST_ASSERT_EQUAL(GREATER, result);
}

void test_validate_range_float_less_equal_min_not_included() {
  float value = 3.0f;  // Equal to min_value, but min is not included
  float min_value = 3.0f;
  float max_value = 7.0f;
  RangeCheckResult result =
      validate_range_float(value, min_value, max_value, false, true);
  TEST_ASSERT_EQUAL(LESS_EQUAL, result);
}

void test_validate_range_float_greater_equal_max_not_included() {
  float value = 7.0f;  // Equal to max_value, but max is not included
  float min_value = 3.0f;
  float max_value = 7.0f;
  RangeCheckResult result =
      validate_range_float(value, min_value, max_value, true, false);
  TEST_ASSERT_EQUAL(GREATER_EQUAL, result);
}

void test_validate_range_float_edge_case_min_included() {
  float value = 3.0f;  // Exactly at min_value, included
  float min_value = 3.0f;
  float max_value = 7.0f;
  RangeCheckResult result =
      validate_range_float(value, min_value, max_value, true, true);
  TEST_ASSERT_EQUAL(WITHIN_RANGE, result);
}

void test_validate_range_float_edge_case_max_included() {
  float value = 7.0f;  // Exactly at max_value, included
  float min_value = 3.0f;
  float max_value = 7.0f;
  RangeCheckResult result =
      validate_range_float(value, min_value, max_value, true, true);
  TEST_ASSERT_EQUAL(WITHIN_RANGE, result);
}

void test_validate_range_float_tolerance_edge() {
  float value = 3.0f + FLT_EPSILON;  // Slightly above min_value with tolerance
  float min_value = 3.0f;
  float max_value = 7.0f;
  RangeCheckResult result =
      validate_range_float(value, min_value, max_value, true, true);
  TEST_ASSERT_EQUAL(WITHIN_RANGE, result);
}

void test_validate_range_float_tolerance_below_max() {
  float value = 7.0f - FLT_EPSILON;  // Slightly below max_value with tolerance
  float min_value = 3.0f;
  float max_value = 7.0f;
  RangeCheckResult result =
      validate_range_float(value, min_value, max_value, true, true);
  TEST_ASSERT_EQUAL(WITHIN_RANGE, result);
}

// DOUBLE

void test_validate_range_double_within_range(void) {
  RangeCheckResult result = validate_range_double(15.5, 10.0, 20.0, true, true);
  TEST_ASSERT_EQUAL(WITHIN_RANGE, result);
}

void test_validate_range_double_below_min_inclusive(void) {
  RangeCheckResult result = validate_range_double(9.9, 10.0, 20.0, true, true);
  TEST_ASSERT_EQUAL(LESS, result);
}

void test_validate_range_double_below_min_exclusive(void) {
  RangeCheckResult result =
      validate_range_double(10.0, 10.0, 20.0, false, true);
  TEST_ASSERT_EQUAL(LESS_EQUAL, result);
}

void test_validate_range_double_above_max_inclusive(void) {
  RangeCheckResult result = validate_range_double(20.1, 10.0, 20.0, true, true);
  TEST_ASSERT_EQUAL(GREATER, result);
}

void test_validate_range_double_above_max_exclusive(void) {
  RangeCheckResult result =
      validate_range_double(20.0, 10.0, 20.0, true, false);
  TEST_ASSERT_EQUAL(GREATER_EQUAL, result);
}

void test_validate_range_double_on_min_inclusive(void) {
  RangeCheckResult result = validate_range_double(10.0, 10.0, 20.0, true, true);
  TEST_ASSERT_EQUAL(WITHIN_RANGE, result);
}

void test_validate_range_double_on_max_inclusive(void) {
  RangeCheckResult result = validate_range_double(20.0, 10.0, 20.0, true, true);
  TEST_ASSERT_EQUAL(WITHIN_RANGE, result);
}

void test_validate_range_double_on_min_exclusive(void) {
  RangeCheckResult result =
      validate_range_double(10.0, 10.0, 20.0, false, true);
  TEST_ASSERT_EQUAL(LESS_EQUAL, result);
}

void test_validate_range_double_on_max_exclusive(void) {
  RangeCheckResult result =
      validate_range_double(20.0, 10.0, 20.0, true, false);
  TEST_ASSERT_EQUAL(GREATER_EQUAL, result);
}

// LONG DOUBLE

void test_validate_range_long_double_within_range(void) {
  long double value = 5.0L, min_value = 1.0L, max_value = 10.0L;
  RangeCheckResult result =
      validate_range_long_double(value, min_value, max_value, true, true);
  TEST_ASSERT_EQUAL(WITHIN_RANGE, result);
}

void test_validate_range_long_double_less_than_min_inclusive(void) {
  long double value = 0.999L, min_value = 1.0L, max_value = 10.0L;
  RangeCheckResult result =
      validate_range_long_double(value, min_value, max_value, true, true);
  TEST_ASSERT_EQUAL(LESS, result);
}

void test_validate_range_long_double_equal_to_min_inclusive(void) {
  long double value = 1.0L, min_value = 1.0L, max_value = 10.0L;
  RangeCheckResult result =
      validate_range_long_double(value, min_value, max_value, true, true);
  TEST_ASSERT_EQUAL(WITHIN_RANGE, result);
}

void test_validate_range_long_double_equal_to_min_exclusive(void) {
  long double value = 1.0L, min_value = 1.0L, max_value = 10.0L;
  RangeCheckResult result =
      validate_range_long_double(value, min_value, max_value, false, true);
  TEST_ASSERT_EQUAL(LESS_EQUAL, result);
}

void test_validate_range_long_double_greater_than_max_inclusive(void) {
  long double value = 10.001L, min_value = 1.0L, max_value = 10.0L;
  RangeCheckResult result =
      validate_range_long_double(value, min_value, max_value, true, true);
  TEST_ASSERT_EQUAL(GREATER, result);
}

void test_validate_range_long_double_equal_to_max_inclusive(void) {
  long double value = 10.0L, min_value = 1.0L, max_value = 10.0L;
  RangeCheckResult result =
      validate_range_long_double(value, min_value, max_value, true, true);
  TEST_ASSERT_EQUAL(WITHIN_RANGE, result);
}

void test_validate_range_long_double_equal_to_max_exclusive(void) {
  long double value = 10.0L, min_value = 1.0L, max_value = 10.0L;
  RangeCheckResult result =
      validate_range_long_double(value, min_value, max_value, true, false);
  TEST_ASSERT_EQUAL(GREATER_EQUAL, result);
}

void test_range() {
  RUN_TEST(test_validate_range_int_within_range_inclusive);
  RUN_TEST(test_validate_range_int_within_range_exclusive);
  RUN_TEST(test_validate_range_int_at_min_inclusive);
  RUN_TEST(test_validate_range_int_at_min_exclusive);
  RUN_TEST(test_validate_range_int_below_min_inclusive);
  RUN_TEST(test_validate_range_int_below_min_exclusive);
  RUN_TEST(test_validate_range_int_at_max_inclusive);
  RUN_TEST(test_validate_range_int_at_max_exclusive);
  RUN_TEST(test_validate_range_int_above_max_inclusive);
  RUN_TEST(test_validate_range_int_above_max_exclusive);

  RUN_TEST(test_validate_range_long_int_min_included);
  RUN_TEST(test_validate_range_long_int_min_excluded);
  RUN_TEST(test_validate_range_long_int_max_included);
  RUN_TEST(test_validate_range_long_int_max_excluded);
  RUN_TEST(test_validate_range_long_int_full_inclusive);
  RUN_TEST(test_validate_range_long_int_full_exclusive);
  RUN_TEST(test_validate_range_long_int_edge_cases);
  RUN_TEST(test_validate_range_long_int_large_values);
  RUN_TEST(test_validate_range_long_int_same_min_max);
  RUN_TEST(test_validate_range_long_int_negative_ranges);

  RUN_TEST(test_validate_range_long_long_int_less_than_min);
  RUN_TEST(test_validate_range_long_long_int_equal_to_min);
  RUN_TEST(test_validate_range_long_long_int_greater_than_max);
  RUN_TEST(test_validate_range_long_long_int_equal_to_max);
  RUN_TEST(test_validate_range_long_long_int_within_range);

  RUN_TEST(test_validate_range_float_within_range);
  RUN_TEST(test_validate_range_float_less_than_min);
  RUN_TEST(test_validate_range_float_greater_than_max);
  RUN_TEST(test_validate_range_float_less_equal_min_not_included);
  RUN_TEST(test_validate_range_float_greater_equal_max_not_included);
  RUN_TEST(test_validate_range_float_edge_case_min_included);
  RUN_TEST(test_validate_range_float_edge_case_max_included);
  RUN_TEST(test_validate_range_float_tolerance_edge);
  RUN_TEST(test_validate_range_float_tolerance_below_max);

  RUN_TEST(test_validate_range_double_within_range);
  RUN_TEST(test_validate_range_double_below_min_inclusive);
  RUN_TEST(test_validate_range_double_below_min_exclusive);
  RUN_TEST(test_validate_range_double_above_max_inclusive);
  RUN_TEST(test_validate_range_double_above_max_exclusive);
  RUN_TEST(test_validate_range_double_on_min_inclusive);
  RUN_TEST(test_validate_range_double_on_max_inclusive);
  RUN_TEST(test_validate_range_double_on_min_exclusive);
  RUN_TEST(test_validate_range_double_on_max_exclusive);

  RUN_TEST(test_validate_range_long_double_within_range);
  RUN_TEST(test_validate_range_long_double_less_than_min_inclusive);
  RUN_TEST(test_validate_range_long_double_equal_to_min_inclusive);
  RUN_TEST(test_validate_range_long_double_equal_to_min_exclusive);
  RUN_TEST(test_validate_range_long_double_greater_than_max_inclusive);
  RUN_TEST(test_validate_range_long_double_equal_to_max_inclusive);
  RUN_TEST(test_validate_range_long_double_equal_to_max_exclusive);
}
