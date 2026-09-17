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
        // 打开管道文件
		int fd = 0;
		fd = open(argv[1], O_RDONLY);
		if(fd == -1){
			perror("读端 打开文件失败");
			return -1;
		}
		printf("读端 打开文件成功 \n");
        // 向管道文件中读取数据
		char buf[BUFSIZ] = {0};
		ssize_t ret_read = 0;
		if(-1 == (ret_read = read(fd,buf, sizeof(buf)))){
			perror("读端 读取文件失败");
			return -1;
		}
		printf("读端 读取文件成功 \n");
		printf("读端 读取文件的内容: %s \n", buf);
        // 关闭管道文件
		if(-1 == close(fd)){
			perror("读端 关闭文件失败");
			return -1;
		}
		printf("关闭文件成功 \n");
        // 使用unlink函数删除管道文件
		if(-1 == unlink(argv[1])){
			perror("unlink 失败");
			return -1;
		}
		printf("unlink success \n");
        // 一般在读操作进行删除管道文件.
        return 0;
}
