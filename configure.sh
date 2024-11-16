#!/bin/bash

echo "Configuring ac_lib..."

cmake -S . -G "Ninja" .. -B "./build" -DCMAKE_BUILD_TYPE=Release

echo "Building ac_lib..."
cd build
ninja
