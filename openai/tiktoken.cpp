#include "../include/tiktoken.h"

namespace py = pybind11;

// Constructor
TikToken::TikToken(void)
{
    tiktoken = py::module::import("tiktoken");
}

// Get the encoding type
py::object TikToken::get_encoding(const std::string &string)
{
    Encoding = tiktoken.attr("get_encoding");
    return Encoding(string);
}

py::object TikToken::get_encoding_for_model(const std::string &string)
{
    Encoding = tiktoken.attr("encoding_for_model");
    return Encoding(string);
}

// Encode a message
std::vector<int> TikToken::encode(const std::string &message)
{
    return Encoding.attr("encode")(message).cast<std::vector<int>>();
}

// Decode a message
std::string TikToken::decode(const std::vector<int> &tokens)
{
    return Encoding.attr("decode")(tokens).cast<std::string>();
}

// Decode a single token
std::string TikToken::decode_single_token_bytes(int token)
{
    return Encoding.attr("decode_single_token_bytes")(token).cast<std::string>();
}

// Count the number of tokens in a string
int TikToken::get_token_count(const std::string &string, const std::string &encoder_name)
{
    Encoding = tiktoken.attr("get_encoding")(encoder_name);
    return Encoding.attr("encode")(string).attr("__len__")().cast<int>();
}
