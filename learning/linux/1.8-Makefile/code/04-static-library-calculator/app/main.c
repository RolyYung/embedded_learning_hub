#include <stdio.h>
#include "calc.h"

int main(void)
{
    printf("7 + 5 = %d\n", calc_add(7, 5));
    printf("7 - 5 = %d\n", calc_subtract(7, 5));
    printf("7 * 5 = %d\n", calc_multiply(7, 5));
    return 0;
}
