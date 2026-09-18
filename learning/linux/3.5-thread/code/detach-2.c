#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void * thread(void * arg){
	
	printf("this is a child thread \n");
	return NULL;
}

int main(int argc, const char * argv[]){
	// 创建新线程
	pthread_t tid = 0;
	int ret = 0;
	ret = pthread_create(&tid, NULL, thread, NULL);
	if(ret != 0){
		printf("create pthread fail \n");
		return -1;
	}
	printf("create pthread success \n");

	// 将线程标为分离态
	int ret_detach = 0;
	ret_detach = pthread_detach(tid);
	if(0 != ret_detach){
		printf("detach fail \n");
		return -1;
	}
	printf("detach success \n");
	sleep(5);
	return 0;
}
