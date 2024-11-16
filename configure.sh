#!/bin/sh

# Ensure the build directory exists
mkdir -p build

# Run Meson setup with the correct native file
meson setup build --native-file native.build
