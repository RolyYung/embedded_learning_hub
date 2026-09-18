// 一般不关注子线程的退出状态值
// 此代码, 用于展示这个特殊情况

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void * thread(void * arg){
	static int g_value = 100;
	pthread_exit((void *)&g_value);
	return NULL;
}
int main(int argc, const char * argv[]){
	
	pthread_t tid = 0;
	pthread_create(&tid, NULL, thread, NULL);
	printf("create pthread success, tid is : %ld \n", tid);
	int *value = NULL;
	int ret = pthread_join(tid, (void **)&value);
	if(ret != 0){
		printf("回收失败 \n");
		return -1;
	}
	printf("child pthread exit success \n");
	printf("child pthread exit status value: %d\n", *value);
	sleep(3);
	return 0;
}
