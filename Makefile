CXX = g++

CXXFLAGS = -I./submodules/cpr/include \
	-I./submodules/cpr/build/cpr_generated_includes \
	-I./submodules/json/single_include \
	-Wall -Wextra -std=c++17

LDFLAGS = -L$(CURDIR)/submodules/cpr/build/lib \
	-Wl,-rpath=$(CURDIR)/submodules/cpr/build/lib \
	-lcpr

TARGET = chat

SOURCES = ./src/openai.cpp ./src/chat.cpp

OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS) submodules/cpr/build/lib/libcpr.so
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

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
	rm -f $(TARGET) $(OBJECTS)

.PHONY: all clones modules clean