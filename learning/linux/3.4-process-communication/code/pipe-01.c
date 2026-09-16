#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc,const char * argv[]){
	// 创建无名管道
	int fd[2] = {0};
	int pipe_ret = 0;
	pipe_ret = pipe(fd);
	if(pipe_ret == -1){
		perror("创建无名管道失败");
		return -1;
	}
	// 1. pipe的文件描述符和open的文件描述符是同一组
	// 2. fd[0]表示的是读端, fd[1]表示的是写端
	printf("创建无名管道成功, fd[0]=%d,fd[1]=%d \n", fd[0], fd[1]);
	// 创建子进程
	pid_t pid = fork();
	if(-1 == pid){
		perror("创建子进程失败 \n");
		return -1;
	}
	else if(pid == 0){
		// 子进程
		// 子进程接收父进程的数据 读数据
		// 关闭子进程的写端
		if(-1 == close(fd[1])){
			perror("关闭子进程写端失败 \n");
			return -1;
		}
		printf("关闭子进程写端成功 \n");
		// 无名管道读取数据
		char buf_str[BUFSIZ] = {0};
		ssize_t read_ret = 0;
		read_ret = read(fd[0], buf_str, sizeof(buf_str));
		if(-1 == read_ret){
			perror("无名管道读取数据失败");
			return -1;
		}
		printf("从无名管道中读取数据成功, 读取到的数据: \n");
		printf("%s \n", buf_str);
		// 关闭子进程的读端
		if(-1 == close(fd[0])){
			perror("关闭读端失败--子进程 \n");
			return -1;
		}
		printf("关闭子进程读端成功");
		exit(EXIT_SUCCESS);
	}
	else if(pid > 0){
		
		// 父进程
		// 关闭父进程的读端
		int close_ret = 0;
		close_ret = close(fd[0]);
		if(close_ret == -1){
			perror("关闭父进程读端失败 \n");
			return -1;
		}
		printf("关闭父进程读端成功 \n");
		// 往无名管道写入数据
		char * str = "hello world";
		ssize_t write_ret = 0;
		if(-1 == (write_ret = write(fd[1], str, strlen(str)))){
			perror("文件写入失败: ");
			return -1;
		}
		printf("无名管道写入成功 \n");
		// 关闭父进程的写端
		if(-1 == close(fd[1])){
			perror("关闭父进程写端失败 \n");
			return -1;
		}
		printf("已将数据写入到管道中 \n");
		wait(NULL);	
	}
	return 0;
}
