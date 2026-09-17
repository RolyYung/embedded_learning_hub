/*
    从用户输入两个数和一个操作符（+, -, *, /），根据操作符进行相应的运算，并输出结果。
    使用 switch 语句处理不同的操作符情况，并检查除法操作是否有零作为除数。
*/
#include <stdio.h>

int main(){
    int a,b;
    char c;
    printf("请输入两个数 和 一个操作符:");
    scanf("%d %d %c", &a, &b, &c);
    switch (c)
    {
    case '+':
        printf("加法运算结果: %d", a+b);
        break;
    case '-':
        printf("减法运算结果: %d", a-b);
        break;
    case '*':
        printf("乘法运算结果: %d", a*b);
        break;
    case '/':
        if(b == 0){
            printf("除法不能作为除数");
            break;
        }
        printf("除法运算结果: %d", a/b);
        break;
    default:
        printf("你输入了非法字符");
        break;
    }
    return 0;
}