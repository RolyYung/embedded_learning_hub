/*
分析下面三个函数：

char *func1()
{
    char str[] = "hello";

    return str;
}


char *func2()
{
    char *str = "hello";

    return str;
}


char *func3()
{
    char *str = malloc(6);

    strcpy(str, "hello");

    return str;
}

回答：

哪一个函数返回的指针可能失效？
哪一个函数返回后仍然可以访问？
哪一个函数需要调用 free()？
三个 "hello" 分别可能存放在哪里？
*/

/*
    哪一个函数返回的指针可能失效？: func1
    哪一个函数返回后仍然可以访问？: func2 func3
    哪一个函数需要调用 free()？: func 3
    三个 "hello" 分别可能存放在哪里？: 1. 栈 2. 常量区 3. 堆区
*/