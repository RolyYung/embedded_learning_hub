#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

// 线程的入口函数
void * pthread_start(void * arg){
	printf("这是线程的入口函数 \n");
	return NULL; // 没有实际意义
}
int main(int argc, const char * argv[]){
	// 创建新线程
	
	pthread_t pthread_id = 0;
	int ret = 0;
	ret = pthread_create(&pthread_id, NULL, pthread_start, NULL);
	if(ret != 0){
		fprintf(stderr, "线程创建失败,错误码%d, 错误信息:%s ",ret, strerror(ret));
		return -1;
	}
	printf("线程创建成功,线程ID: %ld\n", pthread_id);
	sleep(5);
	return 0;
}
