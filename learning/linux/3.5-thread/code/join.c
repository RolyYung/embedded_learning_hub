#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void * thread(void * arg){
	pthread_exit(NULL);
	return NULL;
}
int main(int argc, const char * argv[]){
	
	pthread_t tid = 0;
	pthread_create(&tid, NULL, thread, NULL);
	printf("create pthread success, tid is : %ld \n", tid);
	int ret = pthread_join(tid, NULL);
	if(ret != 0){
		printf("回收失败 \n");
		return -1;
	}
	printf("child pthread exit success \n");
	sleep(3);
	return 0;
}
