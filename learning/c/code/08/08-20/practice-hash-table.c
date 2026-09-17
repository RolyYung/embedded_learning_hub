/*
    哈希表的实现 -- 开放地址法
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10
#define NULL_KEY -1

typedef int DataType;

typedef struct node
{
    DataType * arr;
    int index; 
}HashTable;

// 创建哈希表
HashTable * create_hash_table()
{
    HashTable * hash_table = (HashTable *)malloc(sizeof(HashTable));
    if(hash_table == NULL){
        return NULL;
    }
    hash_table->index=0;
    DataType * arr = (DataType *)malloc(MAX * sizeof(DataType));
    if(arr == NULL){
        free(hash_table);
        return NULL;
    }
    hash_table->arr = arr;
    
    memset(hash_table->arr, -1, MAX * sizeof(DataType));
    return hash_table;
}

// 哈希表是否已满
int is_full_hashtable(HashTable *h)
{
    return h->index == MAX ? 1 : 0;
}

// 哈希表插入元素
void insert_hashtable(HashTable * h, DataType value)
{
    if(h == NULL){
        return ;
    }
    if(is_full_hashtable(h)){
        printf("hashtable is full");
        return ;
    }
    int index = 0; // 索引值
    index = value % MAX;
    while (h->arr[index] != NULL_KEY)
    {
        index = (index + 1) % MAX;
    }
    h->arr[index] = value;
    h->index++;
    return ;

}

// 查找数据
int search_hashtable(HashTable *h, DataType value)
{
    if(h == NULL){
        return -1;
    }

    int index = value % MAX;
    while(h->arr[index] != value)
    {
        index = (index + 1) % MAX;

        // 碰到NULL_KEY没有该值 或者循环一周了还是没找到 就是没有该值
        if(h->arr[index] == NULL_KEY || index == value % MAX) return -1;
    }

    return index;
}

void printf_hashtable(HashTable * h)
{
    if(h == NULL){
        printf("hashtable is empty / NULL");
        return ;
    }

    for (int i = 0; i < MAX; i++)
    {
        /* code */
        if(h->arr[i] != NULL_KEY){
            printf("%d \t", h->arr[i]);
        }
    }
    return ;
    
}

// 释放哈希表
void release_hashtable(HashTable * h)
{
    if(h == NULL){
        return ;
    }

    free(h->arr);
    free(h);
    return;
}

int main()
{
    HashTable *h = create_hash_table();
    if(h == NULL){
        printf("测试失败：哈希表创建失败\n");
        return EXIT_FAILURE;
    }

    int test_failed = 0;

    // 测试创建后的初始状态和判满函数
    if(h->index != 0 || is_full_hashtable(h)){
        printf("测试失败：哈希表初始状态错误\n");
        test_failed = 1;
    }

    // 1、11、21 的哈希地址相同，用来测试线性探测处理冲突
    DataType values[MAX] = {1, 11, 21, 2, 12, 22, 3, 13, 23, 4};
    for(int i = 0; i < 3; i++){
        insert_hashtable(h, values[i]);
    }

    // 此时表未满，31 不存在，并且探测过程中会遇到空槽
    if(search_hashtable(h, 31) != -1){
        printf("测试失败：查找到了不存在的元素 31\n");
        test_failed = 1;
    }

    // 插入剩余元素，使哈希表达到满表状态
    for(int i = 3; i < MAX; i++){
        insert_hashtable(h, values[i]);
    }

    // 测试所有已插入元素能否被正确找到
    for(int i = 0; i < MAX; i++){
        int position = search_hashtable(h, values[i]);
        if(position == -1 || h->arr[position] != values[i]){
            printf("测试失败：没有正确找到元素 %d\n", values[i]);
            test_failed = 1;
        }
    }

    // 测试满表状态以及满表后拒绝继续插入
    if(!is_full_hashtable(h)){
        printf("测试失败：没有正确识别满表状态\n");
        test_failed = 1;
    }

    int old_count = h->index;
    printf("满表插入测试：");
    insert_hashtable(h, 100);
    printf("\n");
    if(h->index != old_count || search_hashtable(h, 100) != -1){
        printf("测试失败：满表后仍然插入了元素 100\n");
        test_failed = 1;
    }

    // 测试打印函数
    printf("哈希表中的元素：");
    printf_hashtable(h);
    printf("\n");

    release_hashtable(h);
    release_hashtable(NULL);

    if(test_failed){
        printf("部分测试未通过\n");
        return EXIT_FAILURE;
    }

    printf("所有测试均通过\n");
    return EXIT_SUCCESS;
}
