// 测试没有register关键字下, 大数据循环的时间.
// 测试目的: 直观感受register关键字的作用: 调用运行速度快.

/*
    register 不保证变量一定进入寄存器；
    现代编译器通常会自动完成寄存器分配。
    当前测试的大量 printf 和粗粒度计时掩盖了任何可能的细微差异。
*/

#include <stdio.h>
#include <time.h>

int main(){
    time_t start, end;
    time(&start);
    printf("程序开始时间戳: %ld\n", start);
    for (int i = 0; i < 999; i++)
    {
        for (int j = 0; j < 999; j++)
        {
            int a = i + j;
            printf("%d", a);
        }
        
    }
    time(&end);
    printf("程序开始时间戳: %ld\n", start);
    printf("程序结束时间戳: %ld\n", end);
    
    return 0;
}