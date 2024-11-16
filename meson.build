# Define the project with a version
project('ac_lib', 'c', version: '1.0.0')

# Source files
src_files = [
  'src/ac_string.c',
]

# Include directories
include = include_directories('src')

# Build the static library
static_library('ac_lib', 
  src_files, 
  include_directories : include,
  name_prefix : ''
)
