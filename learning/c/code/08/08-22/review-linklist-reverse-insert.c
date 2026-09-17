/*
    指针的逆序 -- 头插法
*/

#include <stdio.h>

typedef int Datatype;
typedef struct Node {
    Datatype data;
    struct Node * next;
}Node;

Node * reverse_linklist(Node * head){
    if(head == NULL || head->next == NULL){
        return NULL;
    }

    Node * current = head->next->next;
    head->next->next = NULL;

    while(current != NULL){
        Node * nextTemp = current->next;
        current->next = head->next;
        head->next = current;
        current = nextTemp;
    }

    return head;
}