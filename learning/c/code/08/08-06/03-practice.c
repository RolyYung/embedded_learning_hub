/*
请编写一个程序，使用scanf为一个有10个元素的数组初始化0~10的数字，统计其中每个元素出现的次数。
*/

#include <stdio.h>

int main(){
    int arr[10];
    printf("请输入一个0~10的数字: \n");
    for (int i = 0; i < 10; i++)
    {   
        printf("这是第%d个: ", i+1);
        scanf("%d", &arr[i]);
    }
    int count[11] = {0};
    for (int i = 0; i < 10; i++)
    {
        count[arr[i]]++;
    }
    for (int i = 0; i < 11; i++)
    {
        printf("%d出现次数: %d \n", i, count[i]);
    }
    
    
    
    return 0;
}