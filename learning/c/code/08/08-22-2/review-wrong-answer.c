/*
    链表是否成环
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
    int data;
    struct Node * next;
}Node;

int is_circle_linklist(Node * head){
    if(head == NULL){
        return -1;
    }
    Node * slow = head;
    Node * fast = head->next;
    while (fast != NULL && slow !=NULL)
    {
        if(slow == fast){
            return 1;
        }
        slow = slow->next;
        fast = fast->next->next;
    }
    return 0;
}

// 头插法排序
int sort_linklist_insert(Node * head){
    if(head == NULL){
        return -1;
    }
    if(head->next == NULL || head->next->next == NULL){
        // 空链表, 单链表不需要排序
        return 0;
    }
    Node * current = head->next->next;
    head->next->next = NULL;

    while(current != NULL){
        Node * p = head;
        for(;p->next!=NULL && p->next->data > current->data ; p = p->next);
        Node * nextTemp = current->next;
        current->next = p->next;
        p->next = current;
        current = nextTemp;
    }

    return 0;
}

Node * sort_linklist_three_pointer(Node * head){
    // 空链表 单链表就不需要排序
    if(head == NULL || head->next == NULL){
        return -1;
    }

    Node * current = head;
    Node * prev = NULL;
    Node * next = NULL;

    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    return prev;
}

Node * merge_two_list(Node * list1, Node * list2){
    if(list1 == NULL) return list2;
    if(list2 == NULL) return list1;

    Node dummy;
    Node * temp = &dummy;
    temp->next = NULL;
    while(list1 != NULL && list2 != NULL){
        if(list1->data > list2->data){
            temp->next = list2;
            list2 = list2->next;
        }else{
            temp->next = list1;
            list1 = list1->next;
        }
    }

    if(list1 != NULL) temp->next = list1;
    if(list2 != NULL) temp->next = list2;

    return dummy.next;
}

Node * sort_linklist_sub_merge(Node * list){
    if(list == NULL || list->next == NULL){
        return list;
    }

    Node * slow = list;
    Node * fast = list->next;
    while(fast != NULL && fast->next != NULL){
        slow = slow->next;
        fast = fast->next->next;
    }
    Node * mid = slow->next;
    slow->next = NULL;
    Node * left = sort_linklist_sub_merge(list);
    Node * right = sort_linklist_sub_merge(mid);

    return merge_two_list(left, right);
}

void sort_linklist_merge(Node * head){
    if(head == NULL){
        return ;
    }
    
    head->next = sort_linklist_sub_merge(head->next);
    return ;
}

#define MAX 7
typedef struct h{
    int *arr;
    int index;
}HashTable;

HashTable * init_hashtable(){
    HashTable * h = (HashTable *)malloc(sizeof(HashTable));
    if(h == NULL){
        return NULL;
    }
    int * arr = (int *)malloc(MAX * sizeof(int));
    if(arr == NULL){
        free(h);
        return NULL;
    }
    memset(arr, -1, MAX * sizeof(int));
    h->arr = arr;
    h->index = 0;
    return h;
}

int is_full_hashtable(HashTable * h){
    return (h != NULL && h->index) == MAX ? 1 : 0;
}

int insert_hasttable(HashTable * h, int val){
    if(is_full_hashtable(h)){
        return -1;
    }

    int index = val % MAX;
    while(h->arr[index] != -1){
        index = (index + 1) % MAX;
    }
    h->arr[index] = val;
    h->index++;
    return 0;
}

int binary_search(int *arr, int len, int target){
    int left = 0;
    int right = len-1;
    int mid = (left+right) / 2;

    while(left < right){
        if(arr[mid] == target){
            return mid;
        }else if(arr[mid] > target){
            right = mid - 1;
        }else{
            left = mid + 1;
        }
    }
    printf("not found");
    return -1;
    
}

Node * merge_sorted_linklist(Node * left, Node * right){
    if(left == NULL){ return right;}
    if(right == NULL) return left;
    Node * list1 = left;
    Node * list2 = right;
    Node dummy;
    Node * temp = &dummy;
    temp->next = NULL;
    while (list1 != NULL && list2 != NULL)
    {
        if(list1->data > list2->data){
            temp->next = list2;
            list2 = list2->next;
        }else{
            temp->next = list1;
            list1 = list1->next;
        }
        temp = temp->next;
    }
    
    if(list1 != NULL) temp->next = list1;
    if(list2 != NULL) temp->next = list2;

    return dummy.next;
}