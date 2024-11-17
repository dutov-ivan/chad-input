#include "../src/test.h"
#include "../unity/src/unity.h"
#include "test.h"

void test_read_int_valid_input() {
  int value;
  simulate_stdin("123\n");
  TEST_ASSERT_EQUAL(SUCCESS, read_int(&value, "Test Value", "test", 10, false,
                                      INT_MAX, INT_MIN, true, true));
  TEST_ASSERT_EQUAL(123, value);
}

void test_read_int_out_of_range_high() {
  int value;
  simulate_stdin("2147483648\n");  // INT_MAX + 1
  TEST_ASSERT_EQUAL(ERROR, read_int(&value, "Test Value", "test", 10, false,
                                    INT_MAX, INT_MIN, true, true));
}

void test_read_int_out_of_range_low() {
  int value;
  simulate_stdin("-2147483649\n");  // INT_MIN - 1
  TEST_ASSERT_EQUAL(ERROR, read_int(&value, "Test Value", "test", 10, false,
                                    INT_MAX, INT_MIN, true, true));
}

void test_read_int_non_number() {
  int value;
  simulate_stdin("not_a_number\n");
  TEST_ASSERT_EQUAL(ERROR, read_int(&value, "Test Value", "test", 10, false,
                                    INT_MAX, INT_MIN, true, true));
}

void test_read_int_too_long_input() {
  int value;
  simulate_stdin("12345678901234567890\n");  // Exceeds max_char_count
  TEST_ASSERT_EQUAL(ERROR, read_int(&value, "Test Value", "test", 10, false,
                                    INT_MAX, INT_MIN, true, true));
}

void test_read_int_with_restriction_in_range() {
  int value;
  simulate_stdin("50\n");
  TEST_ASSERT_EQUAL(SUCCESS, read_int(&value, "Test Value", "test", 10, true,
                                      100, 0, true, true));
  TEST_ASSERT_EQUAL(50, value);
}

void test_read_int_with_restriction_out_of_range_high() {
  int value;
  simulate_stdin("101\n");
  TEST_ASSERT_EQUAL(ERROR, read_int(&value, "Test Value", "test", 10, true, 100,
                                    0, true, true));
}

void test_read_int_with_restriction_out_of_range_low() {
  int value;
  simulate_stdin("-1\n");
  TEST_ASSERT_EQUAL(ERROR, read_int(&value, "Test Value", "test", 10, true, 100,
                                    0, true, true));
}

// READ LONG
//

void test_read_long_int_valid_input_unrestricted() {
  long int value;
  const char *input = "12345\n";
  simulate_stdin(input);

  int result = read_long_int(&value, "Test Value", "test", 10, false, LONG_MAX,
                             LONG_MIN, true, true);
  TEST_ASSERT_EQUAL(SUCCESS, result);
  TEST_ASSERT_EQUAL(12345, value);
}

void test_read_long_int_valid_input_restricted() {
  long int value;
  const char *input = "123\n";
  simulate_stdin(input);

  int result = read_long_int(&value, "Restricted Value", "restricted", 10, true,
                             200, 100, true, true);
  TEST_ASSERT_EQUAL(SUCCESS, result);
  TEST_ASSERT_EQUAL(123, value);
}

void test_read_long_int_input_too_long() {
  long int value;
  const char *input = "12345678901234567890\n";  // Exceeds max_char_count
  simulate_stdin(input);

  int result = read_long_int(&value, "Long Input", "long", 10, false, LONG_MAX,
                             LONG_MIN, true, true);
  TEST_ASSERT_EQUAL(ERROR, result);
}

void test_read_long_int_non_numeric_input() {
  long int value;
  const char *input = "abc\n";  // Non-numeric input
  simulate_stdin(input);

  int result = read_long_int(&value, "Non-numeric Input", "non_numeric", 10,
                             false, LONG_MAX, LONG_MIN, true, true);
  TEST_ASSERT_EQUAL(ERROR, result);
}

void test_read_long_int_out_of_bounds() {
  long int value;
  const char *input = "9223372036854775808\n";  // Greater than LONG_MAX
  simulate_stdin(input);

  int result = read_long_int(&value, "Out of Bounds", "out_of_bounds", 10,
                             false, LONG_MAX, LONG_MIN, true, true);
  TEST_ASSERT_EQUAL(ERROR, result);
}

