/*
请编写一个程序，返回链表中的倒数第 k 个节点。
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct LNode{
    int data;
    struct LNode *next;
}ListNode, *ListLinkNode;

ListLinkNode findNode(ListLinkNode head, const int k){
    ListLinkNode first = head;
    ListLinkNode second = head;

    int index = 0;
    while (index<k && first != NULL)
    {
        first = first->next;
        index++;
    }
    if(first == NULL){
        printf("k值超过链表长度");
        return NULL;
    }
    while (first != NULL)
    {
        
        first = first->next;
        second = second->next;
    }
    return second;
    
    
}
int main(){

    return 0;
}