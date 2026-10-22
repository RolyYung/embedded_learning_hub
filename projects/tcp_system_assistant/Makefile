CC = gcc
CPPFLAGS = -I src/include

BUILD = build

.PHONY: all clean

all: build/server build/client

build/server: build/server.o build/message.o
	@gcc $^ -o $@
build/client: build/client.o build/message.o
	@gcc $^ -o $@

build/server.o: src/server.c src/include/message.h 
	$(CC) $(CPPFLAGS) -c $< -o $@

build/client.o: src/client.c src/include/message.h 
	$(CC) $(CPPFLAGS) -c $< -o $@

build/message.o: src/lib/message.c src/include/message.h 
	$(CC) $(CPPFLAGS) -c $< -o $@

clean:
	rm -f $(BUILD)/server $(BUILD)/client \
	      $(BUILD)/server.o $(BUILD)/client.o $(BUILD)/message.o