#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void * thread(void * arg){
	
	printf("this is child thread \n");
	printf("this is child thread: i'm exiting \n");
	pthread_exit(NULL);
	return NULL;
}
int main(int argc, const char * argv[]){
	pthread_t tid = 0;
	
	pthread_create(&tid, NULL, thread, NULL);
	
	printf("this is main thread, tid: %ld \n", tid);
	sleep(3);
	return 0;
}
