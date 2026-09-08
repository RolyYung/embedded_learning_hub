CC = gcc
compile = c
output = o
warn = Wall
std = std=c11
TARGET = temperature

$(TARGET): main.o
	$(CC) $< -$(output) $@ -$(warn) -$(std)
main.o: main.c 
	$(CC) -$(compile) $< -$(output) $@ -$(warn) -$(std)

.PHONY: run help clean

run: $(TARGET) 
	./${TARGET} c2f 100

help: 
	@echo "usage run: make run"
	@echo "usage clean: make clean"
	@echo "usage default: make"

clean: 
	rm -f *.o $(TARGET)
