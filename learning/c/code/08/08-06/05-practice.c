/*

    请编写一个程序，定义一个结构体 Person，包含 name（字符串）和 age（整数）。通过scanf和printf输入输出该结构体的成员。
*/

#include <stdio.h>
struct Person
{
    char name[10];
    int age;
};

int main(){
    struct Person person;
    
    printf("请输入person 姓名: \n");
    scanf("%s", person.name);
    printf("请输入person 年龄: \n");
    scanf("%d", person.age);

    printf("person 姓名: %s \n", person.name);
    printf("person 年龄: %d \n", person.age);
    return 0;
}