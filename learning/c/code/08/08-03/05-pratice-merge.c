// 请编写一个程序，定义一个函数 mergeArrays，将两个已排序的数组合并为一个排序后的数组。

#include <stdio.h>
void mergeArrays(int arr1[], int size1, int arr2[], int size2, int result[]){
    int i=0;
    int j=0;
    int k=0;
    while(i<size1 && j<size2){
        if(arr1[i]<arr2[j]){
            result[k] = arr1[i];
            i++;
        }else{
            result[k] = arr2[j];
            j++;
        }
        k++;
    }
    // arr1剩余元素
    while(i < size1)
    {
        result[k] = arr1[i];
        i++;
        k++;
    }


    // arr2剩余元素
    while(j < size2)
    {
        result[k] = arr2[j];
        j++;
        k++;
    }

}
int main(){
    int arr1[4] = {1,3,5,7};
    int arr2[4] = {2,4,6,8};
    int result[8];
    mergeArrays(arr1,4,arr2,4,result);
    return 0;
}