#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, const char * argv[]){
	// 输入参数个数检查
	if(argc != 2){
		printf("输入的参数个数有误 \n");
		printf("usage: ./a.out pipefilename \n");
		return -1;
	}
	/*
	// 创建管道文件
	int mkfifo_ret = 0;
	if(-1 == (mkfifo_ret = mkfifo(argv[1], 0664))){
		perror("write end: create fifo file fail");
		return -1;
	}
	printf("write end create fifo file success \n");
	*/
	// 打开管道文件
	int fd = 0;
	// write only to open file
	// 非阻塞标志, O_NONBLOCK
	fd = open(argv[1], O_WRONLY);
	if(fd == -1){
		perror("open fifo file fail");
		return -1;
	}
	printf("open fifo file success \n");

	// 管道文件写入
	// 从终端获取写入数据
	char buf[1024] = {0};
	ssize_t ret = 0;
	while(1){
		printf("input fifo file data: \n");
		scanf("%s", buf);
		
		ret = write(fd, buf, sizeof(buf));
		if(ret == -1){
			perror("write end: write data fail");
			close(fd);
			return -1;
		}
		printf("写入的数据: %s \n", buf);
	}
	// 关闭管道文件
	if(-1 == close(fd)){
		perror("close write fifo fail");
		return -1;
	}
	printf("close write fifo file success");
	// in write end don't unlink pipe file
	return 0;
}
