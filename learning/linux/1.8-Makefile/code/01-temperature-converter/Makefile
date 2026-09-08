CC = gcc
CFLAGS = -Wall -std=c11
TARGET = temperature

$(TARGET): main.o
	$(CC) $< -o $@ $(CFLAGS)
main.o: main.c 
	$(CC) -c $< -o $@

.PHONY: run help clean

run: $(TARGET) 
	./$< c2f 100

help: 
	@echo "usage run: make run"
	@echo "usage clean: make clean"
	@echo "usage default: make"

clean: 
	rm -f *.o $(TARGET)
