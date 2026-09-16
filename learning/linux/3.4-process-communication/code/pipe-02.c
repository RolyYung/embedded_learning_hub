// 读端不存在 写端存在会发生什么?
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){
	
	int fd[2] = {0};
	pipe(fd);
	printf("无名管道创建完成 \n");

	pid_t pid = fork();
	if(pid == -1){
		perror("fork失败");
		return -1;
	}
	else if(pid == 0){
		// 子进程
		close(fd[0]);
		close(fd[1]);
		printf("子进程退出成功 \n");
		exit(EXIT_SUCCESS);
	}
	else if(pid > 0){
		// 父进程
		wait(NULL);
		close(fd[0]);
		int write_ret = 0;
		printf("开始写入: ... \n");
		write_ret = write(fd[1], "hello world", 12);
		// 后面的代码不再会执行, 因为两个读端都没有了
		// 进程默认你写入的也不再有读者 所以会想内核发送SIGPIPE信号
		// 这样就导致程序被终止, 即使有报错也不会再展示.
		perror("错误信息");
		printf("写入完成 \n");
		if(write_ret == -1){
			perror("写入失败");
			return -1;
		}
		printf("写入成功 \n");

	}

	return 0;
}
