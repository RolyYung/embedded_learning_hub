#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void * thread(void * arg){
	
	printf("this is child pthread, id: %ld \n", pthread_self());
	int * n = (int *)arg;
	free(n);
	return NULL;
}
int main(int argc, const char * argv[]){
	
	// 1. 申请内存空间
	int * p = (int *)malloc(sizeof(int));	
	if(p == NULL){
		perror("动态申请内存失败");
		return -1;
	}
	*p = 123; // 初始值
	
	// init 线程属性 attr
	pthread_attr_t attr;
	int ret = 0;
	ret = pthread_attr_init(&attr);
	if(ret != 0){
		fprintf(stderr, "init pthread attr fail: %s \n", strerror(ret));
		return -1;
	}
	printf("init thread attr success \n");
	// 设置线程为分离态
	int ret_set = 0;
	ret_set = pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
	if(ret_set != 0){
		fprintf(stderr, "set detach state fail: %s", strerror(ret_set));

		return -1;
	}
	
	// 创建一个新线程
	pthread_t tid = 0;
	int ret_create = pthread_create(&tid, &attr, thread, (void *)p);
	
	printf("set detach state success \n");
	// 销毁线程属性.
	pthread_attr_destroy(&attr);
	printf("destroy attr success \n");
	sleep(1);
	return 0;
}
