// 没有互斥锁, 多线程是否会出现"竞态条件"

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// global var
int money = 1000;
void * thread_1(void *arg){
	while(1){
		if(money >= 100){
			money -= 100;
			printf("thread_1: money value is : %d \n", money);
		}else{
			printf("thread_1: money is less than 100 \n");
			return NULL;
		}
		sleep(1);
	}
	pthread_exit(NULL);
	return NULL;
}

void * thread_2(void * arg){
	
	while(1){
		if(money >= 50){
			money -= 50;
			printf("thread_2: money value is: %d \n", money);

		}else{
			printf("thrad_2: money is less than 50 \n");
			return NULL;
		}
		sleep(1);
	}
	pthread_exit(NULL);
	return NULL;
}
int main(int argc, const char * argv[]){
	// new thread-1
	pthread_t tid_1 = 0;
	pthread_create(&tid_1, NULL, thread_1, NULL);
	
	// new thread-2
	pthread_t tid_2 = 0;
	pthread_create(&tid_2, NULL, thread_2, NULL);


	pthread_join(tid_1, NULL);
	pthread_join(tid_2, NULL);
	return 0;
}
