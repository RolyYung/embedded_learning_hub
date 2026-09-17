/*
    链表排序算法实现-- 归并算法的实现
*/
#include <stdio.h>
#include <stdlib.h>


typedef int DataType;
// 有头链表的实现
typedef struct LinkList{
    DataType data;
    struct LinkList * next;
}Node;

Node * merge_linkList_node(Node * left, Node * right)
{
    if(left==NULL && right==NULL){
        return NULL;
    }

    Node dummy;
    Node * tail = &dummy;
    tail->next = NULL;
    
    while(left!=NULL && right != NULL){
        if(left->data <= right->data){
            tail->next = left;
            left = left->next;
        }else{
            tail->next = right;
            right = right->next;
        }
        tail = tail->next;
    }

    if(left != NULL) tail->next = left;
    if(right != NULL) tail->next = right;
    return dummy.next;
}
// 递归函数, 子链表的拆分
Node * merge_sub_linkList(Node * list)
{
    if(list == NULL || list->next == NULL)
    {
        return list;
    }
    Node * slow = list;
    Node * fast = list->next;
    while (fast != NULL && fast->next != NULL)
    {
        slow = slow->next;
        fast = fast->next->next;
    }
    Node * mid = slow->next;
    slow->next = NULL;
    Node * left = merge_sub_linkList(list);
    Node * right = merge_sub_linkList(mid);

    return merge_linkList_node(left, right);
}

// 总的合并函数
Node * merge_linkList(Node *head)
{
    if(head == NULL)
    {
        return NULL;
    }

    head->next = merge_sub_linkList(head->next);
    return head;
}


// 创建空链表
Node* create_empty_linkList()
{
    Node * head = (Node *)malloc(sizeof(Node));
    if(head == NULL){
        return NULL;
    }
    head->next = NULL;
    return head;
}

// 头插法
int push_front(Node *head, DataType value)
{
    if(head == NULL){
        return -1;
    }
    Node * node = (Node *)malloc(sizeof(Node));
    if(node == NULL){
        return -1;
    }
    node->data = value;
    node->next = head->next;
    head->next = node;
    return 0;
}

// 头删法
int pop_front(Node * head)
{
    if(NULL == head){
        return -1;
    }
    if(NULL == head->next){
        return -1;
    }
    Node * temp = head->next;
    head->next = head->next->next;
    free(temp);
    return 0;
}

// 打印链表
void print_linkList(Node * head)
{
    if(NULL == head){
        return ;
    }
    head = head->next;
    while (NULL != head)
    {
        printf("%d\n", head->data);
        head = head->next;
    }
    return ;
    
}

// 尾插法
int push_back(Node * head, DataType value){
    if(NULL == head){
        return -1;
    }
    Node * tail = head;
    while (NULL != tail->next)
    {
        tail = tail->next;
    }
    Node * node = (Node *)malloc(sizeof(Node));
    if(node == NULL){
        return -1;
    }
    node->data = value;
    node->next = NULL;
    tail->next = node;
    return 0;
}

// 尾删法
int pop_back(Node *head){
    if(NULL == head){
        return -1;
    }
    if(NULL == head->next){
        return -1;
    }
    // 找到倒数第二个节点
    Node * tail = head;
    while(tail->next->next != NULL)
    {
        tail = tail->next;
    }
    Node * temp = tail->next;
    tail->next = NULL;
    free(temp);
    return 0;
}

// 释放链表
int release_linkList(Node * node)
{
    if(NULL == node){
        return -1;
    }
    Node * head = node;
    Node * next = head->next;
    while (NULL != next)
    {
        free(head);
        head = next;
        next = head->next;
    }
    free(head);
    return 0;
}

int main()
{
    
    Node *head = create_empty_linkList();
    if(head == NULL){
        printf("创建链表失败\n");
        return 1;
    }

    // 使用头插和尾插生成一个无序链表
    if(push_back(head, 5) == -1 ||
       push_front(head, 3) == -1 ||
       push_back(head, 1) == -1 ||
       push_front(head, 8) == -1){
        printf("插入节点失败\n");
        release_linkList(head);
        return 1;
    }

    // 测试头删和尾删
    if(pop_front(head) == -1 || pop_back(head) == -1){
        printf("删除节点失败\n");
        release_linkList(head);
        return 1;
    }

    // 再插入两个元素，保持链表无序
    if(push_front(head, 7) == -1 || push_back(head, 2) == -1){
        printf("插入节点失败\n");
        release_linkList(head);
        return 1;
    }

    printf("排序前的链表：\n");
    print_linkList(head);

    Node * sorted_head = merge_linkList(head);
    if(sorted_head == NULL){
        printf("链表排序失败\n");
        release_linkList(head);
        return 1;
    }

    printf("排序后的链表：\n");
    print_linkList(head);

    if(release_linkList(head) == -1){
        printf("释放链表失败\n");
        return 1;
    }
    head = NULL;
    printf("链表释放成功\n");

    return 0;
}


