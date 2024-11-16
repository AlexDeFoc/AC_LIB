#!/bin/sh

echo "Building..."
cd build
ninja

echo "Running..."
cd test
./app.exe
