/*
    编写一个函数，用来计算字符t在str数组中第一次出现的位置
    题目提示：
        如str为“abcc”，t为’c’，则返回3。如果没有找到该字符，则返回-1。
*/
#include <stdio.h>
#include <string.h>

int findC(const char *str, const char t){
    int strLen = strlen(str);
    for (int i = 0; i < strLen; i++)
    {
        if(str[i] == t){
            return i+1;
        }
    }
    return -1;
    
}
int main(){
    char str[] = "abcc";
    int position = findC(str, 'c');
    if(position != -1){
        printf("t字符的位置出现在: %d", position);
    }else{
        printf("该字符串没有t字符");
    }
    return 0;
}