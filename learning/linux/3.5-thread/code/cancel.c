// 取消指定线程

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

void * thread_1(void * arg){
	// can cancel and settimout
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
	pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);
	while(1){
		printf("thread_1 is running \n");
		sleep(1);
	}
	return NULL;
}
void * thread_2(void * arg){
	// can cancel and settimout
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
	while(1){
		printf("thread_2 is running \n");
		sleep(1);
	}
	return NULL;
}
void * thread_3(void * arg){
	printf("thread_3 func");
	// can cancel and settimout
	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
	while(1){
		printf("thread_3 is running \n");
		sleep(1);
	}
	return NULL;
}
int main(){

	// 1. 可取消&可延迟取消线程
	pthread_t tid_1 = 0;
	pthread_create(&tid_1, NULL, thread_1, NULL);
	printf("tid_1 value is : %ld \n", tid_1);
	
	pthread_cancel(tid_1); // 取消tid_1线程
	// 2. 可取消&立即取消
	
	pthread_t tid_2 = 0;
	pthread_create(&tid_2, NULL, thread_2, NULL);
	printf("tid_2 value is : %ld \n", tid_2);
	
	pthread_cancel(tid_2); // 取消tid_2线程
	// 3. 不可取消	
	pthread_t tid_3 = 0;
	pthread_create(&tid_3, NULL, thread_3, NULL);
	printf("tid_3 value is : %ld \n", tid_3);	
	int ret = pthread_cancel(tid_3); // 取消tid_3线程
	printf("ret= %d \n", ret);
	if(ret != 0){
		fprintf(stderr, "cancel thread_3 fail, info: %s", strerror(ret));
		return -1;
	}
	pthread_join(tid_1, NULL);
	
	pthread_join(tid_2, NULL);
	pthread_detach(tid_3);
	printf("before return 0 \n");
	return 0;
}
