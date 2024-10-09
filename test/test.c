#include "../unity/src/unity.h"
#include "hello_test.h"

/* Set up and tear down functions for Unity test framework */
void setUp() {}
void tearDown() {}

int main() {
  UNITY_BEGIN();
  run_hello_tests();
  UNITY_END();
  printf("Create tests, buddy!\n");
  return 0;
}
