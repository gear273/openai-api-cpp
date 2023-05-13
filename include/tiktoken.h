#pragma once

#include <string>
#include <vector>

class TikToken {
public:
    TikToken();
    std::vector<std::string> tokenize(const std::string& text);
    int count_tokens(const std::string& text);
};
