/*
    快排代码
    时间复杂度: n*logn;
    空间复杂度: logn;
    稳定性: 不稳定, 会打乱原有顺序.
*/

#include <stdio.h>

void quick_sort(int *arr, int low, int high){
    if(low >= high){
        return;
    }
    int first = low;
    int last = high;
    int key = arr[low];

    while(first != last){
        while (first != last)
        {
            if(arr[last] < key){
                arr[first] = arr[last];
                ++first;
                break;
            }else{
                --last;
            }
        }
        while (first != last)
        {
            if(arr[first] > key){
                arr[last] = key;
                --last;
                break;
            }else{
                ++first;
            }
        }
        
    }
    arr[first] = key;

    quick_sort(arr, low, first - 1);
    quick_sort(arr, first + 1, high);
}