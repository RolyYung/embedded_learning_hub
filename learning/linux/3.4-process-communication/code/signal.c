// use signal function
#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void my_func(int sig){
	printf("catch SIGINT signal: %d \n", sig);
	return ;
}
int main(int argc, const char * argv[]){
	// param 1: signal number
	// param 2: handler: ignore
	/*
	if(SIG_ERR == signal(SIGINT, SIG_IGN)){
		perror("signal handler connect fail");
		return -1;
	}
	*/
	// default signal handler
	/*
	if(SIG_ERR == signal(SIGINT, SIG_DFL)){
		perror("error");
		return -1;
	}
	*/
	// set a function(捕捉)
	signal(SIGINT, my_func);
	printf("signal handler connect success \n");
	
	while(1){
		printf("hello world \n");
		sleep(1);
	}
	return 0;
}
