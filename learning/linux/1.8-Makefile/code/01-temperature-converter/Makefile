CC = gcc
foo = c
TARGET = temperature

$(TARGET): main.o
	$(CC) $< -o $@ -Wall -std=c11
main.o: main.c 
	$(CC) -${foo} $< -o $@ -Wall -std=c11

.PHONY: run

run: 
	./${TARGET} c2f 100

.PHONY: help

help: 
	@echo "usage run: make run"
	@echo "usage clean: make clean"
	@echo "usage default: make"


.PHONY: clean

clean: 
	rm -f *.o $(TARGET)
