#include <stdio.h>

#include "input/input.h"

int main() {
  printf("I will take some input from you, hahahahhahaha\n");
  printf("Enter an integer: ");
  int n;
  read_input(&n, "cool number", "number", 10, 1, 100, 10, 1, 1);

  return 0;
}
