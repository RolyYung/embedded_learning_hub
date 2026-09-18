// 测试主线程 子线程的执行顺序 execute sort
/*
 * 主线程 子线程没有执行的先后顺序
 * 谁先抢到CPU时间片 谁就先执行.
 *
 * 
 */
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void * pthread_start(void * arg){
	while(1){
		printf("i'm child thread \n");
		sleep(1);
	}
	return NULL;
}

int main(int argc, char * argv[]){
	
	pthread_t tid = 0;
	
	pthread_create(&tid, NULL, pthread_start, NULL);

	while(1){
		printf("i'm parent thread \n");
		sleep(1);
	}
	return 0;
}
