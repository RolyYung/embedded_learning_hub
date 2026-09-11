#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(const int argc, char * argv[]){
    int fd = open("test.txt", O_RDONLY);
    if(fd == -1){
        perror("文件读取失败: ");
    }
    char buf[BUFSIZ] = {0};
    if(read(fd, buf, BUFSIZ) > 0){
        printf("%s\n", buf);
    }

    return 0;
}