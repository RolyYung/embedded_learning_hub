/*
    题目3：类型转换 + 内存大小综合题（嵌入式高频）

假设：

int = 4字节
unsigned int = 4字节

代码：

#include <stdio.h>

int main()
{
    unsigned int len = 0;

    int size = sizeof(len);

    if(size - 5 < 0)
    {
        printf("A");
    }
    else
    {
        printf("B");
    }


    return 0;
}

回答：

sizeof(len) 返回什么类型？
size - 5 的计算过程中会发生什么类型转换？
最终输出 A 还是 B？
如果把：
int size

改成：

unsigned int size

结果会不会变化？为什么？
*/

/*
sizeof 函数返回的size_t, 应该是unsigned long类型
size - 5 的计算过程中会发生什么类型转换？  不清楚
最终输出 A 还是 B？ 输出A
不会发生变化
*/
