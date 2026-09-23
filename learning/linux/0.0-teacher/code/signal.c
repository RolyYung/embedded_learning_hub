#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

int main(int argc, const char * argv[]){
    printf("pid: %d \n", getpid());

    if(signal(SIGINT, SIG_IGN) == SIG_ERR){
        perror("signal error");
        exit(1);
    }

    pid_t pid = fork();
    if(pid == -1){
        perror("fork fail");
        exit(1);
    }else if(pid == 0){
        exit(0);
    }
    

    while (1)
    {
        sleep(3);
        printf("process is running \n");
    }
    

    return 0;
}