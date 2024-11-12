project('input_library', 'c')

# Compiler flags and include directories
c_args = ['-I.', '-Iunity/src', '-Isrc', '-g' ]
inc_dirs = include_directories('.', 'unity/src', 'src')

# Test program sources
test_sources = [
  # Input 
  'src/common_utils.c',
  'src/int_utils.c',
  'src/long_double_utils.c',

  # Input tests 
  'test/test_common_utils.c',
  'test/test_int_utils.c',
  'test/test_long_double_utils.c',
  'test/utils.c',
  'test/test.c',

  # Testing library import
  'unity/src/unity.c',
]

# Define the test executable
executable('test.out', test_sources,
  c_args: c_args,
  include_directories: inc_dirs,
  link_args: ['-lm']
)


