#ifndef STUDENT_H
#define STUDENT_H

// only modify student.h
#include <stddef.h>

typedef struct {
    const char *name;
    int score;
} Student;

double student_average(const Student students[], size_t count);
const Student *student_best(const Student students[], size_t count);

#endif
