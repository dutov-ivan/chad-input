#include <float.h>

#include "../src/input.h"
#include "../unity/src/unity.h"
#include "test.h"

void test_read_int_and_validate_valid_input() {
  int value;
  simulate_stdin("123\n");
  TEST_ASSERT_EQUAL(
      SUCCESS, read_int_and_validate(&value, "Test Value", "test", 10, false,
                                     INT_MAX, INT_MIN, true, true));
  TEST_ASSERT_EQUAL(123, value);
}

void test_read_int_and_validate_out_of_range_high() {
  int value;
  simulate_stdin("2147483648\n");  // INT_MAX + 1
  TEST_ASSERT_EQUAL(
      ERROR, read_int_and_validate(&value, "Test Value", "test", 10, false,
                                   INT_MAX, INT_MIN, true, true));
}

void test_read_int_and_validate_out_of_range_low() {
  int value;
  simulate_stdin("-2147483649\n");  // INT_MIN - 1
  TEST_ASSERT_EQUAL(
      ERROR, read_int_and_validate(&value, "Test Value", "test", 10, false,
                                   INT_MAX, INT_MIN, true, true));
}

void test_read_int_and_validate_non_number() {
  int value;
  simulate_stdin("not_a_number\n");
  TEST_ASSERT_EQUAL(
      ERROR, read_int_and_validate(&value, "Test Value", "test", 10, false,
                                   INT_MAX, INT_MIN, true, true));
}

void test_read_int_and_validate_too_long_input() {
  int value;
  simulate_stdin("12345678901234567890\n");  // Exceeds max_char_count
  TEST_ASSERT_EQUAL(
      ERROR, read_int_and_validate(&value, "Test Value", "test", 10, false,
                                   INT_MAX, INT_MIN, true, true));
}

void test_read_int_and_validate_with_restriction_in_range() {
  int value;
  simulate_stdin("50\n");
  TEST_ASSERT_EQUAL(
      SUCCESS, read_int_and_validate(&value, "Test Value", "test", 10, true,
                                     100, 0, true, true));
  TEST_ASSERT_EQUAL(50, value);
}

void test_read_int_and_validate_with_restriction_out_of_range_high() {
  int value;
  simulate_stdin("101\n");
  TEST_ASSERT_EQUAL(ERROR, read_int_and_validate(&value, "Test Value", "test",
                                                 10, true, 100, 0, true, true));
}

void test_read_int_and_validate_with_restriction_out_of_range_low() {
  int value;
  simulate_stdin("-1\n");
  TEST_ASSERT_EQUAL(ERROR, read_int_and_validate(&value, "Test Value", "test",
                                                 10, true, 100, 0, true, true));
}

// READ LONG
//

void test_read_long_int_and_validate_valid_input_unrestricted() {
  long int value;
  const char *input = "12345\n";
  simulate_stdin(input);

  int result = read_long_int_and_validate(
      &value, "Test Value", "test", 10, false, LONG_MAX, LONG_MIN, true, true);
  TEST_ASSERT_EQUAL(SUCCESS, result);
  TEST_ASSERT_EQUAL(12345, value);
}

void test_read_long_int_and_validate_valid_input_restricted() {
  long int value;
  const char *input = "123\n";
  simulate_stdin(input);

  int result = read_long_int_and_validate(
      &value, "Restricted Value", "restricted", 10, true, 200, 100, true, true);
  TEST_ASSERT_EQUAL(SUCCESS, result);
  TEST_ASSERT_EQUAL(123, value);
}

void test_read_long_int_and_validate_input_too_long() {
  long int value;
  const char *input = "12345678901234567890\n";  // Exceeds max_char_count
  simulate_stdin(input);

  int result = read_long_int_and_validate(
      &value, "Long Input", "long", 10, false, LONG_MAX, LONG_MIN, true, true);
  TEST_ASSERT_EQUAL(ERROR, result);
}

void test_read_long_int_and_validate_non_numeric_input() {
  long int value;
  const char *input = "abc\n";  // Non-numeric input
  simulate_stdin(input);

  int result =
      read_long_int_and_validate(&value, "Non-numeric Input", "non_numeric", 10,
                                 false, LONG_MAX, LONG_MIN, true, true);
  TEST_ASSERT_EQUAL(ERROR, result);
}

