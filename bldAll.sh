#!/bin/bash

# Build Debug version
echo "Building Debug version..."
cmake --build build --config Debug --target all -j 26 --

# Build Release version
echo "Building Release version..."
cmake --build build --config Release --target all -j 26 --

# publish
./publish.sh 