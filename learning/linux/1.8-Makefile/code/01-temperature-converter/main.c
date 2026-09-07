#include <stdio.h>
#include <string.h>

static void print_usage(const char *program)
{
    printf("用法: %s <c2f|f2c> <温度>\n", program);
}

int main(int argc, char *argv[])
{
    double value;

    if (argc != 3 || sscanf(argv[2], "%lf", &value) != 1) {
        print_usage(argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "c2f") == 0) {
        printf("%.2f C = %.2f F\n", value, value * 9.0 / 5.0 + 32.0);
    } else if (strcmp(argv[1], "f2c") == 0) {
        printf("%.2f F = %.2f C\n", value, (value - 32.0) * 5.0 / 9.0);
    } else {
        print_usage(argv[0]);
        return 1;
    }

    return 0;
}
