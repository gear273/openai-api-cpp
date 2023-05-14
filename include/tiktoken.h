#ifndef TIKTOKEN_H
#define TIKTOKEN_H

#include "../submodules/pybind11/include/pybind11/pybind11.h"
#include "../submodules/pybind11/include/pybind11/stl.h"

#include <string>
#include <vector>

class TikToken {
  private:
    pybind11::object tiktoken;
    pybind11::object Encoding;

  public:
    // Constructor
    TikToken();

    std::string get_encoding_for_model(const std::string &string);

    // Encode a message
    std::vector<int> encode(const std::string &message);

    // Decode a message
    std::string decode(const std::vector<int> &tokens);

    // Decode a single token
    std::string decode_single_token_bytes(int token);

    // Count the number of tokens in a string
    int get_token_count(const std::string &string,
                        const std::string &encoder_name);
};

#endif
