/*
    链表的排序 -- 冒泡法
*/

#include <stdio.h>

typedef struct Node {
    int data;
    struct Node * next;

}Node;

int bubble_sort_linklist(Node * head){
    if(head == NULL || head->next == NULL){
        return -1;
    }
    // 有头节点
    Node * node = NULL;
    Node * end = NULL;

    while(end != head){
        node = head;

        while(node->next != end){
            if(node->data > node->next->data){
                int temp = node->data;
                node->data = node->next->data;
                node->next->data = temp;
            }
            node=node->next;
        }
        end = node;
    }
    return 0;
}