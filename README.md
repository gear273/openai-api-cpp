📝 This project and its contents were created with the assistance of OpenAI's GPT-3.5 and GPT-4.

# openai-api-cpp

A C++ wrapper for the OpenAI API. This library provides a simple interface to the OpenAI API, enabling users to generate text using OpenAI's powerful language models directly from their C++ applications.

## Dependencies

This project relies on the following libraries:

-   [libcpr/cpr](https://github.com/whoshuu/cpr) for making HTTP requests
-   [nlohmann/json](https://github.com/nlohmann/json) for handling JSON
-   [gh-markt/cpp-tiktoken](https://github.com/gh-markt/cpp-tiktoken) for handling tokens

## Building

To build this project, you'll need to clone the repository and its submodules, then use `make` to build the library and sample applications.

You can use the provided helper scripts to simplify the building process:

```sh
# Clone the repository
git clone https://github.com/teleprint-me/openai-api-cpp.git

cd openai-api-cpp

# Initialize and update submodules
./init.sh

# Build the cpr and pybind11 objects
./build.sh  # options 1, 2, and 3
```

This will create a shared library `libopenai.so` that you can link against in your C++ applications.

You can also run the example chat application:

```sh
# Run the chat application (make sure to replace YOUR_OPENAI_API_KEY with your actual API key)
OPENAI_API_KEY='YOUR_OPENAI_API_KEY' ./chat
```

You can store your key in an environment variable and use the `run.sh` script as a short-hand:

```sh
# Create the environment file (.env) to store the OpenAI API key as an environment variable
echo "OPENAI_API_KEY='YOUR_OPENAI_API_KEY'" > .env
# Build and run chat
./run.sh
```

Note: Wrap your API key in single quotes if an exception is raised due to the API key missing even while being present.

## Usage

Here's a simple example of how to use the library:

```cpp
// Retrieve the OpenAI API key from the environment variable
const char *api_key = std::getenv("OPENAI_API_KEY");

if (!api_key)
{
    std::cerr << "Error: OPENAI_API_KEY environment variable not set." << std::endl;
    return 1;
}

// Create an instance of the OpenAI class
OpenAI openai(api_key);

// Generate a completion
cpr::Response response = openai.completions("Once upon a time");

// Print the response
std::cout << "Response: " << response.text << std::endl;
```

Refer to the source code for more detailed usage examples.
