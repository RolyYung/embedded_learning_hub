CC = gcc
foo = c
TARGET = temperature

$(TARGET): main.o
	$(CC) $< -o $@
main.o: main.c 
	$(CC) -${foo} $< -o $@
.PHONY: clean

clean: 
	rm -f *.o $(TARGET)
