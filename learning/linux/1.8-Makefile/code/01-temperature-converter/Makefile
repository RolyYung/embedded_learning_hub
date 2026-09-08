CC = gcc
foo = c
TARGET = temperature

$(TARGET): main.o
	$(CC) $< -o $(TARGET)
main.o: 
	$(CC) -${foo} main.c -o $@
.PHONY: clean

clean: 
	rm -f *.o ${TARGET}
