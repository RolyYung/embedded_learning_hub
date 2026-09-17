/*
 * 类型：practice
 * 主题：反转数组
 * 日期：2026-07-30
 *
 * 题目：
 * 反转一个包含 5 个元素的整数数组。
 */

#include <stdio.h>
int main(){
    int arr[5];
    for (int i = 0; i < 5; i++)
    {
        scanf("%d", &arr[i]);
    }

    for (int i = 0; i < 5 / 2; i++)
    {
        int temp = arr[i];
        arr[i] = arr[5 - i - 1];
        arr[5 - i - 1] = temp;
    }

    for (int i = 0; i < 5; i++)
    {
        printf("%d ", arr[i]);
    }



    return 0;
}
