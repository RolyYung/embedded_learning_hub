// gcc gdb 示例代码
// 简单实现一个加减乘除的多文件代码项目
#include <stdio.h>
#include "asmd.h"

int main(int argc, const char* argv[]){
    printf("add=%d,sub=%d,mul=%d,div=%d", add(3,4), sub(8,3), mul(3,3), div(1,1));    
    return 0;
}