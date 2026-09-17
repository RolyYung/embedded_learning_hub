#include <stdio.h>

int main()
{
    int x = 5;
    // int y = ++x + x++;
    int z = x++ + ++x;
    printf("%d", z);
    return 0;
}