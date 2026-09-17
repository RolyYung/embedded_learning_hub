/*
请编写一个程序，访问链表中第 k 个元素，并打印出其值。
*/

#include <stdio.h>
#include <stdlib.h>
typedef struct LNode{
    int data;
    struct LNode *next;
}ListNode, *ListLinkNode;

void printListNode(ListLinkNode head, const int k){
    int i = 0;
    ListLinkNode current = head;
    while (current != NULL && i<k)
    {
        /* code */
        current = current->next;
        i++;
    }
    if(current == NULL){
        printf("k值大于链表长度");
        return;
    }
    printf("%d", current->data);
}
int main(){

}