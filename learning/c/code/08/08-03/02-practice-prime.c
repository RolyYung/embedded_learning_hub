// 请编写一个程序，定义一个函数 isPrime，判断一个整数是否为素数。
// 素数的定义: 只能够被1和自身整除的被称为素数. 2以下的不是素数.
#include <stdio.h>
int isPrime(int n);
int main(){
    isPrime(10);
    return 0;
}

int isPrime(int n) {
    // 2以下不是素数
    if(n<2){
        return 0;
    }
    for(int i=2;i<n;i++){
        if(n%i == 0){
            return 0;
        }
    }
    return 1;

}

