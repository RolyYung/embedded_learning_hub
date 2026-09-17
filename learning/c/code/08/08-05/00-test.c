// 指针串讲视频内容的代码编写
#include <stdio.h>
#include <stdlib.h>

void *GetMem(){
    char p[] = "hello";
    return p;
}


int main(){
    
    char *p = GetMem();
    printf("%d", *p);
    return 0;
}
