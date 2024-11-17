#include "test.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../unity/src/unity.h"

void setUp() {}
void tearDown() {}

int main() {
  UNITY_BEGIN();
  printf("Running input tests\n");
  // test_capture_stdout();
  test_utils();
  test_overflow();
  test_range();
  test_read();
  test_truncate();
  UNITY_END();
  printf("All tests run successfully\n");
  return 0;
}

// Function to capture stdout
char *capture_stdout(void (*test_func)(void)) {
  int pipefd[2];
  pid_t pid;
  char *output = NULL;
  size_t buffer_size = 1024;

  if (pipe(pipefd) == -1) {
    perror("pipe");
    exit(EXIT_FAILURE);
  }

  pid = fork();
  if (pid == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  }

  if (pid == 0) {                    // Child process
    close(pipefd[0]);                // Close read end
    dup2(pipefd[1], STDOUT_FILENO);  // Redirect stdout to write end of the pipe
    close(pipefd[1]);

    test_func();  // Run the test function
    fflush(stdout);
    exit(EXIT_SUCCESS);
  } else {             // Parent process
    close(pipefd[1]);  // Close write end
    output = malloc(buffer_size);
    if (!output) {
      perror("malloc");
      exit(EXIT_FAILURE);
    }
    ssize_t bytes_read = read(pipefd[0], output, buffer_size - 1);
    if (bytes_read == -1) {
      perror("read");
      exit(EXIT_FAILURE);
    }
    output[bytes_read] = '\0';  // Null-terminate the string
    close(pipefd[0]);
  }

  return output;
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

void test_example_output() { printf("Hello, World!\n"); }

void test_capture_stdout() {
  char *output = capture_stdout(test_example_output);
  TEST_ASSERT_NOT_NULL(output);
  TEST_ASSERT_EQUAL_STRING("Hello, World!\n", output);
  free(output);
}
