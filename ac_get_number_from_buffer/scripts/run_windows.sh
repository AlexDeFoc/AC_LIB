#!/bin/bash

# Function to check the exit status of the last command
check_status() {
  if [ $? -ne 0 ]; then
    echo "FAILED: $1"
    echo "$(date '+%Y-%m-%d %H:%M:%S') - FAIL: $1" >>"$temp"
    exit 1
  else
      echo "DONE: $1"
  fi
}

# Go to project root folder & store variables
cd ..
root=$(pwd)
build="$root/build"
output="$root/output/windows"

# Create temp file
temp="$root/temp_output_error_file.txt"
touch "$temp"

# Run cmake
cmake -S . -B build -G Ninja -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ >"$temp" 2>&1
check_status "cmake"


# Go to build folder
cd "$build"

# Run ninja
ninja >"$temp" 2>&1
check_status "ninja"

# Copy library & tests files into output folder
cp -f "ac_get_number_from_buffer.lib" "$output/ac_get_number_from_buffer.lib" >"$temp" 2>&1
check_status ".lib"

cp -f "ac_get_number_from_buffer.dll" "$output/ac_get_number_from_buffer.dll" >"$temp" 2>&1
check_status ".dll"

cp -f "ac_test_1.exe" "$output/ac_test_1.exe" >"$temp" 2>&1
check_status "tests"

# Delete temporary output file
rm "$temp"
