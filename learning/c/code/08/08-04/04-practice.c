/*

请编写一个程序，在主函数中使用指针动态分配有5个int型变量长度的内存，并将该指针输入进sumArray()函数计算数组元素的和。
*/
#include <stdio.h>
#include <stdlib.h>

int sumArray(int *arr, int size);
int main(){
    int *p = (int *)malloc(5*sizeof(int));
    for (int i = 0; i < 5; i++)
    {
        p[i] = i+1;
    }
    int sum = sumArray(p, 5);
    printf("%d \n", sum);
    return 0;
}

int sumArray(int *arr, int size){
    int sum = 0;
    for (int i = 0; i < size; i++)
    {
        sum += arr[i];
    }
    return sum;
    
}