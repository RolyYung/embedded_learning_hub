#include "student.h"

// only modify student.c
double student_average(const Student students[], size_t count)
{
    size_t i;
    int sum = 0;

    if (count == 0) {
        return 0.0;
    }
    for (i = 0; i < count; ++i) {
        sum += students[i].score;
    }
    return (double)sum / (double)count;
}

const Student *student_best(const Student students[], size_t count)
{
    size_t i;
    const Student *best;

    if (count == 0) {
        return NULL;
    }
    best = &students[0];
    for (i = 1; i < count; ++i) {
        if (students[i].score > best->score) {
            best = &students[i];
        }
    }
    return best;
}
