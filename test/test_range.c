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
}
