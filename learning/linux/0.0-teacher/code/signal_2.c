#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

void sig_handler(int sigNum){
    printf("sigNum: %d \n", sigNum);
    return ;
}

int main(int argc, const char * argv[]){
    printf("pid: %d \n", getpid());

    if(signal(SIGINT, sig_handler) == SIG_ERR){
        perror("signal error");
        exit(1);
    }

    if(signal(SIGALRM, sig_handler) == SIG_ERR){
        perror("signal error");
        exit(1);
    }
    
    while (1)
    {
        sleep(3);
        printf("process is running \n");
    }
    

    return 0;
}