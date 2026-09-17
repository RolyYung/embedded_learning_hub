/*
    顺序表的实现
*/
#include <stdio.h>
#include <stdlib.h>

#define DataType int
typedef struct SeqList
{
    DataType * data;
    size_t size;
    int index;
}Seq;

Seq * InitSeqList(size_t size){
    Seq* seq = (Seq *)calloc(1, sizeof(Seq));
    if(seq == NULL){
        return NULL;
    }
    seq->data = (int *)calloc(size, sizeof(DataType));
    if(seq->data == NULL){
        return NULL;
    }
    seq->size = size;
    seq->index = 0;
    return seq;
}

int IsEmptySeq(Seq * seq){
    if(seq != NULL){
        return -1;
    }
    if(seq->index == 0){
        return 1;
    }else{
        return 0;
    }
}

int IsSeqFull(Seq *seq){
    if(seq == NULL){
        return -1;
    }
    if(seq->size == seq->index){
        return 1;
    }else{
        return 0;
    }
}

int ReleaseSeqList(Seq *seq){
    free(seq->data);
    free(seq);
    return 1;
}

int InsertSeqList(Seq *seq, int pos, DataType value){
    if(IsSeqFull(seq)){
        return -1;
    }
    if(pos > seq->index){
        pos = seq->index;
    }
    for(int i = (seq->index); i>pos; --i){
        seq->data[i] = seq->data[i-1]; 
    }
    seq->data[pos] = value;
    seq->index++;
    return 1;
}
void ShowSeqList(Seq* seq){
    for(int i=0;i<seq->index;++i){
        printf("%d \t", seq->data[i]);
    }
    printf("\n");
}
int PushBackSeqList(Seq* seq, DataType value)
{
    if(IsSeqFull(seq)){
        return -1;
    }
    seq->data[seq->index++] = value;
    return 1;
}
int PopBackSeqList(Seq* seq)
{
    if(IsEmptySeq(seq)){
        return -1;
    }
    seq->index--;
    return 1;
}
int clearSeq(Seq * seq){
    if(seq == NULL){
        return -1;
    }
    seq->index = 0;
    return 1;
}
// 删除定义元素.
int DeleteNum(Seq* seq, DataType value)
{
    int i = 0 ;
    for (int j = 0; j < seq->index; j++)
    {
        if(seq->data[j] != value){
            seq->data[i++] = seq->data[j];
        }
    }
    seq->index = i;
    return 1;
}

int main()
{
    Seq *seq = InitSeqList(8);
    InsertSeqList(seq, 0, 60);
    InsertSeqList(seq, 0, 30);
    InsertSeqList(seq, 0, 40);
    PushBackSeqList(seq, 80);
    InsertSeqList(seq, 6, 60);
    PushBackSeqList(seq, 60);
    PushBackSeqList(seq, 60);
    
    ShowSeqList(seq);
    DeleteNum(seq, 60);
    ShowSeqList(seq);
    ReleaseSeqList(seq);
    return 0;
}