/*
二、柱状图中的最大矩形【难度：⭐⭐⭐】
设计一个函数，传递一个int类型数组，返回该数组中最大矩形的面积
功能：数组中每个元素带班柱状图柱子的高度，所有柱子宽度均为1。计算柱状图中能够勾勒出的最大矩形面积

例子:  2, 1, 5, 6, 3
*/
#include <stdio.h>

int calc_max(int * arr, int size){
    int result = 0;
    for (int i = 0; i < size; i++)
    {
        if(arr[i] > result){
            result = arr[i];
        }
        int min_num = arr[i];
        for (int j = i; j < size; j++)
        {
            if(arr[j] < min_num){
                min_num = arr[j];
            }
            if(min_num*((j-i)+1) > result){
                result = min_num*((j-i)+1);
            }
        }
    }
    return result;
    
}

int main(){
    int arr[5] = {2,1,3,6,3};
    int result = calc_max(arr, 5);
    printf("%d", result);
    return 0;

}