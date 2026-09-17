/*
数组初始化
*/
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#define ElemType int
#define MAX_ARRAY_DIM 8
#define ERROR -1
#define OK 0
#define OVERFLOW 1

typedef int Status;

typedef struct {
    ElemType *base;
    int dim; // 维度
    int *bounds; // 维界基址
    int *constants; // 映像函数常量
}Array;

Status InitArray(Array *A, int dim, ...){
    int elemtotal = 1; // 元素总数
    if(dim < 1 || dim > MAX_ARRAY_DIM){
        return ERROR;
    }
    A->dim = dim;
    A->bounds = (int *)malloc(dim * sizeof(int));
    if(NULL == A->bounds) return ERROR;
    va_list ap;
    va_start(ap, dim);
    for (int i = 0; i < dim; i++)
    {
        A->bounds[i] = va_arg(ap,int);
        if(A->bounds[i] < 0){
            return ERROR;
        }
        elemtotal *= A->bounds[i];
    }
    va_end(ap);
    A->base = (ElemType *)malloc(sizeof(ElemType) * elemtotal);
    if(!A->base) exit(OVERFLOW);
    A->constants = (int*)malloc(dim*sizeof(int));
    if(!A->constants) exit(OVERFLOW);
    A->constants[dim - 1] = 1;
    for (int i = dim-2; i >= 0; i--)
    {
        A->constants[i] = A->bounds[i+1]*A->constants[i+1];
    }
    return OK;
}

int main(){

    return 0;
}