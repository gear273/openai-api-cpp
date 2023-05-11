#include <iostream>
#include "../include/openai.h"

OpenAI::OpenAI(const std::string &api_key)
	: api_key(api_key)
{
}

cpr::Header OpenAI::get_headers()
{
	cpr::Header headers = {
		{"Authorization", "Bearer " + api_key},
		{"Content-Type", "application/json"}};

	return headers;
}

cpr::Response OpenAI::models()
{
	return cpr::Get(cpr::Url{OpenAI_API::MODELS}, get_headers());
}

cpr::Response OpenAI::completions(const std::string &prompt,
								  const std::string &model,
								  int max_tokens,
								  float temperature)
{
	nlohmann::json j = {
		{"model", model},
		{"prompt", prompt},
		{"max_tokens", max_tokens},
		{"temperature", temperature}};

	std::string payload = j.dump();

	return cpr::Post(
		cpr::Url{OpenAI_API::COMPLETIONS},
		get_headers(),
		cpr::Body{payload});
}

cpr::Response OpenAI::chat_completions(const std::vector<std::string> &messages,
									   const std::string &model,
									   int max_tokens,
									   float temperature)
{
	nlohmann::json j;

	for (const auto &message : messages)
	{
		j["messages"].push_back({{"role", "user"},
								 {"content", message}});
	}

	j["model"] = model;
	j["max_tokens"] = max_tokens;
	j["temperature"] = temperature;

	std::string payload = j.dump();

	return cpr::Post(cpr::Url{OpenAI_API::CHAT_COMPLETIONS}, get_headers(), cpr::Body{payload});
}