void test_read_long_int_and_validate_out_of_bounds() {
  long int value;
  const char *input = "9223372036854775808\n";  // Greater than LONG_MAX
  simulate_stdin(input);

  int result =
      read_long_int_and_validate(&value, "Out of Bounds", "out_of_bounds", 10,
                                 false, LONG_MAX, LONG_MIN, true, true);
  TEST_ASSERT_EQUAL(ERROR, result);
}

void test_read_long_int_and_validate_below_bounds() {
  long int value;
  const char *input = "-9223372036854775809\n";  // Less than LONG_MIN
  simulate_stdin(input);

  int result =
      read_long_int_and_validate(&value, "Below Bounds", "below_bounds", 10,
                                 false, LONG_MAX, LONG_MIN, true, true);
  TEST_ASSERT_EQUAL(ERROR, result);
}

void test_read_long_int_and_validate_restricted_outside_range() {
  long int value;
  const char *input = "50\n";  // Outside restricted range [100, 200]
  simulate_stdin(input);

  int result = read_long_int_and_validate(
      &value, "Restricted Value", "restricted", 10, true, 200, 100, true, true);
  TEST_ASSERT_EQUAL(ERROR, result);
}

void test_read_long_int_and_validate_exact_boundaries_inclusive() {
  long int value;
  const char *input = "100\n";  // Exact minimum bound
  simulate_stdin(input);

  int result =
      read_long_int_and_validate(&value, "Inclusive Boundaries", "boundaries",
                                 10, true, 200, 100, true, true);
  TEST_ASSERT_EQUAL(SUCCESS, result);
  TEST_ASSERT_EQUAL(100, value);
}

void test_read_long_int_and_validate_exact_boundaries_exclusive() {
  long int value;
  const char *input = "200\n";  // Exact maximum bound, but exclusive
  simulate_stdin(input);

  int result =
      read_long_int_and_validate(&value, "Exclusive Boundaries", "boundaries",
                                 10, true, 200, 100, false, false);
  TEST_ASSERT_EQUAL(ERROR, result);
}

void test_read_long_int_and_validate_invalid_format() {
  long int value;
  const char *input = "123abc\n";  // Mixed numeric and non-numeric input
  simulate_stdin(input);

  int result =
      read_long_int_and_validate(&value, "Invalid Format", "invalid", 10, false,
                                 LONG_MAX, LONG_MIN, true, true);
  TEST_ASSERT_EQUAL(ERROR, result);
}

// Test for valid input within range
void test_read_long_long_int_and_validate_valid_input() {
  long long int value;
  simulate_stdin("100\n");  // Simulate user input "100"

  int result =
      read_long_long_int_and_validate(&value, "Enter a number", "num", 20, true,
                                      LLONG_MAX, LLONG_MIN, true, true);

  TEST_ASSERT_EQUAL(SUCCESS, result);
  TEST_ASSERT_EQUAL(100, value);  // Assuming 100 is the value read
}

// Test for invalid input that's not a number
void test_read_long_long_int_and_validate_invalid_input_non_numeric() {
  long long int value;
  simulate_stdin("abc\n");  // Simulate non-numeric input

  int result =
      read_long_long_int_and_validate(&value, "Enter a number", "num", 20, true,
                                      LLONG_MAX, LLONG_MIN, true, true);

  TEST_ASSERT_EQUAL(ERROR, result);
}

// Test for input too long
void test_read_long_long_int_and_validate_input_too_long() {
  long long int value;
  simulate_stdin(
      "123456789012345678901234567890\n");  // Input longer than the max length

  int result =
      read_long_long_int_and_validate(&value, "Enter a number", "num", 20, true,
                                      LLONG_MAX, LLONG_MIN, true, true);

  TEST_ASSERT_EQUAL(ERROR, result);
}

// Test for value exceeding the upper limit (GREATER)
void test_read_long_long_int_and_validate_value_too_large() {
  long long int value;
  simulate_stdin("9223372036854775808\n");  // One more than LLONG_MAX

  int result =
      read_long_long_int_and_validate(&value, "Enter a number", "num", 20, true,
                                      LLONG_MAX, LLONG_MIN, true, true);

  TEST_ASSERT_EQUAL(ERROR, result);
}

// Test for value below the lower limit (LESS)
void test_read_long_long_int_and_validate_value_too_small() {
  long long int value;
  simulate_stdin("-9223372036854775809\n");  // One less than LLONG_MIN

  int result =
      read_long_long_int_and_validate(&value, "Enter a number", "num", 20, true,
                                      LLONG_MAX, LLONG_MIN, true, true);

  TEST_ASSERT_EQUAL(ERROR, result);
}

