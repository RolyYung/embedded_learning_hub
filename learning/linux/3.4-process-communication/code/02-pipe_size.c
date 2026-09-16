#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

int main(){
	int pipefd[2] = {0};
	if( -1== pipe(pipefd)){
		perror("创建匿名管道失败 \n");
		return -1;
	}
	printf("创建无名管道成功 \n");

	// fork 函数创建子进程
	pid_t pid = fork();
	if(-1 == pid){
		perror("创建子进程失败 \n");
		return -1;
	}
	else if(pid == 0){
		// 子进程
		close(pipefd[0]);
		int count = 0;
		
		while(1){
			char buf_str[1024] = {0};
			int write_ret = 0;
			write_ret = write(pipefd[1], buf_str, 1024);
			count += write_ret;
			printf("写入数据字节数: %d \n", count);
		}
		close(pipefd[1]);
	}
	else if(pid > 0){
		// 父进程
		close(pipefd[1]);
		wait(NULL);
		close(pipefd[0]);
	}

	return 0;
}
