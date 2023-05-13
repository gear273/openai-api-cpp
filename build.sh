#!/usr/bin/env bash

# build cpr
cd submodules/cpr || (echo "Error: Missing 'submodules/cpr'" && exit)
mkdir -p build
cd build || (echo "Error: Building 'submodules/cpr' failed" && exit)
cmake ..
make

# return to repository root directory
cd ../../../

# build pybind11
cd submodules/pybind11 || (echo "Error: Missing 'submodules/pybind11'" && exit)
mkdir -p build
cd build || (echo "Error: Building 'submodules/pybind11' failed" && exit)
cmake ..
make check -j 4
