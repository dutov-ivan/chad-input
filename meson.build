project('ln(x + sqrt(1 + x^2))', 'c')

# Compiler flags and include directories
c_args = ['-I.', '-Iunity/src', '-Isrc', '-g' ]
inc_dirs = include_directories('.', 'unity/src', 'src')

# Main program sources
main_sources = [
  'src/main.c',
  # Input
  'src/input/common_utils.c',
  'src/input/int_utils.c',
  'src/input/long_double_utils.c'
]

# Test program sources
test_sources = [
  # Input 
  'src/input/common_utils.c',
  'src/input/int_utils.c',
  'src/input/long_double_utils.c',

  # Input tests 
  'test/input/test_common_utils.c',
  'test/input/test_int_utils.c',
  'test/input/test_long_double_utils.c',
  'test/test.c',

  # Testing library import
  'unity/src/unity.c',
]

# Define the main executable
executable('main.out', main_sources,
  c_args: c_args,
  include_directories: inc_dirs,
  link_args: ['-lm']
)

# Define the test executable
executable('test.out', test_sources,
  c_args: c_args,
  include_directories: inc_dirs,
  link_args: ['-lm']
)


