// 使用条件变量
// 一个生成者线程, 一个消费者线程(多线程进行通信)
// 满足一个条件: 生产完数据后,消费者才能消费数据
// 条件变量是跟互斥锁结合使用
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex;
pthread_cond_t cond;
pthread_t tid_1, tid_2;
int data;
int flag = 0;

void * thread_1(void * arg){
    // 加锁
    pthread_mutex_lock(&mutex);

    // 生产数据(修改共享资源)
    printf("product: is running, after 3s done \n");
    sleep(3);
    data = 1234;
    flag = 1; // product has done
    printf("product: print data: %d \n", data);

    // 唤醒消费者
    // 唤醒不会立即执行
    // 获取锁成功后才会执行
    pthread_cond_broadcast(&cond);

    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
    return NULL;
}

void * thread_2(void * arg){
    int ret_lock = 0;
    ret_lock = pthread_mutex_lock(&mutex);
    printf("thread_2 ret_lock value: %d \n", ret_lock);

    // 等待被唤醒
    while(!flag){
        int ret_wait = pthread_cond_wait(&cond, &mutex);
        if(0 != ret_wait){
            printf("等待唤醒失败 \n");
            return NULL;
        }
    }
    printf("consumer thread: data: %d \n", data);
    flag = 0;
    pthread_mutex_unlock(&mutex);
    pthread_exit(NULL);
    return NULL;
}
int main(int argc, const char * argv[]){

    pthread_mutex_init(&mutex, NULL);
    pthread_cond_init(&cond, NULL);

    pthread_create(&tid_1, NULL, thread_1, NULL);
    pthread_create(&tid_2, NULL, thread_2, NULL);

    pthread_join(tid_1, NULL);
    pthread_join(tid_2, NULL);

    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    return 0;
}