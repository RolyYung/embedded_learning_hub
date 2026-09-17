/*
请编写一个C语言程序，实现二分查找算法。给定一个已排序的整数数组arr[] = {1, 3, 5, 7, 9, 11, 13};和一个目标值，判断目标值是否在数组中。若存在，输出目标值在数组中的下标（从0开始），否则输出“Not Found”。
*/

#include <stdio.h>

void findTarget(int *arr, int length, int target){
    
    int low = 0;
    int high = length - 1;
    int mid = 0;
    while(low <= high){
        mid = (high + low) / 2;
        if(target < arr[mid]){
            high = mid-1;
        }else if(target == arr[mid]){
            printf("Found */");
            return;
        }else if(target > arr[mid]){
            low = mid+1;
        }
    }
    printf("Not Found");
    return ;
}

int main(){
    int arr[] = {1, 3, 5, 7, 9, 11, 13};
    int target = 14;
    findTarget(arr, 7, target);
    return 0;
}