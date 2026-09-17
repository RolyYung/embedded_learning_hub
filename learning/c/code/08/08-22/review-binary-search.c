/*
    二分查找代码
*/

#include <stdio.h>

int binary_search(int *arr, int length, int target){
    int left = 0;
    int right = length - 1;

    while (left <= right)
    {   
        int mid = (left+right) / 2;
        if(arr[mid] == target){
            return mid;
        }else if(arr[mid] > target){
            right = mid-1;
        }else{
            left = mid+1;
        }
    }
    return -1;
    
}