void test_read_long_int_below_bounds() {
  long int value;
  const char *input = "-9223372036854775809\n";  // Less than LONG_MIN
  simulate_stdin(input);

  int result = read_long_int(&value, "Below Bounds", "below_bounds", 10, false,
                             LONG_MAX, LONG_MIN, true, true);
  TEST_ASSERT_EQUAL(ERROR, result);
}

void test_read_long_int_restricted_outside_range() {
  long int value;
  const char *input = "50\n";  // Outside restricted range [100, 200]
  simulate_stdin(input);

  int result = read_long_int(&value, "Restricted Value", "restricted", 10, true,
                             200, 100, true, true);
  TEST_ASSERT_EQUAL(ERROR, result);
}

void test_read_long_int_exact_boundaries_inclusive() {
  long int value;
  const char *input = "100\n";  // Exact minimum bound
  simulate_stdin(input);

  int result = read_long_int(&value, "Inclusive Boundaries", "boundaries", 10,
                             true, 200, 100, true, true);
  TEST_ASSERT_EQUAL(SUCCESS, result);
  TEST_ASSERT_EQUAL(100, value);
}

void test_read_long_int_exact_boundaries_exclusive() {
  long int value;
  const char *input = "200\n";  // Exact maximum bound, but exclusive
  simulate_stdin(input);

  int result = read_long_int(&value, "Exclusive Boundaries", "boundaries", 10,
                             true, 200, 100, false, false);
  TEST_ASSERT_EQUAL(ERROR, result);
}

void test_read_long_int_invalid_format() {
  long int value;
  const char *input = "123abc\n";  // Mixed numeric and non-numeric input
  simulate_stdin(input);

  int result = read_long_int(&value, "Invalid Format", "invalid", 10, false,
                             LONG_MAX, LONG_MIN, true, true);
  TEST_ASSERT_EQUAL(ERROR, result);
}

// Test for valid input within range
void test_read_long_long_int_valid_input() {
  long long int value;
  simulate_stdin("100\n");  // Simulate user input "100"

  int result = read_long_long_int(&value, "Enter a number", "num", 20, true,
                                  LLONG_MAX, LLONG_MIN, true, true);

  TEST_ASSERT_EQUAL(SUCCESS, result);
  TEST_ASSERT_EQUAL(100, value);  // Assuming 100 is the value read
}

// Test for invalid input that's not a number
void test_read_long_long_int_invalid_input_non_numeric() {
  long long int value;
  simulate_stdin("abc\n");  // Simulate non-numeric input

  int result = read_long_long_int(&value, "Enter a number", "num", 20, true,
                                  LLONG_MAX, LLONG_MIN, true, true);

  TEST_ASSERT_EQUAL(ERROR, result);
}

// Test for input too long
void test_read_long_long_int_input_too_long() {
  long long int value;
  simulate_stdin(
      "123456789012345678901234567890\n");  // Input longer than the max length

  int result = read_long_long_int(&value, "Enter a number", "num", 20, true,
                                  LLONG_MAX, LLONG_MIN, true, true);

  TEST_ASSERT_EQUAL(ERROR, result);
}

// Test for value exceeding the upper limit (GREATER)
void test_read_long_long_int_value_too_large() {
  long long int value;
  simulate_stdin("9223372036854775808\n");  // One more than LLONG_MAX

  int result = read_long_long_int(&value, "Enter a number", "num", 20, true,
                                  LLONG_MAX, LLONG_MIN, true, true);

  TEST_ASSERT_EQUAL(ERROR, result);
}

// Test for value below the lower limit (LESS)
void test_read_long_long_int_value_too_small() {
  long long int value;
  simulate_stdin("-9223372036854775809\n");  // One less than LLONG_MIN

  int result = read_long_long_int(&value, "Enter a number", "num", 20, true,
                                  LLONG_MAX, LLONG_MIN, true, true);

  TEST_ASSERT_EQUAL(ERROR, result);
}

