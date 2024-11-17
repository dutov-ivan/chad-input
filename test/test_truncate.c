#include <float.h>

#include "../src/test.h"
#include "../unity/src/unity.h"
#include "test.h"

void test_truncate_to_precision_float_no_change() {
  float num = 3.14159f;
  int decimal_places = 3;
  float result = truncate_to_precision_float(num, decimal_places);
  TEST_ASSERT_EQUAL_FLOAT(3.141f, result);
}

void test_truncate_to_precision_float_truncate_to_zero_decimal() {
  float num = 3.14159f;
  int decimal_places = 0;
  float result = truncate_to_precision_float(num, decimal_places);
  TEST_ASSERT_EQUAL_FLOAT(3.0f, result);
}

void test_truncate_to_precision_float_negative_number() {
  float num = -3.14159f;
  int decimal_places = 3;
  float result = truncate_to_precision_float(num, decimal_places);
  TEST_ASSERT_EQUAL_FLOAT(-3.141f, result);
}

void test_truncate_to_precision_float_truncate_more_than_precision() {
  float num = 3.14159f;
  int decimal_places = 5;
  float result = truncate_to_precision_float(num, decimal_places);
  TEST_ASSERT_EQUAL_FLOAT(3.14159f, result);  // No truncation needed
}

void test_truncate_to_precision_float_large_number() {
  float num = 12345.6789f;
  int decimal_places = 2;
  float result = truncate_to_precision_float(num, decimal_places);
  TEST_ASSERT_EQUAL_FLOAT(12345.67f, result);
}

void test_truncate_to_precision_float_zero() {
  float num = 0.0f;
  int decimal_places = 2;
  float result = truncate_to_precision_float(num, decimal_places);
  TEST_ASSERT_EQUAL_FLOAT(0.0f, result);
}

void test_truncate_to_precision_float_large_precision() {
  float num = 3.1415926535f;
  int decimal_places = 10;
  float result = truncate_to_precision_float(num, decimal_places);
  TEST_ASSERT_EQUAL_FLOAT(3.1415926535f, result);  // No truncation needed
}

void test_truncate_to_precision_float_edge_case() {
  float num = 3.99999f;
  int decimal_places = 2;
  float result = truncate_to_precision_float(num, decimal_places);
  TEST_ASSERT_EQUAL_FLOAT(3.99f, result);  // Truncation should occur
}

void test_truncate_to_precision_float_rounding_behavior() {
  float num = 5.55555f;
  int decimal_places = 3;
  float result = truncate_to_precision_float(num, decimal_places);
  TEST_ASSERT_EQUAL_FLOAT(5.555f,
                          result);  // Truncation should occur, not rounding
}

void test_truncate_to_precision_float_negative_truncate() {
  float num = -123.456789f;
  int decimal_places = 3;
  float result = truncate_to_precision_float(num, decimal_places);
  TEST_ASSERT_EQUAL_FLOAT(-123.456f, result);  // Negative number truncation
}

void test_truncate_to_precision_double_no_truncation_needed(void) {
  double result = truncate_to_precision_double(123.456, 3);
  TEST_ASSERT_EQUAL_DOUBLE(123.456, result);
}

void test_truncate_to_precision_double_truncate_excess_decimals(void) {
  double result = truncate_to_precision_double(123.456789, 3);
  TEST_ASSERT_EQUAL_DOUBLE(123.456, result);
}

void test_truncate_to_precision_double_rounding_not_applied(void) {
  double result = truncate_to_precision_double(123.999, 2);
  TEST_ASSERT_EQUAL_DOUBLE(123.99, result);
}

void test_truncate_to_precision_double_large_number_truncation(void) {
  double result = truncate_to_precision_double(123456789.987654321, 5);
  TEST_ASSERT_EQUAL_DOUBLE(123456789.98765, result);
}

void test_truncate_to_precision_double_negative_number(void) {
  double result = truncate_to_precision_double(-123.456789, 3);
  TEST_ASSERT_EQUAL_DOUBLE(-123.456, result);
}

