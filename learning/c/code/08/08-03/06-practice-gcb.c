// 请编写一个程序，求两个数的最大公约数和最小公倍数。

#include <stdio.h>
int gcb(int a, int b){
    while (b !=0)
    {
        int temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

int lcm(int a,int b){
    return (a*b) / (gcb(a,b));
}
int main(){

    return 0;
}