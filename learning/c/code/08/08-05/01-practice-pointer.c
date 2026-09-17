/*
题目1：动态内存 + 指针生命周期（重点）

判断下面代码有没有问题，如果有问题，指出具体哪里错，以及为什么。

#include <stdio.h>
#include <stdlib.h>

int *create()
{
    int a = 100;

    int *p = malloc(sizeof(int));

    *p = a;

    return &a;
}

int main()
{
    int *ptr = create();

    printf("%d\n", *ptr);

    free(ptr);

    return 0;
}

请回答：

ptr 最终指向哪里？
printf("%d", *ptr) 是否安全？
free(ptr) 是否正确？
如果要修改，让函数返回一个有效的整数地址，你有几种方法？
*/

/*
    ptr 指向了内存已经被释放的内存空间, 即悬空指针
    printf("%d", *ptr) 不安全, 会有可能出现段错误. 即读取了一个不属于程序的内存地址的值, 会被报错.
    free(ptr) 不正确
    修改方案1: static int a = 10;
    方案2: return p;
    方案3: int *p = 10; return p
*/