#ifndef INPUT_TEST_H
#define INPUT_TEST_H

void simulate_stdin(const char *input);
char *capture_stdout(void (*test_func)(void));

void test_capture_stdout();
void test_read_input(void);
void test_overflow(void);
void test_range(void);
void test_read(void);
void test_truncate(void);
void test_utils(void);

#endif
