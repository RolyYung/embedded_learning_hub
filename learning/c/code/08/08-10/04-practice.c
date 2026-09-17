/*
    手写strcpy函数
*/

#include <stdio.h>

char * my_strcpy(char *dest, const char *src){
    if(dest == NULL || src == NULL){
        return NULL;
    }
    char *result = dest;
    while (*src != '\0')
    {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
    return result;
    
}
int main(){
    char str[] = "hello";
    char dest[6];
    char * result = my_strcpy(dest, str);
    printf("%d", sizeof(result));
    return 0;
}