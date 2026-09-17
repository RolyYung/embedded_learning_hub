#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, const char * argv[]){
	// 判断参数输入个数
	if(argc != 2){
		printf("输入的参数个数有误 \n");
		printf("usage: ./a.out pathname \n");
		return -1;
	}
	// 创建管道文件
	int mkfifo_ret = 0;
	mkfifo_ret = mkfifo(argv[1], 0664);
	if(-1 == mkfifo_ret){
		return -1;
	}
	// 打开管道文件
	int fd = open(argv[1], O_WRONLY);
	if(fd == -1){
		perror("写端: 打开文件失败");
		return -1;
	}
	printf("写端: 打开文件成功\n");
	// 向管道文件中写入数据
	ssize_t ret_write = 0;
	char buf[] = "12345678";
	if(-1 == (ret_write = write(fd, buf, sizeof(buf)))){
		perror("写端: 写入失败");
	}
	printf("写端: 向管道文件中写入数据成功 \n");
	// 关闭管道文件
	if(-1 == close(fd)){
		perror("写端 关闭管道文件失败");
		return -1;
	}
	printf("写端 关闭管道文件成功 \n");
	return 0;
}
