/*
    判断链表是否成环代码编写
*/

#include <stdio.h>

typedef struct Node {
    int data;
    struct Node * next;

}Node;

int is_circle_linklist(Node * head){
    if(head == NULL){
        return 0;
    }
    Node * slow = head;
    Node * fast = head->next;

    while (slow != NULL && fast != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;
        if(slow == fast){
            return 1;
        }
    }
    return 0;
    
}