#include <iostream>
#include "openai.h"

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

cpr::Response OpenAI::completions(const std::string &prompt)
{
	cpr::Payload payload = {
		{"prompt", prompt}};

	return cpr::Post(cpr::Url{OpenAI_API::COMPLETIONS}, get_headers(), payload);
}

cpr::Response OpenAI::chat_completions(const std::vector<std::string> &messages)
{
	cpr::Payload payload = {
		{"messages", messages}};

	return cpr::Post(cpr::Url{OpenAI_API::CHAT_COMPLETIONS}, get_headers(), payload);
}
