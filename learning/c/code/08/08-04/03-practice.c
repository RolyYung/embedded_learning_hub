/*
请编写一个程序，使用calculateAverage()函数利用指针计算数组中元素的平均值。该函数的输入参数有两个，一个是数组的指针，另一个是元素的数量。数组初始有5个元素
*/

#include <stdio.h>
float calculateAverage(int *arr, int size);
int main(){
    int arr[5] = {1,2,3,4,5};
    float avg = calculateAverage(arr, 5);
    printf("平均值: %f", avg);
    return 0;
}

float calculateAverage(int *arr, int size){
    int sum=0;
    for (int i = 0; i < size; i++)
    {
        /* code */
        sum += arr[i];
    }
    return sum / size;
    
}