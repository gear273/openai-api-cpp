📝 This project and its contents were created with the assistance of OpenAI's GPT-3.5 and GPT-4.

# openai-api-cpp

A C++ wrapper for the OpenAI API. This library provides a simple interface to the OpenAI API, enabling users to generate text using OpenAI's powerful language models directly from their C++ applications.

## Dependencies

This project relies on the following libraries:

-   [cpr](https://github.com/whoshuu/cpr) for making HTTP requests
-   [nlohmann/json](https://github.com/nlohmann/json) for handling JSON

## Building

To build this project, you'll need to clone the repository and its submodules, then use `make` to build the library and sample applications.

You can use the provided helper scripts to simplify the building process:

```sh
# Clone the repository
git clone https://github.com/teleprint-me/openai-api-cpp.git

cd openai-api-cpp

# Initialize and update submodules
make modules

# Build the cpr objects
./build_cpr.sh

# Build the openai library
make
```

This will create a shared library `libopenai.so` that you can link against in your C++ applications.

You can also build and run the example chat application:

```sh
# Build the chat application
make chat

# Run the chat application (make sure to replace YOUR_OPENAI_API_KEY with your actual API key)
OPENAI_API_KEY=YOUR_OPENAI_API_KEY ./chat
```

You can store your key in an environment variable and use the `run.sh` script as a short-hand:

```sh
# Create the environment file
echo "OPENAI_API_KEY=YOUR_API_KEY" > .env
# Build and run chat
./run.sh
```

## Usage

Here's a simple example of how to use the library:

```cpp
// Create an instance of the OpenAI class
OpenAI openai("your-openai-api-key");

// Generate a completion
cpr::Response response = openai.completions("Once upon a time");

// Print the response
std::cout << "Response: " << response.text << std::endl;
```

Refer to the source code for more detailed usage examples.

## Make Commands

This project has several `make` commands to facilitate various operations:

-   `make`: Builds the `libopenai.so` shared library.
-   `make chat`: Builds the `chat` example application.
-   `make modules`: Runs `git submodule update --init`, useful for initializing and updating submodules.
-   `make clean`: Cleans up the built files.
