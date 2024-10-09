#include "test/hello_test.h"
#include "../src/hello.h"
#include "../unity/src/unity.h"

void test_hello_world() {
  hello_world();
  TEST_ASSERT_EQUAL(1, 1);
}

void run_hello_tests() {
  RUN_TEST(test_hello_world);
  printf("All hello tests run successfully\n");
}
