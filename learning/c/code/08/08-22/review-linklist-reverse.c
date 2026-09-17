/*
    链表的逆序操作 -- 三指针法
*/

#include <stdio.h>


typedef int Datatype;
typedef struct Node{
    Datatype data;
    struct Node * next;
}Node;

Node * reverse_linklist(Node * head){
    if(head == NULL || head->next == NULL){
        return NULL;
    }
    Node * current = head;
    Node * prev = NULL;
    Node * next = NULL;

    while(current != NULL){
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    return prev;
}