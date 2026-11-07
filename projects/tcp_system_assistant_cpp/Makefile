CC = gcc
CXX = g++
CPPFLAGS = -I src/include
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic -I src/include

BUILD = build 

.PHONY: all clean

all: build/server build/client

build/server: build/server.o build/message.o
	@$(CXX) $^ -o $@
build/client: build/client.o build/message.o
	@$(CXX) $^ -o $@

build/server.o: src/server.cpp src/include/message.h src/include/socket_guard.hpp
	$(CXX) $(CPPFLAGS) -c $< -o $@

build/client.o: src/client.cpp src/include/message.h src/include/socket_guard.hpp
	$(CXX) $(CPPFLAGS) -c $< -o $@

build/message.o: src/lib/message.cpp src/include/message.h 
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(BUILD)/server $(BUILD)/client \
	      $(BUILD)/server.o $(BUILD)/client.o $(BUILD)/message.o
