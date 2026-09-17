/*
请编写一个程序，在链表的第 k 个位置插入一个元素。
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct LNode{
    int data;
    struct LNode *next;
}ListNode, *ListLinkNode;

void insertNode(ListLinkNode head, int k){
    ListLinkNode current = head;
    int index = 0;
    while (index < k-1 && current != NULL)
    {
        current = current->next;
        index++;
    }
    if(current == NULL){
        printf("k超出链表范围");
        return ;
    }
    ListLinkNode newNode = (ListLinkNode)malloc(sizeof(ListNode));
    newNode->data = 0;
    newNode->next = current->next;
    current->next = newNode;
    return ;
    
}
int main(){

    return 0;
}