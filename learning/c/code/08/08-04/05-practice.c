/*
请编写一个程序，在findMax()函数中输入数组指针和元素数量，使用指针在数组中查找最大值，返回最大值给主函数并在主函数中打印出来。
*/
#include <stdio.h>

int findMax(int *arr, int size);
int main(){
    int arr[5] = {3,8 ,10, 2, 1};
    int max = findMax(arr, 5);
    printf("最大值是: %d", max);
    return 0;
}

int findMax(int *arr, int size){
    int max = arr[0];
    for (int i = 0; i < size; i++)
    {
        if(arr[i] > max){
            max = arr[i];
        }
    }
    return max;
    
}