#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(const int argc, char * argv[]){
	if(argc != 3){
		printf("参数传递错误! \n");
		return -1;
	}
	int src_fd = -1;
	int dest_fd = -1;
	if(-1 == (src_fd = open(argv[1], O_RDONLY))){
		printf("打开文件失败 \n");
		return -1;
	}
	while(1){
		char buf[BUFSIZ] = {0};
		int read_ret;
		if(-1 == (read_ret = read(src_fd, buf, BUFSIZ))){
			printf("文件读取失败 \n");
			close(src_fd);
			return -1;
		}

		if(-1 == (dest_fd = open(argv[2], O_WRONLY | O_CREAT, 0666))){
			printf("打开文件失败 \n");
			return -1;
		}
		if(-1 == (write(dest_fd, buf, BUFSIZ))){
			printf("写入文件失败 \n");
			close(dest_fd);
			return -1;
		}
		if(read_ret < BUFSIZ){
			break;
		}
		
	}
	printf("cp done \n");
	return 0;
}
