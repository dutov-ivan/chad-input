#include <stdio.h>
#include <stdlib.h>

#include "test_input.h"

void mock_input(const char *input) {
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
