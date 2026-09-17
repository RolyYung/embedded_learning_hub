/*
请用C语言实现 char *my_strcpy(char *dest, const char *src)，要求：
•	函数返回 dest 指针。
必须处理 dest 与 src 内存重叠的情况吗？如果需要，怎么写；如果不需要，为什么？


*/
#include <stdio.h>
char *my_strcpy(char *dest, const char *src){
    if(dest == NULL || src == NULL){
        return NULL;
    }
    char *ret = dest;
    while(*src != '\0'){
        *dest++ = *src++;
    }
    *dest = '\0';
    return *ret;
}
