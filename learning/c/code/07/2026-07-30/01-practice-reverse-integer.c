/*
 * 类型：practice
 * 主题：反转整数
 * 日期：2026-07-30
 *
 * 题目：
 * 输入一个整数，输出其反向数字（不是字符）。
 * 例如输入 12345，输出 54321。
 */

#include <stdio.h>

int main(){
    int num, reversed = 0;
    printf("请输入一个整数：");
    scanf("%d", &num);
    while (num != 0)
    {
        reversed = reversed * 10 + num % 10;
        num = num / 10;
    }
    printf("%d", reversed);

    return 0;
}
