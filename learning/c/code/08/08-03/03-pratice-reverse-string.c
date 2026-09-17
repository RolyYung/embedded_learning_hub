// 请编写一个程序，定义一个函数 reverse，反转一个字符串。

#include <stdio.h>
#include <string.h>

void reverse(char str[]);
int main(){
    reverse("hello");
    return 0;
}

void reverse(char str[]){
    int len = strlen(str);
    int left = 0;
    int right = len - 1;
    for(;left <= right;){
        char temp = str[left];
        str[left] = str[right];
        str[right] = temp;
        left++;
        right--;
    }
}