// Test for valid input within the specified range (but exclusive of the
// boundaries)
void test_read_long_long_int_and_validate_valid_input_with_range_check() {
  long long int value;
  simulate_stdin("50\n");  // Simulate input within range

  int result = read_long_long_int_and_validate(&value, "Enter a number", "num",
                                               20, true, 100, 10, false, false);

  TEST_ASSERT_EQUAL(SUCCESS, result);
  TEST_ASSERT_EQUAL(50, value);  // Assuming 50 is the value read
}

// Test for value exactly equal to the lower boundary when boundaries are
// exclusive (LESS_EQUAL)
void test_read_long_long_int_and_validate_value_exclusive_lower() {
  long long int value;
  simulate_stdin("10\n");  // Lower boundary value, exclusive range

  int result = read_long_long_int_and_validate(&value, "Enter a number", "num",
                                               20, true, 10, 20, false, false);

  TEST_ASSERT_EQUAL(ERROR,
                    result);  // Expect failure because boundaries are exclusive
}

// Test for value exactly equal to the upper boundary when boundaries are
// exclusive (GREATER_EQUAL)
void test_read_long_long_int_and_validate_value_exclusive_upper() {
  long long int value;
  simulate_stdin("20\n");  // Upper boundary value, exclusive range

  int result = read_long_long_int_and_validate(&value, "Enter a number", "num",
                                               20, true, 10, 20, false, false);

  TEST_ASSERT_EQUAL(ERROR,
                    result);  // Expect failure because boundaries are exclusive
}

// Test for valid input with inclusive range (min and max included)
void test_read_long_long_int_and_validate_valid_input_with_inclusive_range() {
  long long int value;
  simulate_stdin("10\n");  // Boundary inclusive

  int result = read_long_long_int_and_validate(&value, "Enter a number", "num",
                                               20, true, 100, 10, true, true);

  TEST_ASSERT_EQUAL(SUCCESS, result);
  TEST_ASSERT_EQUAL(10, value);  // Boundary inclusive, so 10 should be allowed
}

// Test for value just outside range when boundaries are inclusive
void test_read_long_long_int_and_validate_value_outside_inclusive_range() {
  long long int value;
  simulate_stdin("5\n");  // Outside the inclusive range of [10, 100]

  int result = read_long_long_int_and_validate(&value, "Enter a number", "num",
                                               20, true, 100, 10, true, true);

  TEST_ASSERT_EQUAL(ERROR,
                    result);  // Expect failure because 5 is outside the range
}

void test_read_float_and_validate_valid_input_within_range(void) {
  float value;
  simulate_stdin("15.2\n");

  int result = read_float_and_validate(&value, "Test Value", "Test", 10, true,
                                       20.0, 10.0, true, true);

  TEST_ASSERT_EQUAL_FLOAT(15.2, value);
  TEST_ASSERT_EQUAL_INT(SUCCESS, result);
}

void test_read_float_and_validate_invalid_input_not_a_number(void) {
  float value;
  simulate_stdin("abc\n");

  int result = read_float_and_validate(&value, "Test Value", "Test", 10, true,
                                       20.0, 10.0, true, true);

  TEST_ASSERT_EQUAL_INT(ERROR, result);
}

void test_read_float_and_validate_invalid_input_overflow(void) {
  float value;
  simulate_stdin("1e1000\n");  // Large number causing overflow

  int result = read_float_and_validate(&value, "Test Value", "Test", 10, true,
                                       1000.0, 0.0, true, true);

  TEST_ASSERT_EQUAL_INT(ERROR, result);
}

void test_read_float_and_validate_input_below_min_value(void) {
  float value;
  simulate_stdin("5.0\n");

  int result = read_float_and_validate(&value, "Test Value", "Test", 10, true,
                                       10.0, 6.0, true, true);

  TEST_ASSERT_EQUAL_INT(ERROR, result);
}

void test_read_float_and_validate_input_above_max_value(void) {
  float value;
  simulate_stdin("25.0\n");

  int result = read_float_and_validate(&value, "Test Value", "Test", 10, true,
                                       20.0, 10.0, true, true);

  TEST_ASSERT_EQUAL_INT(ERROR, result);
}

