#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>


sem_t sem_1;
sem_t sem_2;

int count = 0; // 统计生产次数

pthread_t tid_1 = 0;
pthread_t tid_2 = 0;

void * thread_1(void * arg){
    while(1){
        int ret = sem_wait(&sem_2);
        if(-1 == ret){
            perror("thread_1: wait sem_2 fail");
            return NULL;
        }
        printf("thread_1: wait sem_2 success \n");

        printf("thread_1: is running data, after 3s done \n");
        sleep(3);
        count++;
        printf("thread_1: data handle done \n");
        printf("thread_1: count value: %d \n", count);
        
        ret = sem_post(&sem_1);
        if(-1 == ret){
            perror("thread_1: sem post fail");
            return NULL;
        }
        printf("thread_1: sem post success \n");
    }
    return NULL;
}

void * thread_2(void * arg){
    while (1)
    {
        int ret;
        ret = sem_wait(&sem_1);
        if(-1 == ret){
            perror("thread 2: sem_wait 1 fail");
            return NULL;
        }
        printf("thread 2: sem_wait 1 success \n");

        printf("thread 2: is reading data \n");
        printf("thread 2: after 3s done \n");
        sleep(3);
        printf("thread 2: reading data done \n");
        count--;
        printf("count value: %d", count);
        ret = sem_post(&sem_2);
        if(-1 == ret){
            perror("thread 2: sem_2 wait fail");
            return NULL;
        }
        printf("thread 2: sem_2 post success \n");
    }
    
    return NULL;
}

int main(int argc, const char *argv[]){
    // init semaphore_1
    int ret_init;
    ret_init = sem_init(&sem_1, 0, 0);
    if(ret_init == -1){
        perror("sem_init func fail");
        return -1;
    }
    printf("sem_init 1 func success \n");

    // init semaphore_2
    
    ret_init = sem_init(&sem_2,0, 1);
    if(-1 == ret_init){

        return -1;
    }
    printf("sem_init 2 func success \n");

    // create thread 1
    pthread_create(&tid_1, NULL, thread_1, NULL);
    // create thread 2
    pthread_create(&tid_2, NULL, thread_2, NULL);

    pthread_join(tid_1, NULL);
    pthread_join(tid_2, NULL);


    sem_destroy(&sem_1);
    sem_destroy(&sem_2);
    return 0;
}