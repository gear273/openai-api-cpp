#include "../include/tiktoken.h"

namespace py = pybind11;

// Constructor
TikToken::TikToken(void)
{
    py::module tiktoken = py::module::import("tiktoken");
}

// Get the encoding type
std::string TikToken::get_encoding(const std::string &string)
{
    py::object Encoding = tiktoken.attr("get_encoding");
    return Encoding(string).cast<std::string>();
}

std::string TikToken::get_encoding_for_model(const std::string &string)
{
    py::object Encoding = tiktoken.attr("encoding_for_model");
    return Encoding(string).cast<std::string>();
}

// Encode a message
std::vector<int> TikToken::encode(const std::string &message)
{
    py::object Encoding = tiktoken.attr("get_encoding");
    return Encoding(message).cast<std::vector<int>>();
}

// Decode a message
std::string TikToken::decode(const std::vector<int> &tokens)
{
    py::object Encoding = tiktoken.attr("get_encoding");
    return Encoding(tokens).cast<std::string>();
}

// Decode a single token
std::string TikToken::decode_single_token_bytes(int token)
{
    py::object Encoding = tiktoken.attr("get_encoding");
    return Encoding(token).cast<std::string>();
}

// Count the number of tokens in a string
int TikToken::get_token_count(const std::string &string, const std::string &encoder_name)
{
    py::object Encoding = tiktoken.attr("get_encoding");
    py::object encoded = Encoding(string);
    return len(encoded).cast<int>();
}
