/*
练习题
编写一个程序，使用数组指针传参的方式来完成以下任务：
·计算一维数组所有元素的和
·找出数组中的最大值和最小值
·将数组元素逆序排列
*/

//函数声明
void printArray(int (* arr)[10], int size);
int arraySum(int(* arr)[10], int size);
void findMinMax(int(* arr)[10], int size, int * min, int * max);void reverseArray(int(* arr)[10], int size);

int main(){

    return 0;
}
//计算一维数组所有元素的和
int arraySum(int(* arr)[10], int size){
    int result = 0;
    for(int i=0;i<size;i++){
        result += *arr[i];
    }
    return result;
}

//找出数组中的最大值和最小值
void findMinMax(int(* arr)[10], int size, int * min, int * max){
    *min = *arr[0];
    *max = *arr[0];
    for(int i=0;i<size;i++){
        if(*arr[i] > *max){
            *max = *arr[i];
        }
        if(*arr[i] < *min){
            *min = *arr[i];
        }
    }
}

//将数组元素逆序排列
void reverseArray(int(* arr)[10], int size){
    for (int i = 0; i < size; i++)
    {
        for (int j = i+1; j < size; j++)
        {
            if(*arr[i] < *arr[j]){
                *arr[i] = *arr[j];
            }
        }
        
    }
    
}