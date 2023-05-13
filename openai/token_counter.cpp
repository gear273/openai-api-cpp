#include <iostream>
#include "../include/tiktoken.h"

int main()
{
    // Create an instance of the TikToken class
    TikToken tiktoken;

    // Get the encoding for a specific model
    std::string encoding = tiktoken.get_encoding_for_model("gpt-3.5-turbo");

    // Prompt the user for input
    std::cout << "Enter a string: ";
    std::string input;
    std::getline(std::cin, input);

    // Count the number of tokens in the string
    int token_count = tiktoken.get_token_count(input, encoding);

    std::cout << "The string '" << input << "' contains " << token_count << " tokens." << std::endl;

    return 0;
}
