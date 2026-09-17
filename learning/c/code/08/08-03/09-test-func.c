// 题目1：递归计算数字累加（基础）

// #include <stdio.h>

// int sum(int n);
// int main(){


// }

// int sum(int n){
//     if(n == 1){
//         return 1;
//     }
//     return n + sum(n-1);
// }

/*
    题目2：递归反转字符串（进阶）
    请编写函数：

void reversePrint(char str[], int index);

要求：

使用递归倒序打印字符串。

例如：

char str[] = "hello";

reversePrint(str, 0);

输出：

olleh

注意：

这里不是修改原字符串，而是直接倒序输出。
*/
#include <stdio.h>
#include <string.h>

void reversePrint(char str[], int index);
int main(){

    return 0;
}
void reversePrint(char str[], int index){
    if(index == strlen(str)){
        return;
    }
    printf("%c", str[strlen(str) - 1 - index]);
    reversePrint(str, ++index);
}