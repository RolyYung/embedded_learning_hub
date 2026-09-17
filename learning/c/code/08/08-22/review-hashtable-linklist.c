/*
    链地址法
    实现哈希表的初始化 插入 查询
*/

#include <stdio.h>
#define MAX 7

typedef struct Node{
    int data;
    struct Node * next;
}Node;

typedef struct h {
    Node ** list;
}HashTable;

// 初始化
HashTable * init_hashtable(){
    HashTable * h = (HashTable *)malloc(sizeof(HashTable));
    if(h == NULL){
        return NULL;
    }
    Node ** list = (Node **)calloc(MAX, sizeof(Node *));
    if(list == NULL){
        free(h);
        return NULL;
    }
    h->list = list;
    return h;
}

int insert_hashtable(HashTable * h, int val){
    if(h == NULL){
        return -1;
    }
    Node * node = (Node *)malloc(sizeof(Node));
    if(node == NULL){
        return -1;
    }
    node->data = val;
    int index = val % MAX;
    node->next = h->list[index];
    h->list[index] = node;

    return 0;
}

int search_hashtable(HashTable * h, int val){
    if(h == NULL){
        return -1;
    }
    int index = val % MAX;
    Node * node = h->list[index];
    int i = 0;
    while (node == NULL && node->data != val)
    {
        node = node->next;
        i++;
    }
    if(node == NULL){
        printf("not found the val");
        return -1;
    }
    printf("index = %d, i = %d", index, i);
    return 0;
}