void test_read_float_and_validate_valid_input_with_no_restriction(void) {
  float value;
  simulate_stdin("15.5\n");

  int result = read_float_and_validate(&value, "Test Value", "Test", 10, false,
                                       20.0, 10.0, true, true);

  TEST_ASSERT_EQUAL_FLOAT(15.5, value);
  TEST_ASSERT_EQUAL_INT(SUCCESS, result);
}

void test_read_float_and_validate_input_exceeds_max_length(void) {
  float value;
  simulate_stdin("1234567890.1234567890\n");  // Exceeds max_char_count of 10

  int result = read_float_and_validate(&value, "Test Value", "Test", 10, true,
                                       20.0, 10.0, true, true);

  TEST_ASSERT_EQUAL_INT(ERROR, result);
}

void test_read_float_and_validate_input_precision_warning_yes(void) {
  float value;
  simulate_stdin("15.123456\n+\n");

  int result = read_float_and_validate(&value, "Test Value", "Test", 10, true,
                                       20.0, 10.0, true, true);

  TEST_ASSERT_EQUAL_FLOAT(15.123456, value);
  TEST_ASSERT_EQUAL_INT(SUCCESS, result);
  // Assuming there is a way to check for warnings, this test could include a
  // check for a warning message
}

void test_read_float_and_validate_input_precision_warning_no(void) {
  float value;
  simulate_stdin("15.123456\n-\n");

  int result = read_float_and_validate(&value, "Test Value", "Test", 10, true,
                                       20.0, 10.0, true, true);

  TEST_ASSERT_EQUAL_INT(ERROR, result);
  // Assuming there is a way to check for warnings, this test could include a
  // check for a warning message
}

// DOUBLE

void test_read_double_and_validate_valid_input_within_unrestricted_range(void) {
  double value;
  simulate_stdin("123.456\n");
  int result = read_double_and_validate(&value, "Число", "Ч", 10, false, 0.0,
                                        0.0, false, false);
  TEST_ASSERT_EQUAL(SUCCESS, result);
  TEST_ASSERT_EQUAL_DOUBLE(123.456, value);
}

void test_read_double_and_validate_valid_input_within_restricted_range(void) {
  double value;
  simulate_stdin("50.25\n");
  int result = read_double_and_validate(&value, "Число", "Ч", 10, true, 100.0,
                                        50.0, true, true);
  TEST_ASSERT_EQUAL(SUCCESS, result);
  TEST_ASSERT_EQUAL_DOUBLE(50.25, value);
}

void test_read_double_and_validate_input_outside_range(void) {
  double value;
  simulate_stdin("200.0\n");
  int result = read_double_and_validate(&value, "Число", "Ч", 10, true, 100.0,
                                        50.0, true, true);
  TEST_ASSERT_EQUAL(ERROR, result);
}

void test_read_double_and_validate_input_not_a_number(void) {
  double value;
  simulate_stdin("not_a_number\n");
  int result = read_double_and_validate(&value, "Число", "Ч", 10, false, 0.0,
                                        0.0, false, false);
  TEST_ASSERT_EQUAL(ERROR, result);
}

void test_read_double_and_validate_input_overlength(void) {
  double value;
  simulate_stdin("12345678901\n");  // Exceeds max_char_count
  int result = read_double_and_validate(&value, "Число", "Ч", 10, false, 0.0,
                                        0.0, false, false);
  TEST_ASSERT_EQUAL(ERROR, result);
}

void test_read_double_and_validate_underflow(void) {
  double value;
  simulate_stdin("1e-400\n");  // Value underflows
  int result = read_double_and_validate(&value, "Число", "Ч", 10, false, 0.0,
                                        0.0, false, false);
  TEST_ASSERT_EQUAL(ERROR, result);
}

void test_read_double_and_validate_overflow(void) {
  double value;
  simulate_stdin("1e+400\n");  // Value overflows
  int result = read_double_and_validate(&value, "Число", "Ч", 10, false, 0.0,
                                        0.0, false, false);
  TEST_ASSERT_EQUAL(ERROR, result);
}

void test_read_double_and_validate_imprecise_input_yes(void) {
  double value;
  simulate_stdin("123.45678901234567890\n+\n");  // Exceeds precision
  int result = read_double_and_validate(&value, "Число", "Ч", 25, false, 0.0,
                                        0.0, false, false);
  TEST_ASSERT_EQUAL(SUCCESS, result);
  TEST_ASSERT_DOUBLE_WITHIN(DBL_EPSILON, 123.45678901234567890, value);
}

