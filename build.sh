#!/usr/bin/env bash

# Prompt user to choose module to build
echo "Which module would you like to build?"
echo "1. cpr (submodule)"
echo "2. cpp-tiktoken (submodule)"
echo "3. openai-api-cpp (module)"

read -p "Enter your choice (1, 2, or 3): " choice

case $choice in
  1)
    # Build cpr submodule
    cd submodules/cpr || (echo "Error: Missing 'submodules/cpr'" && exit 1)
    mkdir -p build
    cd build || (echo "Error: Building 'submodules/cpr' failed" && exit 1)
    cmake ..
    make

    echo "cpr submodule build completed."
    ;;

  2)
    # Build cpp-tiktoken submodule
    cd submodules/cpp-tiktoken || (echo "Error: Missing 'submodules/cpp-tiktoken'" && exit 1)
    mkdir -p build
    cd build || (echo "Error: Building 'submodules/cpp-tiktoken' failed" && exit 1)
    cmake ..
    make

    echo "cpp-tiktoken submodule build completed."
    ;;

  3)
    # Build openai-api-cpp module
    mkdir -p build
    cd build || (echo "Error: Building 'submodules/pybind11' failed" && exit 1)
    cmake ..
    make

    echo "openai-api-cpp build completed."
    ;;


  *)
    echo "Invalid choice. Exiting."
    exit 1
    ;;
esac

# Return to the repository root directory
cd ../../../
