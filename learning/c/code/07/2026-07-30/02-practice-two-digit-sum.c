/*
 * 类型：practice
 * 主题：两位数各位之和
 * 日期：2026-07-30
 *
 * 题目：
 * 输出所有十位和个位之和等于 8 的两位数。
 */

#include <stdio.h>
int main(){
    for (int i = 10; i < 100; i++)
    {
        /* code */
        int ones = i % 10;
        int tens = i / 10;
        if(ones + tens == 8){
            printf("%d\n", i);
        }
    }

    return 0;
}
