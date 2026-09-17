/*
请编写一个程序，删除链表中所有满足 Node.val == val 的节点，并返回新的头节点。
*/

#include <stdio.h>
#include <stdlib.h>
typedef struct LNode {
    int data;
    struct LNode *next;
}ListNode, *ListNodeLink;

ListNodeLink deleteValNode(ListNodeLink head,const int val){
    ListNodeLink dummy = malloc(sizeof(ListNode));
    dummy->next = head;
    ListNodeLink current = dummy;

    while (current != NULL)
    {
        if(current->next->data == val){
            ListNodeLink temp = current->next;
            current->next = current->next->next;
            free(temp);
        }else{
            current=current->next;
        }
        
    }
    return dummy->next;
    
}


int main(){

    return 0;
}