#include "../src/input.h"
#include "../unity/src/unity.h"
#include "test.h"

// Test for is_int_in_range function
void test_is_int_in_range_valid_inclusive(void) {
  int value = 5;
  TEST_ASSERT_TRUE(is_int_in_range(&value, "number", 10, 0, 1, 1));
}

void test_is_int_in_range_valid_exclusive(void) {
  int value = 5;
  TEST_ASSERT_TRUE(is_int_in_range(&value, "number", 10, 0, 0, 0));
}

void test_is_int_in_range_high_exclusive(void) {
  int value = 10;
  TEST_ASSERT_TRUE(!is_int_in_range(&value, "number", 10, 0, 0, 1));
}

void test_is_int_in_range_low_exclusive(void) {
  int value = 0;
  TEST_ASSERT_TRUE(!is_int_in_range(&value, "number", 10, 0, 1, 0));
}

void test_is_int_in_range_low_inclusive(void) {
  int value = -1;
  TEST_ASSERT_TRUE(!is_int_in_range(&value, "number", 10, 0, 1, 1));
}

// Test: Valid input (within range, inclusive boundaries)
void test_read_int_valid_input_inclusive(void) {
  int value;
  mock_input("5\n");  // Simulate valid integer input within range

  int result = read_int(&value, "number", "num", 7, 1, 10, 0, 1, 1);
  TEST_ASSERT_EQUAL(0, result);  // Expect success (0)
  TEST_ASSERT_EQUAL(5, value);   // Expect value to be set to 5
}

// Test: Out-of-range input (exceeding max_value, exclusive)
void test_read_int_out_of_range_high_exclusive(void) {
  int value;
  mock_input("10\n");  // Simulate input exactly at max_value (exclusive)

  int result = read_int(&value, "number", "num", 7, 1, 9, 0, 0, 1);
  TEST_ASSERT_EQUAL(1,
                    result);  // Expect failure (1) due to exceeding max_value
}

// Test: Out-of-range input (below min_value, exclusive)
void test_read_int_out_of_range_low_exclusive(void) {
  int value;
  mock_input("0\n");  // Simulate input exactly at min_value (exclusive)

  int result = read_int(&value, "number", "num", 7, 1, 10, 1, 1, 0);
  TEST_ASSERT_EQUAL(1,
                    result);  // Expect failure (1) due to being below min_value
}

// Test: Invalid input (non-numeric characters)
void test_read_int_invalid_format(void) {
  int value;
  mock_input("abc\n");  // Non-integer input

  int result = read_int(&value, "number", "num", 7, 1, 10, 0, 1, 1);
  TEST_ASSERT_EQUAL(1,
                    result);  // Expect failure (1) due to invalid input format
}

// Test: Input without newline (too long)
void test_read_int_no_newline(void) {
  int value;
  mock_input("123");  // Input missing newline at the end

  int result = read_int(&value, "number", "num", 7, 1, 10, 0, 1, 1);
  TEST_ASSERT_EQUAL(1, result);  // Expect failure (1) due to missing newline
}

// Test: Input with decimal value (should fail since it's not an integer)
void test_read_int_with_decimal(void) {
  int value;
  mock_input("5.5\n");  // Simulate input with a decimal value

  int result = read_int(&value, "number", "num", 7, 1, 10, 0, 1, 1);
  TEST_ASSERT_EQUAL(
      1, result);  // Expect failure (1) because input is not an integer
}

// Test: Valid input (unrestricted mode)
void test_read_int_valid_unrestricted(void) {
  int value;
  mock_input("-100\n");  // Simulate valid integer input without restrictions

  int result = read_int(&value, "number", "num", 7, 0, 0, 0, 0, 0);
  TEST_ASSERT_EQUAL(0, result);    // Expect success (0)
  TEST_ASSERT_EQUAL(-100, value);  // Expect value to be set correctly
}

// Test: Valid input (within range, min inclusive, max exclusive)
void test_read_int_valid_range_inclusive_min_exclusive_max(void) {
  int value;
  mock_input("10\n");  // Input exactly at max_value (exclusive)

  int result = read_int(&value, "number", "num", 7, 1, 10, 0, 0, 1);
  TEST_ASSERT_EQUAL(
      1, result);  // Expect failure (1) due to max_value being exclusive
}

// Test: Valid input (exactly at min_value inclusive)
void test_read_int_valid_min_value_inclusive(void) {
  int value;
  mock_input("0\n");  // Input exactly at min_value

  int result = read_int(&value, "number", "num", 7, 1, 10, 0, 1, 1);
  TEST_ASSERT_EQUAL(0, result);  // Expect success (0), min_value is inclusive
}

void test_int_utils() {
  RUN_TEST(test_is_int_in_range_valid_inclusive);
  RUN_TEST(test_is_int_in_range_valid_exclusive);
  RUN_TEST(test_is_int_in_range_high_exclusive);
  RUN_TEST(test_is_int_in_range_low_exclusive);
  RUN_TEST(test_is_int_in_range_low_inclusive);

  RUN_TEST(test_read_int_valid_input_inclusive);
  RUN_TEST(test_read_int_out_of_range_high_exclusive);
  RUN_TEST(test_read_int_out_of_range_low_exclusive);
  RUN_TEST(test_read_int_invalid_format);
  RUN_TEST(test_read_int_no_newline);
  RUN_TEST(test_read_int_with_decimal);
  RUN_TEST(test_read_int_valid_unrestricted);
  RUN_TEST(test_read_int_valid_range_inclusive_min_exclusive_max);
  RUN_TEST(test_read_int_valid_min_value_inclusive);
}
