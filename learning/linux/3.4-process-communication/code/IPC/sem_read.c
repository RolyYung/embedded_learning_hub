#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <string.h>

#define SHM_SIZE 4096

int main(int argc, const char * argv){
    key_t key;
    key = ftok("test.txt", 2);
    if(-1 == key){
        perror("generate key fail");
        return -1;
    }

    int semid = 0;
    semid = semget(key,2,0666);
    if(-1 == semid){
        perror("get semaphore fail");
        return -1;
    }
    printf("get semaphore success, value is : %d", semid);

    
}