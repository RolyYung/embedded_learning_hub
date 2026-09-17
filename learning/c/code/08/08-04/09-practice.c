/*
补全函数：
要求：
在函数内部申请一个int变量，让main函数可以访问。

*/

#include <stdio.h>
#include <stdlib.h>


void create(int **p)
{
    p = malloc(sizeof(int *));
    *p = malloc(sizeof(int));
}


int main()
{
    int *ptr = NULL;

    create(&ptr);

    *ptr = 50;

    printf("%d\n", *ptr);

    free(ptr);

    return 0;
}