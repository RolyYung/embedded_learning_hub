#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main (int argc, const char * argv[]){
	
	fork();
	fork();

	while(1){
		printf("pid: %d, ppid: %d, pgid: %d, \n", getpid(), getppid(), getpgrp());
		sleep(3);
	}
	return 0;
}
