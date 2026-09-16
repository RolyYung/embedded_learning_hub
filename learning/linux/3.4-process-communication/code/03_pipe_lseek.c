// 测试无名管道 无法使用lseek函数, 调用会直接调用失败, 返回-1值
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(){
	// 创建无名管道
	int fd[2] = {0};
	if(-1 == pipe(fd)){
		perror("创建无名管道失败");
		return -1;
	}
	printf("创建无名管道成功 \n");
	if(-1 == close(fd[0])){
		perror("关闭读端失败");
		return -1;
	}
	printf("关闭读端成功 \n");
	// 从文件开始位置偏移零个字节
	if(-1 == lseek(fd[1], 0, SEEK_SET)){
		perror("使用lseek 函数失败");
		return -1;
	}	
	printf("使用lseek函数成功");

	if(-1 == close(fd[1])){
		perror("关闭写端失败");
		return -1;
	}
	printf("关闭写端成功");

	return 0;
}
