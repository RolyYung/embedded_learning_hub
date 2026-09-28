#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

struct mymsg{
    long mtype;
    char mtext[1024];
};

int main(int argc, const char *argv[]){
    // 1. judge argc
    if(argc != 2){
        printf("input arg count wrong \n");
        printf("usage: ./a.out pathname \n");
        return -1;
    }
    // 2. generate key (ftok)
    key_t key;
    int proj_id = 1;
    key = ftok(argv[1], proj_id);
    if(-1 == key){
        perror("ftok fail");
        return -1;
    }
    printf("key value: %d \n", key);
    // 3. msgget create message queue
    int msgid;
    msgid = msgget(key, IPC_CREAT | 0666);
    if(-1 == msgid){
        perror("msgget fail");
        return -1;
    }
    printf("msgid value: %d \n", msgid);
    struct mymsg my_msg;
    my_msg.mtype = 1;
    strcpy(my_msg.mtext, "hello world");
    int ret = msgsnd(msgid, &my_msg, strlen(my_msg.mtext), 0);
    if(-1 == ret){
        perror("msgsnd fail");
        return -1;
    }
    printf("msgsnd result value: %d\n", ret);

    
    return 0;
}