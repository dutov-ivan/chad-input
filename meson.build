project('chad-input', 'c')

# Compiler flags and include directories
c_args = ['-I.', '-Iunity/src', '-Isrc', '-g' ]
inc_dirs = include_directories('.', 'unity/src', 'src')

# Test program sources
test_sources = [
  # Input 
  'src/utils.c',
  'src/int.c',
  'src/long_int.c',
  'src/long_long_int.c',
  'src/float.c',
  'src/double.c',
  'src/long_double.c',

  # Input tests 
  'test/test_read.c',
  'test/test_range.c',
  'test/test_truncate.c',
  'test/test_utils.c',
  'test/test_overflow.c',

  # Testing library import
  'test/test.c',
  'unity/src/unity.c',
]

# Define the test executable
executable('test.out', test_sources,
  c_args: c_args,
  include_directories: inc_dirs,
  link_args: ['-lm']
)


