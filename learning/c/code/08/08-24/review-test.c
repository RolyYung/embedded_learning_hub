/*
    单元测试 错题整理:
    以下C语言代码实现的是哪种排序算法？

*/

int main(){
    int i ;
    int n = 10;
    int arr[10] = {1,2,3,4,5,6,7,8,9,10};
    int temp;
    int j;
    for (i = 0; i < n - 1; i++) {
        temp = arr[i];
        j = i;
        while (j > 0 && arr[j - 1] > temp) {
            arr[j] = arr[j - 1];
            j--;
        }
        arr[j] = temp;
    }
}