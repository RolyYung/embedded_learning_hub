/*
请编写一个程序，在reverseArray()函数中使用指针实现数组的反转。reverseArray函数有两个输入参数，一个是数组的指针，另一个是数组中的元素个数。数组初始有5个元素

*/
#include <stdio.h>

void reverseArray(int *arr, int size){
    for (int i = 0; i < size / 2; i++)
    {
        int temp = arr[i];
        arr[i] = arr[size - i -1];
        arr[size - i -1] = temp;
    }
    
}
int main(){
    int arr[5] = {1,2,3,4,5};
    reverseArray(arr, 5);
    for (int i = 0; i < 5; i++)
    {
        printf("%d \n", arr[i]);
    }
    
    return 0;
}