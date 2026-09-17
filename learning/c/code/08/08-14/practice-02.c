/*
请编写一个顺序查找算法，查找给定数组中是否存在指定元素，并输出结果。

题目提示：
题目描述:
请编写一个C语言程序，使用顺序查找算法查找一个给定的元素是否在数组中。程序需要接收一个整数数组和一个目标值，输出目标值是否在数组中，若在则输出“Found”，否则输出“Not Found”。

输入:

一个整数数组，长度不超过100。
一个整数，表示要查找的目标值。
输出:

如果数组中存在目标值，输出“Found”。
如果数组中不存在目标值，输出“Not Found”。
示例输入:

arr = {12, 34, 55, 22, 77, 89}
target = 22
​
示例输出:

Found*/

#include <stdio.h>
#define MAX_LENGTH 100

void isInArray(int *arr, int val){
    for (int i = 0; i < MAX_LENGTH; i++)
    {
        if(arr[i] == val){
            printf("Found */");
            return;
        }
    }
    printf("Not Found");
}
int main(){
    int arr[MAX_LENGTH] = {0};
    int index = 0;
    int input = -1;
    while (input != 0)   
    {
        printf("输入数组值: (0结束)");
        scanf("%d", &input);
        arr[index] = input;
        index++;
    }
    int val;
    printf("输入你想查找的值:");
    scanf("%d", &val);
    isInArray(arr, val);
    

    return 0;
}