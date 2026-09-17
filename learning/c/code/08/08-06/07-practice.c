/*
请编写一个程序，使用 goto 跳出二层嵌套循环。
*/

#include <stdio.h>

int main(){
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            if(i == 5 && j == 4){
                goto jump;
            }
            printf("%d, %d \n", i , j);
        }
        
    }
    jump: 
        printf("已经跳出两层循环");
    return 0;
}