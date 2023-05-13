#include "../include/tiktoken.h"

namespace py = pybind11;

// Constructor
TikToken::TikToken(const std::string &model)
{
    py::module tiktoken = py::module::import("tiktoken");
    py::object TikToken = tiktoken.attr("TikToken");
    this->tiktoken_instance = TikToken(model);
}

// Get the encoding type
std::string TikToken::get_encoding()
{
    return this->tiktoken_instance.attr("get_encoding")().cast<std::string>();
}

// Encode a message
std::vector<int> TikToken::encode(const std::string &message)
{
    return this->tiktoken_instance.attr("encode")(message).cast<std::vector<int>>();
}

// Count the number of tokens in a string
int TikToken::num_tokens_from_string(const std::string &string)
{
    return this->tiktoken_instance.attr("num_tokens_from_string")(string).cast<int>();
}

// Decode a message
std::string TikToken::decode(const std::vector<int> &tokens)
{
    return this->tiktoken_instance.attr("decode")(tokens).cast<std::string>();
}

// Decode a single token
std::string TikToken::decode_single_token_bytes(int token)
{
    return this->tiktoken_instance.attr("decode_single_token_bytes")(token).cast<std::string>();
}
