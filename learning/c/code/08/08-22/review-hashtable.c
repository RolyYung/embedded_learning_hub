/*
开放地址法: 
    编写哈希表的初始化、插入、查询代码
*/

#include <stdio.h>

#define MAX 7
#define NULL_KEY -1

typedef struct HashTable{
    int *arr;
    int index;
}HashTable;

HashTable * init_hashtable(){
    HashTable * h = (HashTable *)malloc(sizeof(HashTable));
    if(h == NULL){
        return NULL;
    }
    h->index = 0;
    int * arr = (int *)calloc(sizeof(int) * MAX);
    if(arr == NULL){
        free(h);
        return NULL;
    }
    memset(arr, -1, sizeof(int)*MAX);
    h->arr = arr;
    return h;
}

int is_full_hashtable(HashTable * h){
    return h->index == MAX ? 1 : 0;
}

// 插入
int insert_hashtable(HashTable * h, int val){
    if(h == NULL){
        return -1;
    }
    if(is_full_hashtable(h)){
        return -1;
    }
    int index = val % MAX;
    while(h->arr[index] != NULL_KEY){
        index = (index + 1) % MAX;
    }
    h->arr[index] = val;
    h->index++;
    return 0;
}

// 查找hashtable
int search_hashtable(HashTable * h, int val){
    if(h == NULL){
        return -1;
    }

    int index = val % MAX;
    while(h->arr[index] != val){
        index = (index + 1) % MAX;
        if(h->arr[index] == NULL_KEY || index == val % MAX) return -1;
    }
    return index;
}