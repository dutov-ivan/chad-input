#include "test.h"

#include <stdlib.h>

#include "../unity/src/unity.h"

void setUp() {}
void tearDown() {}

int main() {
  UNITY_BEGIN();
  printf("Running input tests\n");
  test_utils();
  test_overflow();
  test_range();
  test_read();
  test_truncate();
  UNITY_END();
  printf("All tests run successfully\n");
  return 0;
}

void simulate_stdin(const char *input) {
  FILE *temp = fopen("test_input.txt", "w");
  if (!temp) {
    perror("fopen");
    exit(EXIT_FAILURE);
  }

  fputs(input, temp);
  fclose(temp);

  temp = freopen("test_input.txt", "r", stdin);
  if (!temp) {
    perror("freopen");
    exit(EXIT_FAILURE);
  }
}
