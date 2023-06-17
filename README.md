# openai-api-cpp

This project provides a C++ wrapper for the OpenAI API. It offers a simple interface to the OpenAI API, allowing users to generate text using OpenAI's powerful language models directly from their C++ applications.

## Dependencies

The project relies on the following libraries:

-   [libcpr/cpr](https://github.com/libcpr/cpr) for making HTTP requests
-   [nlohmann/json](https://github.com/nlohmann/json) for handling JSON
-   [gh-markt/cpp-tiktoken](https://github.com/gh-markt/cpp-tiktoken) for handling tokens

## Building

To build this project, follow these steps:

1. Clone the repository and its submodules:

    ```sh
    git clone https://github.com/teleprint-me/openai-api-cpp.git
    cd openai-api-cpp
    ./init.sh
    ```

2. Use `cmake` to build the library and sample applications:

    ```sh
    ./build.sh  # options 1, 2, and 3
    ```

    The `build` directory will contain the following components:

    - `build/libopenai-api-cpp.so`: The core library as a shared object
    - `build/chat`: A simple example chat application built using the shared object
    - `build/token_counter`: A simple example token counting utility built using the shared object

3. Run the example chat application:

    ```sh
    OPENAI_API_KEY='YOUR_OPENAI_API_KEY' ./chat
    ```

    You can store your API key in an environment variable and use the `run.sh` script as a shorthand:

    ```sh
    echo "OPENAI_API_KEY='YOUR_OPENAI_API_KEY'" > .env
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

Please refer to the source code for more detailed usage examples.
