/*
    链表排序 -- 头插法
*/

#include <stdio.h>

typedef struct Node {
    int data;
    struct Node * next;
}Node;

int insert_sort_linklist(Node * head){
    if(head == NULL || head->next == NULL || head->next->next == NULL){
        return -1;
    }

    Node * current = head->next->next;
    head->next->next = NULL;

    while(current != NULL)
    {
        Node * p = NULL;
        for(p=head; p!=NULL && p->next->data < current->data; p = p->next);

        Node * nextTemp = current->next;
        current->next = p->next;
        p->next = current;
        current = nextTemp;
    }
    return 0;
}