/*
 * 类型：practice
 * 主题：查找第二大元素
 * 日期：2026-07-30
 *
 * 题目：
 * 查找一个包含 5 个元素的整数数组中的第二大元素。
 */

#include <stdio.h>
#include <string.h>

int main(){
    int arr[5], max, second_max;
    for (int i = 0; i < 5; i++)
    {
        scanf("%d", &arr[i]);
    }
    max = second_max = arr[0];

    for (int i = 1; i < 5; i++)
    {
        if(arr[i] > max){
            second_max = max;
            max = arr[i];
        }else if(arr[i] > second_max && arr[i] != max){
            second_max = arr[i];
        }
        /* code */
    }
    printf("%d, %d", max, second_max);

    return 0;
}
