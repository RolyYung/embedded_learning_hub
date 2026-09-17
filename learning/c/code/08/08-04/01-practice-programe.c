// 请编写一个程序，在swap函数中利用指针交换两个整数的值。

#include <stdio.h>

void swap(int *a, int *b);
int main(){
    int x,y;
    printf("输入两个值: ");
    scanf("%d", &x);
    scanf("%d", &y);
    swap(&x, &y);
    printf("交换后两个值: %d, %d", x, y);
    return 0;
}

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}