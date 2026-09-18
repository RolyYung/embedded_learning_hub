#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void * thread(void *){
	printf("child thread tid: %ld, \n", pthread_self());
	return NULL;
}
int main(int argc, const char * argv[]){
	pthread_t tid = 0;
	pthread_create(&tid, NULL, thread, NULL);
	printf("create thread success, tid: %ld \n", tid);
	printf("main thread tid: %ld \n", pthread_self());
	sleep(3);

	return 0;
}
