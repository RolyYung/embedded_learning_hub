// 主线程 子线程 是否用同一块内存空间
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
int num = 100;

void * pthread_start(void * arg){
	printf("this is child thread \n");
	while(1){
		sleep(1);
		printf("child thread: num = %d, address= %p \n",num, &num);		
	}
	return NULL;
}
int main(int argc, const char * argv[]){
	// 创建新线程
	pthread_t tid = 0;
	pthread_create(&tid, NULL, pthread_start, NULL);
	printf("thread id is: %ld \n", tid);

	while(1){
		printf("main thread: num = %d, address= %p \n",num, &num);		
		sleep(1);
	}
	return 0;
}
