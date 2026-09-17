/*
    请编写一个程序，定义一个函数 factorial 计算一个数的阶乘，并在主函数中调用。

*/
#include <stdio.h>
int factorial(int n);
int main(){

    factorial(5);
    return 0;
}

int factorial(int n){
    if(n == 1){
        return 1;
    }
    return n * factorial(n - 1);

}