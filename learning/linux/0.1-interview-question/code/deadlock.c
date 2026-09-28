#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex_a = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_b = PTHREAD_MUTEX_INITIALIZER;

void * thread_1(void *arg){

    printf("thread_1: prepare to get A \n");

    pthread_mutex_lock(&mutex_a);
    printf("thread_1: get A \n");
    sleep(1);

    printf("thread_2: prepare to get B \n");

    pthread_mutex_lock(&mutex_b);

    printf("thread_2: get B \n");

    pthread_mutex_unlock(&mutex_a);
    pthread_mutex_unlock(&mutex_b);

    return NULL;
}

void * thread_2(void * arg){
    
    return NULL;
}

int main(int argc, const char * argv[]){
    pthread_t tid1, tid2;

    pthread_create(&tid1, NULL, thread_1, NULL);
    pthread_create(&tid2, NULL, thread_2, NULL);

    pthread_join(&tid1, NULL);
    pthread_join(&tid2, NULL);

    pthread_mutex_destroy(&mutex_a);
    pthread_mutex_destroy(&mutex_b);

    return 0;
}