/*
    快排算法实现
*/

#include <stdio.h>
#include <stdlib.h>

void quick_sort(int *arr, int low, int high){
    if(arr == NULL){
        return;
    }
    if(low >= high){
        return ;
    }
    int key = arr[low];
    int first = low;
    int last = high;
    

    while (first != last)
    {
        while (first != last)
        {
            if(arr[last] < key){
                arr[first] = arr[last];
                ++first;
                break;  
            }else{
                last--;
            }
        }
        while (first != last)
        {
            if(arr[first] > key){
                arr[last] = arr[first];
                --last;
                break;
            }else{
                first++;
            }
        }
    }
    arr[first] = key;

    quick_sort(arr, low, first-1);
    quick_sort(arr, first+1, high);
    
}

int main() {
    int arr[] = {5, -2, 8, 1, 5, 0, -7, 3};
    int length = sizeof(arr) / sizeof(arr[0]);

    printf("before sort: ");
    for (int i = 0; i < length; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    quick_sort(arr, 0, length - 1);

    printf("after sort:  ");
    for (int i = 0; i < length; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