void test_truncate_to_precision_double_zero_decimal_places(void) {
  double result = truncate_to_precision_double(123.456, 0);
  TEST_ASSERT_EQUAL_DOUBLE(123.0, result);
}

void test_truncate_to_precision_double_no_decimals_input(void) {
  double result = truncate_to_precision_double(123.0, 2);
  TEST_ASSERT_EQUAL_DOUBLE(123.0, result);
}

// LONG DOUBLE

void test_truncate_to_precision_long_double_no_truncation(void) {
  long double result = truncate_to_precision_long_double(123.456789L, 6);
  TEST_ASSERT_DOUBLE_WITHIN(LDBL_EPSILON, 123.456789L, result);
}

void test_truncate_to_precision_long_double_truncate_fractional(void) {
  long double result = truncate_to_precision_long_double(123.456789L, 4);
  TEST_ASSERT_DOUBLE_WITHIN(LDBL_EPSILON, 123.4567L, result);
}

void test_truncate_to_precision_long_double_no_fractional_part(void) {
  long double result = truncate_to_precision_long_double(123.0L, 3);
  TEST_ASSERT_DOUBLE_WITHIN(LDBL_EPSILON, 123.0L, result);
}

void test_truncate_to_precision_long_double_negative_number(void) {
  long double result = truncate_to_precision_long_double(-123.456789L, 2);
  TEST_ASSERT_DOUBLE_WITHIN(LDBL_EPSILON, -123.45L, result);
}

void test_truncate_to_precision_long_double_zero(void) {
  long double result = truncate_to_precision_long_double(0.0L, 5);
  TEST_ASSERT_DOUBLE_WITHIN(LDBL_EPSILON, 0.0L, result);
}

void test_truncate_to_precision_long_double_large_precision(void) {
  long double result = truncate_to_precision_long_double(1.23456789L, 10);
  TEST_ASSERT_DOUBLE_WITHIN(LDBL_EPSILON, 1.23456789L, result);
}

void test_truncate_to_precision_long_double_no_precision(void) {
  long double result = truncate_to_precision_long_double(123.456789L, 0);
  TEST_ASSERT_DOUBLE_WITHIN(LDBL_EPSILON, 123.0L, result);
}

void test_truncate(void) {
  RUN_TEST(test_truncate_to_precision_float_no_change);
  RUN_TEST(test_truncate_to_precision_float_truncate_to_zero_decimal);
  RUN_TEST(test_truncate_to_precision_float_negative_number);
  RUN_TEST(test_truncate_to_precision_float_truncate_more_than_precision);
  RUN_TEST(test_truncate_to_precision_float_large_number);
  RUN_TEST(test_truncate_to_precision_float_zero);
  RUN_TEST(test_truncate_to_precision_float_large_precision);
  RUN_TEST(test_truncate_to_precision_float_edge_case);
  RUN_TEST(test_truncate_to_precision_float_rounding_behavior);
  RUN_TEST(test_truncate_to_precision_float_negative_truncate);

  RUN_TEST(test_truncate_to_precision_double_no_truncation_needed);
  RUN_TEST(test_truncate_to_precision_double_truncate_excess_decimals);
  RUN_TEST(test_truncate_to_precision_double_rounding_not_applied);
  RUN_TEST(test_truncate_to_precision_double_large_number_truncation);
  RUN_TEST(test_truncate_to_precision_double_negative_number);
  RUN_TEST(test_truncate_to_precision_double_zero_decimal_places);
  RUN_TEST(test_truncate_to_precision_double_no_decimals_input);

  RUN_TEST(test_truncate_to_precision_long_double_no_truncation);
  RUN_TEST(test_truncate_to_precision_long_double_truncate_fractional);
  RUN_TEST(test_truncate_to_precision_long_double_no_fractional_part);
  RUN_TEST(test_truncate_to_precision_long_double_negative_number);
  RUN_TEST(test_truncate_to_precision_long_double_zero);
  RUN_TEST(test_truncate_to_precision_long_double_large_precision);
  RUN_TEST(test_truncate_to_precision_long_double_no_precision);
}
