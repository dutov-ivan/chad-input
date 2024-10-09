project('ln(x + sqrt(1 + x^2))', 'c')

# Compiler flags and include directories
c_args = ['-I.', '-Iunity/src', '-Isrc', '-g' ]
inc_dirs = include_directories('.', 'unity/src', 'src')

# Main program sources
main_sources = [
  'src/hello.c',
  'src/main.c'
]

# Test program sources
test_sources = [
  'src/hello.c',
  'test/hello_test.c',
  'test/test.c',
  'unity/src/unity.c',
]

# Define the main executable
executable('main.out', main_sources,
  c_args: c_args,
  include_directories: inc_dirs,
  link_args: []
)

# Define the test executable
executable('test.out', test_sources,
  c_args: c_args,
  include_directories: inc_dirs,
  link_args: []
)


