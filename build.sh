#!/bin/bash
set -e  # Exit on any error

# Step 1: Install CMake if not installed
if ! [ -x "$(command -v cmake)" ]; then
    echo "Installing CMake..."
    sudo apt update
    sudo apt install -y cmake
fi

# Step 2: Create and navigate to the build directory
mkdir -p build
cd build

# Step 3: Run CMake and build the project
cmake ..
make

# Step 4: Run the server executable (adjust path if necessary)
./server/server