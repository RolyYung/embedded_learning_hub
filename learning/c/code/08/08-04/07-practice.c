/*
请编写一个程序，在areStringsEqual()函数中使用两个指针作为输入参数判断两个字符串是否相等。
*/

#include <stdio.h>
#include <string.h>

int areStringsEqual(char *str1, char *str2);
int main(){
    char str1[] = "Hello";
    char str2[] = "World";
    int is_equal = areStringsEqual(str1, str2);
    if(is_equal == 0){
        printf("两字符串相等");
    }else{
        printf("两字符串不相等");
    }
    return 0;
}

int areStringsEqual(char *str1, char *str2){
    return strcmp(str1, str2);
}