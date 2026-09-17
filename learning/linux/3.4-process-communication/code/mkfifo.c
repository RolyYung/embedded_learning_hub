#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, const char * argv[]){
	// 1. 对输入的参数做检查
	if(argc != 2){
		printf("输入参数个数有误 \n");
		printf("usage: ./a.out filename");
		return -1;
	}

	// 2. 创建有名管道, 用mkfifo函数
	int ret = 0;
	ret = mkfifo(argv[1], 0664);
	// 如果管道文件存在, 就会进行报错.
	if(ret == -1){
		perror("创建有名管道失败");
		return -1;
	}
	printf("创建有名管道成功 \n");

	// 3. 创建子进程
	pid_t pid = fork();
	if(pid == -1){
		perror("创建子进程失败");
		return -1;
	}
	else if (pid == 0){
		// 子进程
		// 打开管道文件
		// 内核管道缓存区只会在第一次open函数调用才会进行分配
		int fd = open(argv[1], O_WRONLY);
		if(fd == -1){
			perror("打开文件失败");
			unlink(argv[1]);
			return -1;
		}
		printf("打开管道文件成功");
		// 往管道中写入数据
		char buf_str[] = "hello world\n";
		ssize_t ret_write = 0;
		ret_write = write(fd,buf_str, sizeof(buf_str));
		if(ret_write == -1){
			perror("子进程写入数据失败 \n");
			return -1;
		}
		printf("子进程写入数据成功");
		// 关闭管道文件
		if(-1 == close(fd)){
			perror("子进程关闭管道失败");
			return -1;
		}
		printf("子进程关闭管道成功");
		exit(EXIT_SUCCESS);
	}
	else if (pid > 0) {
		// 父进程
		// 等待子进程的退出

		// 打开管道文件
		int fd = open(argv[1], O_RDONLY);
		if(fd == -1){
			perror("父进程 打开文件失败");
			return -1;
		}
		printf("父进程打开文件成功 \n");
		wait(NULL); // 不关心子进程的退出状态值
		// 从管道文件中读取数据
		char buf[BUFSIZ] = {0};
		ssize_t ret_read = 0;
		ret_read = read(fd, buf, sizeof(buf));
		if(ret_read == -1){
			perror("父进程 读取数据失败");
			return -1;
		}
		printf("父进程 读取数据成功 \n");
		printf("读取的数据: %s \n", buf);
		// 关闭管道文件
		close(fd);
	}
	
	return 0;
}
