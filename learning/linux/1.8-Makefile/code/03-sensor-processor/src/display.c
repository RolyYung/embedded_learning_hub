#include <stdio.h>
#include "display.h"

void display_result(double average, unsigned int sample_count)
{
    printf("样本数: %u\n", sample_count);
    printf("平均温度: %.2f C\n", average);
}
