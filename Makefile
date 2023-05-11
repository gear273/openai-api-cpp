CXX = g++

CXXFLAGS = -I./submodules/cpr/include \
	-I./submodules/cpr/build/cpr_generated_includes \
	-I./submodules/json/single_include \
	-Wall -Wextra -std=c++17 -fPIC

LDFLAGS = -L$(CURDIR)/submodules/cpr/build/lib \
	-Wl,-rpath=$(CURDIR)/submodules/cpr/build/lib \
	-lcpr

CHAT_BUILD_TARGET = build/chat
LIB_BUILD_TARGET = build/lib/libopenai.so

SOURCES = ./openai/openai.cpp
CHAT_SOURCES = ./openai/chat.cpp

OBJECTS = $(SOURCES:.cpp=.o)
CHAT_OBJECTS = $(CHAT_SOURCES:.cpp=.o)

all: $(LIB_BUILD_TARGET)

$(CHAT_BUILD_TARGET): $(OBJECTS) $(CHAT_OBJECTS) submodules/cpr/build/lib/libcpr.so
	mkdir -p build
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

$(LIB_BUILD_TARGET): $(OBJECTS) submodules/cpr/build/lib/libcpr.so
	mkdir -p build/lib
	$(CXX) $(CXXFLAGS) -shared -o $@ $^ $(LDFLAGS)
	mkdir -p build/include
	cp include/openai.h build/include/

library: $(LIB_BUILD_TARGET)

chat: $(CHAT_BUILD_TARGET)

build: library chat

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clones:
	git submodule add https://github.com/whoshuu/cpr.git submodules/cpr
	git submodule add https://github.com/nlohmann/json submodules/json
	git submodule init
	git submodule update

modules:
	git submodule update --init

submodules/cpr/build/lib/libcpr.so: submodules/cpr
	mkdir -p submodules/cpr/build
	cd submodules/cpr/build && cmake ..
	$(MAKE) -C submodules/cpr/build

clean:
	rm -rf $(OBJECTS) $(CHAT_OBJECTS) build/

.PHONY: all clones modules library chat build clean
