CC := gcc
CFLAGS := -Wall -std=c11

SRCS := $(wildcard src/*.c)
OBJS := $(patsubst src/%.c, build/%.o, $(SRCS))
HEADERS := $(wildcard include/*.h)
TARGET := build/sensor_processor

$(TARGET): $(OBJS) $(HEADERS) build/
	$(CC) $(OBJS) -o $(TARGET)
build/%.o:  src/%.c ${HEADERS} build/
	$(CC) $(CFLAGS) -c $< -o $@ -I include/
build/: 
	mkdir build

.PHONY: clean

clean: build/
	rm -rf $<


