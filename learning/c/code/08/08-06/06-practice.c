/*

请编写一个程序，定义一个函数 countDigits，计算一个整数中数字的个数。
*/

#include <stdio.h>

int countDigits(int num){
    int count = 0;
    if(num == 0) return 1;
    while (num != 0)
    {   
        count++;
        num /= 10;
    }
    return count;
    
}
int main(){
    int num;
    printf("请输入数字:");
    scanf("%d", &num);
    printf("数字个数: %d", countDigits(num));
    return 0;
}