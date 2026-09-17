/*
判断链表是否成环代码编写

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct ListNode
{
    int val;
    struct ListNode * next;
}ListNode;

// 
bool hasCycle(ListNode *node){
    ListNode *slow = node;
    ListNode *fast = node;
    while (fast != NULL && fast->next != NULL)
    {   
        slow = slow->next;
        fast = fast->next->next; 
        if(slow == fast){
            return true;
        } 
    }
     
    return false;
}

ListNode* createNode(int val) {
    ListNode *newNode = (ListNode*)malloc(sizeof(ListNode));
    newNode->val = val;
    newNode->next = NULL;
    return newNode;
}
int main(){
    ListNode *node1 = createNode(1);
    ListNode *node2 = createNode(2);
    ListNode *node3 = createNode(3);
    ListNode *node4 = createNode(4);

    node1->next = node2;
    node2->next = node3;
    node3->next = node4;

    int a[4] = {1,2,3,4};
    for(int i= 0; i<4;++i){
        printf("%d", a[i]);
    }
    if (hasCycle(node1)) {
        printf("链表中有环！\n");
    } else {
        printf("链表中无环。\n");
    }
    return 0;
}