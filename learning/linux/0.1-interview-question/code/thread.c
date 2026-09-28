#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define THREAD_NUM 2
#define QUEUE_SIZE 100

int task_queue[QUEUE_SIZE];

int task_count = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *worker(void *arg){
    while (1)
    {
        pthread_mutex_lock(&mutex);

        while(task_count == 0){
            pthread_cond_wait(&cond, &mutex);
        }

        int task = task_queue[task_count - 1];
        task_count--;

        pthread_mutex_unlock(&mutex);
        sleep(2);
    }
    
    return NULL;
}