#!/usr/bin/env bash

function build() {
  local module_path="${1}"
  cd "${module_path}" || (echo "Error: Missing '$module_path'" && exit 1)
  mkdir -p build
  cd build || (echo "Error: Building '$module_path' failed" && exit 1)
  cmake .. || (echo "Error: Failed to locate CMakeLists.txt for '$module_path'" && exit 1)
  make || (echo "Error: Building '$module_path' failed" && exit 1)
  cd "${2}" || (echo "Error: Failed to exit '$module_path'" && exit 1)
}

# Prompt user to choose module to build
echo "Which module would you like to build?"
echo "1. cpr (submodule)"
echo "2. cpp-tiktoken (submodule)"
echo "3. openai-api-cpp (module)"

read -rp "Enter your choice (1, 2, or 3): " choice

case $choice in
  1)
    # Build cpr submodule
    build "submodules/cpr" ../../../
    echo "'submodules/cpr' build completed."
    ;;

  2)
    # Build cpp-tiktoken submodule
    build "submodules/cpp-tiktoken" ../../../
    echo "'submodules/cpp-tiktoken' build completed."
    ;;

  3)
    # Build openai-api-cpp module
    build "." ../
    cp -r ./submodules/cpp-tiktoken/build/tokenizers ./build/tokenizers
    echo "'openai-api-cpp' build completed."
    ;;

  *)
    echo "Invalid choice. Exiting."
    exit 1
    ;;
esac
