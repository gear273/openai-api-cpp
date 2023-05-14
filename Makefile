CXX = g++

CXXFLAGS = -I/usr/include/python3.11 \
	-I./submodules/pybind11/include \
	-I./submodules/cpr/include \
	-I./submodules/cpr/build/cpr_generated_includes \
	-I./submodules/json/single_include \
	-Wall -Wextra -std=c++17 -fPIC

LDFLAGS = -L$(CURDIR)/submodules/cpr/build/lib \
	-Wl,-rpath=$(CURDIR)/submodules/cpr/build/lib \
	-lcpr -lpython3.11

TOKEN_COUNTER_BUILD_TARGET = build/token_counter
CHAT_BUILD_TARGET = build/chat
LIB_BUILD_TARGET = build/lib/libopenai.so

SOURCES = openai/openai.cpp
CHAT_SOURCES = openai/chat.cpp
TOKEN_COUNTER_SOURCES = openai/token_counter.cpp
TIKTOKEN_SOURCES = openai/tiktoken.cpp

OBJECTS = $(SOURCES:.cpp=.o)
CHAT_OBJECTS = $(CHAT_SOURCES:.cpp=.o)
TOKEN_COUNTER_OBJECTS = $(TOKEN_COUNTER_SOURCES:.cpp=.o)
TIKTOKEN_OBJECTS = $(TIKTOKEN_SOURCES:.cpp=.o)

all: $(LIB_BUILD_TARGET)

$(CHAT_BUILD_TARGET): $(OBJECTS) $(CHAT_OBJECTS) $(TIKTOKEN_OBJECTS) submodules/cpr/build/lib/libcpr.so
	mkdir -p build
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(TOKEN_COUNTER_BUILD_TARGET): $(OBJECTS) $(TOKEN_COUNTER_OBJECTS) $(TIKTOKEN_OBJECTS) submodules/cpr/build/lib/libcpr.so
	mkdir -p build
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(LIB_BUILD_TARGET): $(OBJECTS) $(TIKTOKEN_OBJECTS) submodules/cpr/build/lib/libcpr.so
	mkdir -p build/lib
	$(CXX) $(CXXFLAGS) -shared -o $@ $^ $(LDFLAGS)
	mkdir -p build/include
	cp include/openai.h build/include/
	cp include/tiktoken.h build/include/

library: $(LIB_BUILD_TARGET)

chat: $(CHAT_BUILD_TARGET)

token_counter: $(TOKEN_COUNTER_BUILD_TARGET)

build: library chat token_counter

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clones:
	git submodule add https://github.com/whoshuu/cpr.git submodules/cpr
	git submodule add https://github.com/nlohmann/json submodules/json
	git submodule add https://github.com/pybind/pybind11.git submodules/pybind11
	git submodule init
	git submodule update

modules:
	git submodule update --init

submodules/cpr/build/lib/libcpr.so: submodules/cpr
	mkdir -p submodules/cpr/build
	cd submodules/cpr/build && cmake ..
	$(MAKE) -C submodules/cpr/build

clean:
	rm -rf $(OBJECTS) $(CHAT_OBJECTS) $(TOKEN_COUNTER_OBJECTS) $(TIKTOKEN_OBJECTS) build/

.PHONY: all clones modules library chat token_counter build clean
