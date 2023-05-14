#include "../include/openai.h"
#include <cstdlib>
#include <iostream>

int main() {
    // Retrieve the OpenAI API key from the environment variable
    const char *api_key = std::getenv("OPENAI_API_KEY");

    if (!api_key) {
        std::cerr << "Error: OPENAI_API_KEY environment variable not set."
                  << std::endl;
        return 1;
    }

    // Create an instance of the OpenAI class
    OpenAI openai(api_key);

    std::vector<std::string> messages;

    // Prompt the user for a system message
    std::cout << "Enter a system message: ";
    std::string system_message;
    std::getline(std::cin, system_message);
    messages.push_back(system_message);

    while (true) {
        // Prompt the user for input
        std::cout << "User: ";
        std::string user_message;
        std::getline(std::cin, user_message);

        if (user_message == "quit") {
            break;
        }

        messages.push_back(user_message);

        // Call the chat_completions method
        cpr::Response response = openai.chat_completions(messages);

        // Check if the API call was successful
        if (response.status_code == 200) {
            // Parse response JSON
            nlohmann::json j = nlohmann::json::parse(response.text);

            // Get the model's message content
            std::string model_message = j["choices"][0]["message"]["content"];

            // Add model's message to the messages vector
            messages.push_back(model_message);

            std::cout << "GPT: " << model_message << std::endl;
        } else {
            std::cerr << "Error: " << response.status_code << std::endl;
            std::cerr << "Error message: " << response.error.message
                      << std::endl;
        }
    }

    return 0;
}
