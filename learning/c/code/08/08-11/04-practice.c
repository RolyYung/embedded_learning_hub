/*
请编写一个程序，反转链表并返回反转后的链表。
*/

#include <stdio.h>
#include <stdlib.h>
typedef struct LNode
{
    int data;
    struct LNode *next;
}ListNode, *ListLinkNode;

ListLinkNode reverseList(ListLinkNode head){
    ListLinkNode prev = NULL;
    ListLinkNode current = head;
    ListLinkNode next = NULL;

    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    return prev;
    
}
int main(){


    return 0;
}