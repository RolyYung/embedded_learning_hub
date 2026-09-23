#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t sem_rd, sem_wr;

void * read_thread(void *arg){
    for (int i = 0; i < 10; i++)
    {
        sem_wait(&sem_rd);
        printf("A \n");
        sem_post(&sem_wr);
    }
    
    return NULL;
}

void * write_thread(void * arg){
    for (int i = 0; i < 10; i++)
    {
        sem_wait(&sem_wr);
        printf("B\n");
        sem_post(&sem_rd);
    }
    
    return NULL;
}

int main(int argc, const char * argv[]){
    sem_init(&sem_rd, 0, 1);
    sem_init(&sem_wr, 0 , 0);

    pthread_t tid_rd,tid_wr;
    pthread_create(&tid_rd, NULL, read_thread, NULL);
    pthread_create(&tid_wr, NULL, write_thread, NULL);

    pthread_join(tid_rd, NULL);
    pthread_join(tid_wr, NULL);

    return 0;
}