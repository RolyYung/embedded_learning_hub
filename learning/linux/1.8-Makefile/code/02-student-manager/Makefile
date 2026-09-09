CC = gcc
INCLUDE = -I ./include/
TARGET = student_manager

all: $(TARGET)

$(TARGET): main.o student.o report.o
	gcc $^ -o $@ $(INCLUDE)

main.o: main.c include/report.h include/student.h
	gcc -c $< -o $@ $(INCLUDE)
student.o: student.c include/student.h
	gcc -c $< -o $@ $(INCLUDE)
report.o: report.c include/report.h include/student.h
	gcc -c $< -o $@ $(INCLUDE)

.PHONY: clean run all

clean: 
	rm -f *.o $(TARGET)

run: 
	./$(TARGET)
