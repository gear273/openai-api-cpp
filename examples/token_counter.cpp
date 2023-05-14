#include "../submodules/cpp-tiktoken/encoding.h"
#include <iostream>
#include <string>
#include <vector>

int main() {
    // Get the encoding for a specific model
    auto encoder = GptEncoding::get_encoding(LanguageModel::CL100K_BASE);

    // Prompt the user for input
    std::cout << "Enter a string: ";
    std::string input;
    std::getline(std::cin, input);

    // Encode the input string
    std::vector<int> tokens = encoder->encode(input);

    // The number of tokens is the size of the returned vector
    int token_count = tokens.size();

    std::cout << "The string '" << input << "' contains " << token_count
              << " tokens." << std::endl;

    return 0;
}
