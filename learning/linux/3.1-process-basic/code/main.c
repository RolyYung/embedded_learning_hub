
#include "daemon.h"
#include <stdio.h>

int main(int argc, const char * argv[]){
    FILE * fp = fopen("log", "w+");
    if(fp == NULL){
        perror("fopen fail");
        exit(1);
    }

    create_daemon();

    while(1){
        sleep(1);
        fprintf(fp, "daemon is running \n");
        fflush(fp);
    }
    return 0;
}