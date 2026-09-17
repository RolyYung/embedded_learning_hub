/*
请编写一个程序，实现栈的基本操作，包括入栈、出栈、查看栈顶元素及判断栈是否为空。
*/

#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 10

typedef struct Stack {
    int *base;
    int *top;
    int stacksize;
}SqStack, *StackLink;

typedef enum {
    ERROR,
    OK,
}Status;

typedef enum {
    noEmpty,
    isEmpty,
}Empty;

Status InitStack(StackLink stack){
    stack->base = (int *)malloc(MAX_SIZE * sizeof(int));
    if(NULL == stack->base) return ERROR;
    stack->top = stack->base;
    stack->stacksize = MAX_SIZE;
    return OK;
}

Status PushStack(StackLink stack, int val){
    // 判断栈是否已满
    if((stack->top - stack->base) >= stack->stacksize){
        return ERROR;
    }
    *(stack->top) =val;
    stack->top ++;
    return OK;
}
Empty isEmptyStack(StackLink stack);
Status PoPStack(StackLink stack, int val){
    if(isEmptyStack(stack)){return ERROR;};
    stack->top --;
    return OK;
}


Empty isEmptyStack(StackLink stack){
    if(stack->top == stack->base){
        return isEmpty;
    }else{
        return noEmpty;
    }
}

int getTopStackEle(StackLink stack){
    if(isEmptyStack(stack)) return 0;
    return *(stack->top);
}

int main(){
    return 0;
}