// Test for valid input within the specified range (but exclusive of the
// boundaries)
void test_read_long_long_int_valid_input_with_range_check() {
  long long int value;
  simulate_stdin("50\n");  // Simulate input within range

  int result = read_long_long_int(&value, "Enter a number", "num", 20, true,
                                  100, 10, false, false);

  TEST_ASSERT_EQUAL(SUCCESS, result);
  TEST_ASSERT_EQUAL(50, value);  // Assuming 50 is the value read
}

// Test for value exactly equal to the lower boundary when boundaries are
// exclusive (LESS_EQUAL)
void test_read_long_long_int_value_exclusive_lower() {
  long long int value;
  simulate_stdin("10\n");  // Lower boundary value, exclusive range

  int result = read_long_long_int(&value, "Enter a number", "num", 20, true, 10,
                                  20, false, false);

  TEST_ASSERT_EQUAL(ERROR,
                    result);  // Expect failure because boundaries are exclusive
}

// Test for value exactly equal to the upper boundary when boundaries are
// exclusive (GREATER_EQUAL)
void test_read_long_long_int_value_exclusive_upper() {
  long long int value;
  simulate_stdin("20\n");  // Upper boundary value, exclusive range

  int result = read_long_long_int(&value, "Enter a number", "num", 20, true, 10,
                                  20, false, false);

  TEST_ASSERT_EQUAL(ERROR,
                    result);  // Expect failure because boundaries are exclusive
}

// Test for valid input with inclusive range (min and max included)
void test_read_long_long_int_valid_input_with_inclusive_range() {
  long long int value;
  simulate_stdin("10\n");  // Boundary inclusive

  int result = read_long_long_int(&value, "Enter a number", "num", 20, true,
                                  100, 10, true, true);

  TEST_ASSERT_EQUAL(SUCCESS, result);
  TEST_ASSERT_EQUAL(10, value);  // Boundary inclusive, so 10 should be allowed
}

// Test for value just outside range when boundaries are inclusive
void test_read_long_long_int_value_outside_inclusive_range() {
  long long int value;
  simulate_stdin("5\n");  // Outside the inclusive range of [10, 100]

  int result = read_long_long_int(&value, "Enter a number", "num", 20, true,
                                  100, 10, true, true);

  TEST_ASSERT_EQUAL(ERROR,
                    result);  // Expect failure because 5 is outside the range
}

void test_read() {
  RUN_TEST(test_read_int_valid_input);
  RUN_TEST(test_read_int_out_of_range_high);
  RUN_TEST(test_read_int_out_of_range_low);
  RUN_TEST(test_read_int_non_number);
  RUN_TEST(test_read_int_too_long_input);
  RUN_TEST(test_read_int_with_restriction_in_range);
  RUN_TEST(test_read_int_with_restriction_out_of_range_high);
  RUN_TEST(test_read_int_with_restriction_out_of_range_low);

  RUN_TEST(test_read_long_int_valid_input_unrestricted);
  RUN_TEST(test_read_long_int_valid_input_restricted);
  RUN_TEST(test_read_long_int_input_too_long);
  RUN_TEST(test_read_long_int_non_numeric_input);
  RUN_TEST(test_read_long_int_out_of_bounds);
  RUN_TEST(test_read_long_int_below_bounds);
  RUN_TEST(test_read_long_int_restricted_outside_range);
  RUN_TEST(test_read_long_int_exact_boundaries_inclusive);
  RUN_TEST(test_read_long_int_exact_boundaries_exclusive);
  RUN_TEST(test_read_long_int_invalid_format);

  RUN_TEST(test_read_long_long_int_valid_input);
  RUN_TEST(test_read_long_long_int_invalid_input_non_numeric);
  RUN_TEST(test_read_long_long_int_input_too_long);
  RUN_TEST(test_read_long_long_int_value_too_large);
  RUN_TEST(test_read_long_long_int_value_too_small);
  RUN_TEST(test_read_long_long_int_valid_input_with_range_check);
  RUN_TEST(test_read_long_long_int_value_exclusive_lower);
  RUN_TEST(test_read_long_long_int_value_exclusive_upper);
  RUN_TEST(test_read_long_long_int_valid_input_with_inclusive_range);
  RUN_TEST(test_read_long_long_int_value_outside_inclusive_range);
}
