// 模拟kill命令: kill -信号编号 进程号
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>

int main(int argc, const char * argv[]){
	// 1. 参数个数的检查
	if(argc != 3 || argv[1][0] != '-'){
		printf("输入参数有误. \n");
		printf("usage: ./a.out -signum pid");
		return -1;
	}
	// 2. 发送信号前, 把参数转换成整数 atoi
	int signum = 0;
	signum = atoi(argv[1]+1);
	if(0 == signum || signum < 1 || signum > 64){
		printf("signum 信号编号错误 \n");
		return -1;
	}
	int pid = 0;
	if(0 >= (pid = atoi(argv[2]))){
		printf("pid 错误 \n");
		return -1;
	}
	// 3. 使用kill函数 进行发送信号
	int ret = kill(pid, signum);
	if(-1 == ret){
		perror("kill 函数执行失败");
		return -1;
	}
	// 4. 打印结果
	printf("kill -%d %d\n", signum, pid);
	return 0;
}
