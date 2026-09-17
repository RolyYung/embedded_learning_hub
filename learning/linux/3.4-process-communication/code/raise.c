#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

void handler(int sig){
	if(sig == SIGCHLD){
		printf("子进程退出, 捕捉到了SIGCHLD信号 \n");
		// 父进程回收子进程的资源
		wait(NULL); // 不关注子进程的退出状态值
	}
	return ;
}
int main(int argc, char * argv[]){
	
	// 建立信号 与 信号处理方式的关联
	// 捕捉
	if(SIG_ERR == signal(SIGCHLD, handler)){
		perror("关联失败");
		return -1;
	}
	printf("关联成功 \n");
	// SIGCHLD: 当子进程退出的时候, 发送的信号.
	// 创建子进程
	pid_t pid = fork();
	if(pid == -1){
		perror("创建子进程失败");
		return -1;
	}
	else if(pid == 0){
		// 子进程
		printf("我是子进程,我的pid=%d \n", getpid());
		printf("子进程延时5秒之后退出 \n");
		sleep(5);
		exit(EXIT_SUCCESS);
	}
	else if(pid > 0){
		// 父进程
		printf("我是父进程, 我的pid=%d \n", getpid());
		sleep(8);
		// 父进程向自身发送指定的信号
		// SIGKILL: 杀死进程. 不能被捕捉和忽略
		raise(SIGKILL);
	}
	//
	return 0;
}
