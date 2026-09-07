#include "report.h"

int main(void)
{
    const Student students[] = {
        {"Alice", 86}, {"Bob", 93}, {"Chen", 78}, {"Diana", 91}
    };

    report_print(students, sizeof(students) / sizeof(students[0]));
    return 0;
}
