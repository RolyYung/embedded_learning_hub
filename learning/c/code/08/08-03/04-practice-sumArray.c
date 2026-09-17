// 请编写一个程序，定义一个函数 sumArray，计算一个整数数组的总和。
#include <stdio.h>
int sumArray(int *arr, int size);

int main(){
    int arr[5] = {1,2,3,4,5};
    int sum = sumArray(arr, sizeof(arr)/sizeof(int));
    printf("%d", sum);
    return 0;
}

int sumArray(int *arr, int size){
    int result = 0;
    for (int i = 0; i < size; i++)
    {
        result += arr[i];
    }
    return result;
    
}