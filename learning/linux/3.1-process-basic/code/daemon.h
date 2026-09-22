#ifndef DAEMON_H
#define DAEMON_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>

//调用此函数, 就会编程守护进程
void create_daemon(){

    pid_t pid = fork();
    if(pid == -1){
        perror("fork process fail");
        exit(1);
    }
    else if(pid == 0){
        // child process
        setsid();// create new session. be the session leader.
        signal(SIGHUP, SIG_IGN);
        pid = fork();
        if(pid == -1){
            exit(1);
        }else if(pid > 0){
            exit(0);
        }
        chdir("/home/roly");
        umask(0000);

        close(0);
        close(1);
        close(2);
    }
    else if(pid > 0){
        // parent process
        exit(0); // exit parent process
    }
    return ;
}

#endif