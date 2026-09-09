CC = gcc
INCLUDE = -I ./include/
TARGET = student_manager
OBJS = main.o student.o report.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $^ -o $@ $(INCLUDE)

main.o: main.c include/report.h include/student.h
	$(CC) -c $< -o $@ $(INCLUDE)
student.o: student.c include/student.h
	$(CC) -c $< -o $@ $(INCLUDE)
report.o: report.c include/report.h include/student.h
	$(CC) -c $< -o $@ $(INCLUDE)

.PHONY: clean run all

clean: 
	rm -f $(OBJS) $(TARGET)

run: $(TARGET) 
	./$<
