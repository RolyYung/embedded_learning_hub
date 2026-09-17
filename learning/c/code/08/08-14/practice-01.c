/*
请编写一个顺序查找算法，查找数组中目标值的所有位置并输出。

题目提示：
题目描述:
请编写一个C语言程序，使用顺序查找算法查找一个给定元素在数组中的所有位置（索引），并输出这些索引。如果目标值在数组中不存在，则输出"Not Found"。

输入:

一个整数数组，长度不超过1000。
一个整数，表示要查找的目标值。
输出:

如果数组中有目标值，输出目标值所在的所有位置（索引）。
如果目标值不存在，输出"Not Found"。
示例输入:

arr = {12, 34, 22, 34, 77, 34}
target = 34
​
示例输出:

1 3 5
*/

#include <stdio.h>


int findPostion(int *arr, int length, int val, int *result){
    int index = 0;
    for (int i = 0; i < length; i++)
    {
        if(val == arr[i]){
            result[index] = i;
            index ++;
        }
    }
    if(index == 0){
        printf("Nou Found");
        return -1;
    }
    return index;
    
}

int main(){
    int a = -1;
    int arr[1000];
    int index = 0;
    while (a != 0)   
    {
        printf("输入数组数字: (0结束)");
        scanf("%d", &a);
        arr[index] = a;
        index++;
    }
    int val;
    printf("输入您想要找的值");
    scanf("%d", &val);
    int result[1000];
    int resLength = findPostion(arr, 1000, val,result);
    for (int i = 0; i < resLength; i++)
    {
        printf("%d \t", result[i]);
    }
    
    
    
    return 0;
}