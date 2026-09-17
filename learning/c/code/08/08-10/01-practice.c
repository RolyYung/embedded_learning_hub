/*
请用两种不同的方法写一个函数 int is_little_endian(void)，返回1为小端，0为大端。
•	方法一：使用 union。
•	方法二：使用 char * 指针强制转换 int。

*/
#include <stdio.h>
/*
方法一：使用 union。
union littleEndian{
        char x;
        int y;
    };
int is_little_endian(void){
    int a = 0x1;
    union littleEndian z;
    z.y = a;
    if(z.x == 0x1){
        return 1;
    }else{
        return 0;
    }
}
*/

/*
方法二：使用 char * 指针强制转换 int。
*/
int is_little_endian(void){
    int a = 0x1;
    char *p = (char *) &a;
    if(*p == 1){
        return 1;
    }else{
        return 0;
    }
}

int main(){
    
    return 0;
}