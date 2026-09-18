#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

void * pthread_start(void * arg){
	
	printf("我是子线程 \n");
	// 接收传递过来的参数
	int * val = (int *)arg;
	printf("传递过来的参数为: %d \n", *val);
	free(val);
	return NULL;
}
int main(int argc, char * argv[]){
	
	pthread_t tid = 0; // 线程id
	#if 0
	// 栈区给入口函数传递参数
	int value = 100;
	#else
	int * value = (int *)malloc(sizeof(int));
	if(value == NULL){
		printf("堆区开辟空间失败 \n");
		return -1;
	}
	printf("堆区开辟空间成功 \n");
	*value = 123;


	#endif 
	int ret = 0;
	ret = pthread_create(&tid, NULL, pthread_start, (void *)value);
	if(ret != 0){
		printf("创建子线程失败, 错误码: %d \n", ret);
		return -1;
	}
	printf("线程创建成功, 线程id: %ld \n", tid);
	sleep(2);
	return 0;
}
