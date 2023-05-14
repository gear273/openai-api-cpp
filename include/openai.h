#ifndef OPENAI_API_H
#define OPENAI_API_H

#include "../submodules/cpr/include/cpr/cpr.h"
#include "../submodules/json/single_include/nlohmann/json.hpp"
#include <string>

namespace OpenAI_API {
const std::string URL = "https://api.openai.com/v1";
const std::string MODELS = URL + "/models";
const std::string COMPLETIONS = URL + "/completions";
const std::string CHAT_COMPLETIONS = URL + "/chat/completions";
} // namespace OpenAI_API

class OpenAI {
  private:
    std::string api_key;
    cpr::Header get_headers();

  public:
    OpenAI(const std::string &api_key);

    cpr::Response models();

    cpr::Response completions(const std::string &prompt,
                              const std::string &model = "text-davinci-003",
                              int max_tokens = 16, float temperature = 0.7);

    cpr::Response chat_completions(const std::vector<std::string> &messages,
                                   const std::string &model = "gpt-3.5-turbo",
                                   int max_tokens = 512,
                                   float temperature = 0.7);
};

#endif
