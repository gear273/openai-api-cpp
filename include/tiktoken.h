#ifndef TIKTOKEN_H
#define TIKTOKEN_H

#include "../submodules/pybind11/include/pybind11/pybind11.h"
#include "../submodules/pybind11/include/pybind11/stl.h"

#include <string>
#include <vector>

class TikToken
{
public:
    // Constructor
    TikToken(const std::string &model);

    // Get the encoding type
    std::string get_encoding();

    // Encode a message
    std::vector<int> encode(const std::string &message);

    // Count the number of tokens in a string
    int get_token_count(const std::string &string);

    // Decode a message
    std::string decode(const std::vector<int> &tokens);

    // Decode a single token
    std::string decode_single_token_bytes(int token);
};

#endif
