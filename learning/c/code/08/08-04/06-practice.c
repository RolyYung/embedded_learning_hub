/*
请编写一个程序，在concatenateStrings()函数中使用指针将两个字符串"Hello"和"World!"连接起来。concatenateStrings()函数的输入参数有三个，一个是第一个字符串的指针，第二个是第二个字符串的指针，第三个是用于存储连接结果的字符数组。
*/

#include <stdio.h>
#include <string.h>

void concatenateStrings(char *str1, char *str2, char *result);
int main(){
    char str1[] = "Hello";
    char str2[] = "World!";
    char result[12];
    concatenateStrings(str1,str2,result);
    printf("%s", result);
    return 0;
}

void concatenateStrings(char *str1, char *str2, char *result){
    strcat(result, str1);
    strcat(result, str2);
}