void test_read_double_and_validate_imprecise_input_no(void) {
  double value;
  simulate_stdin("123.45678901234567890\n-\n");  // Exceeds precision
  int result = read_double_and_validate(&value, "Число", "Ч", 25, false, 0.0,
                                        0.0, false, false);
  TEST_ASSERT_EQUAL(ERROR, result);
}

// LONG DOUBLE
void test_read_long_double_and_validate_within_range(void) {
  simulate_stdin("123.456\n");
  long double value;
  int result = read_long_double_and_validate(
      &value, "Positive Number", "Num", 50, true, 200.0L, 100.0L, true, true);
  TEST_ASSERT_EQUAL(SUCCESS, result);
  TEST_ASSERT_DOUBLE_WITHIN(LDBL_EPSILON, 123.456L, value);
}

void test_read_long_double_and_validate_below_min(void) {
  simulate_stdin("99.999\n");
  long double value;
  int result = read_long_double_and_validate(&value, "Test Number", "Num", 50,
                                             true, 200.0L, 100.0L, true, true);
  TEST_ASSERT_EQUAL(ERROR, result);
}

void test_read_long_double_and_validate_above_max(void) {
  simulate_stdin("201.001\n");
  long double value;
  int result = read_long_double_and_validate(&value, "Test Number", "Num", 50,
                                             true, 200.0L, 100.0L, true, true);
  TEST_ASSERT_EQUAL(ERROR, result);
}

void test_read_long_double_and_validate_edge_min(void) {
  simulate_stdin("100.0\n");
  long double value;
  int result = read_long_double_and_validate(&value, "Edge Test", "Num", 50,
                                             true, 200.0L, 100.0L, true, true);
  TEST_ASSERT_EQUAL(SUCCESS, result);
  TEST_ASSERT_DOUBLE_WITHIN(LDBL_EPSILON, 100.0L, value);
}

void test_read_long_double_and_validate_edge_max(void) {
  simulate_stdin("200.0\n");
  long double value;
  int result = read_long_double_and_validate(&value, "Edge Test", "Num", 50,
                                             true, 200.0L, 100.0L, true, true);
  TEST_ASSERT_EQUAL(SUCCESS, result);
  TEST_ASSERT_DOUBLE_WITHIN(LDBL_EPSILON, 200.0L, value);
}

void test_read_long_double_and_validate_out_of_range_underflow(void) {
  simulate_stdin("1e-5000\n");
  long double value;
  int result = read_long_double_and_validate(&value, "Underflow Test", "Num",
                                             50, false, 0, 0, false, false);
  TEST_ASSERT_EQUAL(ERROR, result);
}

void test_read_long_double_and_validate_out_of_range_overflow(void) {
  simulate_stdin("1e5000\n");
  long double value;
  int result = read_long_double_and_validate(&value, "Overflow Test", "Num", 50,
                                             false, 0, 0, false, false);
  TEST_ASSERT_EQUAL(ERROR, result);
}

void test_read_long_double_and_validate_not_a_number(void) {
  simulate_stdin("abcd\n");
  long double value;
  int result = read_long_double_and_validate(&value, "Invalid Input", "Num", 50,
                                             false, 0, 0, false, false);
  TEST_ASSERT_EQUAL(ERROR, result);
}

void test_read_long_double_and_validate_truncated_precision_yes(void) {
  simulate_stdin("123.45678901234567890\n+\n");
  long double value;
  int result = read_long_double_and_validate(&value, "Precision Test", "Num",
                                             50, false, 0, 0, false, false);
  TEST_ASSERT_EQUAL(SUCCESS, result);
  TEST_ASSERT_DOUBLE_WITHIN(LDBL_EPSILON, 123.45678901234568L,
                            value);  // Precision limited to LDBL_DIG
}

void test_read_long_double_and_validate_truncated_precision_no(void) {
  simulate_stdin("123.45678901234567890\n-\n");
  long double value;
  int result = read_long_double_and_validate(&value, "Precision Test", "Num",
                                             50, false, 0, 0, false, false);
  TEST_ASSERT_EQUAL(ERROR, result);
}

void test_read_long_double_and_validate_length_exceeded(void) {
  simulate_stdin("1234567890123456789012345678901234567890\n");
  long double value;
  int result = read_long_double_and_validate(&value, "Length Test", "Num", 20,
                                             false, 0, 0, false, false);
  TEST_ASSERT_EQUAL(ERROR, result);
}

