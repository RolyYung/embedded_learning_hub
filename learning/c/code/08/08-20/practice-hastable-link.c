/*
 哈希表的链地址实现.
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 10


typedef int DataType;

typedef struct Node {
    DataType data;
    struct Node * next;
}Node;

typedef struct HashTable
{
    Node ** list;
}HashTable;
int is_nagetive(int val){
    return val < 0;
}
// 创建哈希表
HashTable * create_hashtable(){
    HashTable *h = (HashTable *)malloc(sizeof(HashTable));
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

// 插入哈希表
int insert_hashtable(HashTable *h, DataType val){
    if(h == NULL){
        return -1;
    }
    if(is_nagetive(val)){
        return -1;
    }
    int index = val % MAX;
    Node * node = (Node *)malloc(sizeof(Node));
    if(node ==NULL){
        return -1;
    }
    node->data = val;
    node->next = h->list[index];
    h->list[index] = node;
    return 0;
}

// 查找链表, 没找到返回-1, 找到返回对应index, 输出具体位置
int search_hashtable(HashTable *h, DataType val){
    if(h == NULL){
        return -1;
    }
    if(is_nagetive(val)){
        return -1;
    }
    int index = val % MAX;
    Node * temp = h->list[index];
    if(temp == NULL){
        return -1;
    }
    int i =0;
    for (; temp != NULL && temp->data != val; temp = temp->next){
        i++;
    }
    if(temp == NULL){
        return -1;
    }
    printf("i=%d", i);

    return index;
    
}

// 释放哈希表
void release_hashtable(HashTable *h){
    if(h == NULL){
        return ;
    }

    // 释放list
    for (int i = 0; i < MAX; i++)
    {
        if(h->list[i] != NULL){
            Node * temp = h->list[i];
            while (temp != NULL)
            {
                Node * nextTemp = temp->next;
                free(temp);
                temp = nextTemp;
            }
        }
    }
    free(h->list);
    free(h);
    return ;
}



int main(){

    return 0;
}