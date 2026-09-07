#include <stdio.h>
#include "report.h"

void report_print(const Student students[], size_t count)
{
    const Student *best = student_best(students, count);
    size_t i;

    puts("学生成绩:");
    for (i = 0; i < count; ++i) {
        printf("  %-8s %d\n", students[i].name, students[i].score);
    }
    printf("平均分: %.2f\n", student_average(students, count));
    if (best != NULL) {
        printf("最高分: %s (%d)\n", best->name, best->score);
    }
}
