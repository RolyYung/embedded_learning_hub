#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <string.h>

#define SHM_SIZE 4096

int main(int argc, const char * argv[])
{
    //1.生成键值
    //注1：ftok函数的第一个参数文件名可以通过输入的参数进行获取
    //注2：ftok函数的第一个参数文件名如果只写文件名,表示当前路径下的文件
    key_t key = 0;
    key = ftok("test.txt", 2);
    if(-1 == key){
        perror("generate key value fail");
        return -1;
    }
    printf("key value is: %d", key);

    //2.创建信号量集
    int sem_id = 0;
    sem_id = semget(key, 2, IPC_CREAT|0666);
    if(-1 == sem_id){
        perror("create semaphore fail");
        return -1;
    }
    printf("create semaphore success, the value is : %d", sem_id);

    
}