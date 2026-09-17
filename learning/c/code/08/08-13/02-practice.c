/*
请编写一个程序，实现队列的基本操作，包括入队、出队、查看队首元素及判断队列是否为空。

*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct QueueNode{
    int data;
    struct QueueNode * next;
}*NodeLink;

typedef struct Queue{
    struct QueueNode *front;
    struct QueueNode *rear;
}*QueueLink;

QueueLink InitQueue(QueueLink queue){
    NodeLink node = (NodeLink)malloc(sizeof(struct QueueNode));
    node->next = NULL;
    queue->front = node;
    queue->rear = node;
}

NodeLink enQueue(QueueLink queue, int val){
    NodeLink node = (NodeLink)malloc(sizeof(struct QueueNode));
    queue->rear->next = node;
    node->data = val;
    queue->rear = node;
    return node;
}

void deQueue(QueueLink queue){
    NodeLink node = queue->front;
    queue->front = queue->front->next;
    free(node);
    return;
}

int getQueueTop(QueueLink queue){
    return queue->front->data;
}

bool isEmptyQueue(QueueLink queue){
    return queue->front == queue->rear;
}

int main(){

    return 0;
}