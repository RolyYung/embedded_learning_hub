#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
int main(int argc, const char *argv[]){
	// 判断参数个数
	if(argc != 2){
		printf("参数个数错误: \n");
		printf("usage: ./a.out fifofilename \n");
		return -1;
	}
	// 创建管道文件
    int mkfifo_ret = 0;
    if(-1 == (mkfifo_ret = mkfifo(argv[1], 0664))){
       perror("read end: create fifo file fail");
       return -1;
    }
    printf("read end create fifo file success \n");
	// 打开管道文件
	int fd = 0;
	fd = open(argv[1], O_RDONLY);
	if(-1 == fd){
		perror("read end- open fifo file fail");
		return -1;
	}
	printf("read end- open fifo file success \n");

	char buf[BUFSIZ] = {0};
	while(1){
		ssize_t ret_read = 0;
		ret_read = read(fd, buf, sizeof(buf)-1);
		if(-1 == ret_read){
			perror("read end- read fifo file fail");
			return -1;
		}
		printf("read end- read fifo file data: %s \n", buf);
		// 手动填充\0
		buf[ret_read] = '\0';
		if(ret_read == 0){
			break;
		}
	}
	// 从管道文件中读取数据
	// 关闭管道文件
	close(fd);
	// unlink fifo file
	if(-1 == unlink(argv[1])){
		perror("read end- unlink fail");
		return -1;
	}

	return 0;
}
