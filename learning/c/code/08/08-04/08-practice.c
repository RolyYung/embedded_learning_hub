/*
*编写一个函数，用来计算字符t在str数组中第一次出现的位置
如str为“abcc”，t为’c’，则返回3。如果没有找到该字符，则返回-1。
*/

#include <stdio.h>
#include <string.h>
int findFirstC(char *str, int size);

int main(){
    char str[] = "Hello world!";
    int position = findFirstC(str, strlen(str));
    if(position != -1){
        printf("c position is: %d", position);
    }else{
        printf("not found c");
    }
    return 0;
}

int findFirstC(char *str, int size){
    for (int i = 0; i < size; i++)
    {
        if(str[i] == 'c'){
            return i;
        }
    }
    return -1;

}