void test_read() {
  RUN_TEST(test_read_int_and_validate_valid_input);
  RUN_TEST(test_read_int_and_validate_out_of_range_high);
  RUN_TEST(test_read_int_and_validate_out_of_range_low);
  RUN_TEST(test_read_int_and_validate_non_number);
  RUN_TEST(test_read_int_and_validate_too_long_input);
  RUN_TEST(test_read_int_and_validate_with_restriction_in_range);
  RUN_TEST(test_read_int_and_validate_with_restriction_out_of_range_high);
  RUN_TEST(test_read_int_and_validate_with_restriction_out_of_range_low);

  RUN_TEST(test_read_long_int_and_validate_valid_input_unrestricted);
  RUN_TEST(test_read_long_int_and_validate_valid_input_restricted);
  RUN_TEST(test_read_long_int_and_validate_input_too_long);
  RUN_TEST(test_read_long_int_and_validate_non_numeric_input);
  RUN_TEST(test_read_long_int_and_validate_out_of_bounds);
  RUN_TEST(test_read_long_int_and_validate_below_bounds);
  RUN_TEST(test_read_long_int_and_validate_restricted_outside_range);
  RUN_TEST(test_read_long_int_and_validate_exact_boundaries_inclusive);
  RUN_TEST(test_read_long_int_and_validate_exact_boundaries_exclusive);
  RUN_TEST(test_read_long_int_and_validate_invalid_format);

  RUN_TEST(test_read_long_long_int_and_validate_valid_input);
  RUN_TEST(test_read_long_long_int_and_validate_invalid_input_non_numeric);
  RUN_TEST(test_read_long_long_int_and_validate_input_too_long);
  RUN_TEST(test_read_long_long_int_and_validate_value_too_large);
  RUN_TEST(test_read_long_long_int_and_validate_value_too_small);
  RUN_TEST(test_read_long_long_int_and_validate_valid_input_with_range_check);
  RUN_TEST(test_read_long_long_int_and_validate_value_exclusive_lower);
  RUN_TEST(test_read_long_long_int_and_validate_value_exclusive_upper);
  RUN_TEST(
      test_read_long_long_int_and_validate_valid_input_with_inclusive_range);
  RUN_TEST(test_read_long_long_int_and_validate_value_outside_inclusive_range);

  RUN_TEST(test_read_float_and_validate_valid_input_within_range);
  RUN_TEST(test_read_float_and_validate_invalid_input_not_a_number);
  RUN_TEST(test_read_float_and_validate_invalid_input_overflow);
  RUN_TEST(test_read_float_and_validate_input_below_min_value);
  RUN_TEST(test_read_float_and_validate_input_above_max_value);
  RUN_TEST(test_read_float_and_validate_valid_input_with_no_restriction);
  RUN_TEST(test_read_float_and_validate_input_exceeds_max_length);
  RUN_TEST(test_read_float_and_validate_input_precision_warning_yes);
  RUN_TEST(test_read_float_and_validate_input_precision_warning_no);

  RUN_TEST(test_read_double_and_validate_valid_input_within_unrestricted_range);
  RUN_TEST(test_read_double_and_validate_valid_input_within_restricted_range);
  RUN_TEST(test_read_double_and_validate_input_outside_range);
  RUN_TEST(test_read_double_and_validate_input_not_a_number);
  RUN_TEST(test_read_double_and_validate_input_overlength);
  RUN_TEST(test_read_double_and_validate_underflow);
  RUN_TEST(test_read_double_and_validate_overflow);
  RUN_TEST(test_read_double_and_validate_imprecise_input_yes);
  RUN_TEST(test_read_double_and_validate_imprecise_input_no);

  RUN_TEST(test_read_long_double_and_validate_within_range);
  RUN_TEST(test_read_long_double_and_validate_below_min);
  RUN_TEST(test_read_long_double_and_validate_above_max);
  RUN_TEST(test_read_long_double_and_validate_edge_min);
  RUN_TEST(test_read_long_double_and_validate_edge_max);
  RUN_TEST(test_read_long_double_and_validate_out_of_range_underflow);
  RUN_TEST(test_read_long_double_and_validate_out_of_range_overflow);
  RUN_TEST(test_read_long_double_and_validate_not_a_number);
  RUN_TEST(test_read_long_double_and_validate_truncated_precision_yes);
  RUN_TEST(test_read_long_double_and_validate_truncated_precision_no);
  RUN_TEST(test_read_long_double_and_validate_length_exceeded);
}
