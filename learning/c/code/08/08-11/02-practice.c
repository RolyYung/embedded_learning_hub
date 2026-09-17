/*
请编写一个程序，返回链表的中间节点。如果有两个中间节点，返回第二个中间节点。
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct LNode{
    int data;
    struct LNode *next;
}ListNode, *ListLinkNode;

ListLinkNode findMiddle(ListLinkNode head){
    ListLinkNode fast = head;
    ListLinkNode slow = head;
    while (fast != NULL && fast->next != NULL)
    {
        /* code */
        fast = fast->next->next;
        slow = slow->next;
    }
    return slow;
}
int main(){

    return 0;
}