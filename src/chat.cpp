#include <iostream>
#include "openai.h"

int main()
{
	// Enter your OpenAI API key
	std::string api_key = "<your-api-key>";

	// Create an instance of the OpenAI class
	OpenAI openai(api_key);

	// Prompt the user for input
	std::cout << "Enter a message: ";
	std::string message;
	std::getline(std::cin, message);

	// Call the chat_completions method
	cpr::Response response = openai.chat_completions({message});

	// Check if the API call was successful
	if (response.status_code == 200)
	{
		std::cout << "Response: " << response.text << std::endl;
	}
	else
	{
		std::cerr << "Error: " << response.status_code << std::endl;
		std::cerr << "Error message: " << response.error.message << std::endl;
	}

	return 0;
}