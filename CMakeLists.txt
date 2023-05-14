cmake_minimum_required(VERSION 3.1.2)

project(openai-api-cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -fPIC")

# Specify the directories where the compiler can find the headers
include_directories(include
    submodules/cpr/include
    submodules/cpr/build/cpr_generated_includes
    submodules/json/single_include
    submodules/cpp-tiktoken)

# Specify the directories where the linker can find the libraries
link_directories(submodules/cpr/build/lib)
link_directories(submodules/cpp-tiktoken/build)

# Specify the source files
set(SOURCES openai/openai.cpp)
set(CHAT_SOURCES examples/chat.cpp)
set(TOKEN_COUNTER_SOURCES examples/token_counter.cpp)

# Specify the target executable and the files to compile for it
add_library(openai-api-cpp SHARED ${SOURCES})
add_executable(chat ${SOURCES} ${CHAT_SOURCES})
add_executable(token_counter ${SOURCES} ${TOKEN_COUNTER_SOURCES})

# Specify the libraries to link against
target_link_libraries(openai-api-cpp cpr)
target_link_libraries(chat openai-api-cpp)
target_link_libraries(token_counter openai-api-cpp tiktoken pcre2-8)

# Install targets
install(TARGETS openai-api-cpp DESTINATION lib)
install(FILES include/openai.h DESTINATION include)
