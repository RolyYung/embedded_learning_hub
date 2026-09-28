#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

struct recv_data{
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
    printf("key value: %d", key);
    // 3. msgget create message queue
    int msgid;
    msgid = msgget(key, IPC_CREAT | 0666);
    if(-1 == msgid){
        perror("msgget fail");
        return -1;
    }
    printf("msgid value: %d \n", msgid);
    
    // 4. recive message data
    struct recv_data recvdata;
    recvdata.mtype = 1;
    recvdata.mtext[0] = '\0';
    ssize_t msg_rcv_ret = 0;
    msg_rcv_ret = msgrcv(msgid, &recvdata, sizeof(recvdata.mtext),recvdata.mtype,0);
    if(msg_rcv_ret == -1){
        perror("msgrcv fail \n");
        return -1;
    }
    printf("msgrcv success, recive byte: %ld \n", msg_rcv_ret);
    printf("msgrcv string value: %s \n", recvdata.mtext);

    // 延时删除,将msgid标记为删除状态
    // 
    msgctl(msgid, IPC_RMID, NULL);
    printf("remove msg success \n");

    return 0;
}