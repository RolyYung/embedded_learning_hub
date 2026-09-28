#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>

#define SHM_SIZE 4096

int main(int argc, const char * argv[]){
    //1.对输入参数的参数个数进行检查
    if(argc != 2)
    {
        printf("输入参数的参数个数有误\n");
        printf("usage:./a.out pathname\n");
        return -1;
    }

    //2.使用ftok函数生成键值
    key_t key;
    key = ftok(argv[1], 1);

    int shmget_id = 0;
    shmget_id = shmget(key, SHM_SIZE, IPC_CREAT|0664);

    char * shm_addr = NULL;
    shm_addr = shmat(shmget_id, NULL, 0);

    while (1)
    {
        scanf("%s", shm_addr);

        if(strcmp(shm_addr, "quit") == 0){
            break;
        }
    }
    
    shmdt(shm_addr);

    shmctl(shmget_id, IPC_RMID, NULL);


    return 0;
}