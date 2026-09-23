#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int buf[5] = {11,22,33,44,55};
int count = 5;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void * thread_consumer(void * arg){

    while(1){
        pthread_mutex_lock(&mutex);
        if(count == 0){
            pthread_cond_wait(&cond, &mutex);
        }
        int b = buf[--count];
        printf("consumer :%d \n", b);
        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void * thread_producter(void * arg){

    while(1){
        pthread_mutex_lock(&mutex);
        if(count >= 5){
            pthread_cond_wait(&cond, &mutex);
        }
        buf[count++] = rand() %100 + 1;
        printf("productor produce: %d \n", buf[count - 1]);
        pthread_cond_broadcast(&cond);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main(int argc, const char * argv[]){
    pthread_t tid_1, tid_2;
    pthread_create(&tid_1, NULL, thread_producter, NULL);
    pthread_create(&tid_2, NULL, thread_consumer, NULL);

    pthread_join(tid_1, NULL);
    pthread_join(tid_2, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    return 0;
}