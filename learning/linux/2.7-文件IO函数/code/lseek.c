#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, const char * argv[]){
    int fd = 0;
    fd = open("test.txt", O_RDWR|O_APPEND|O_CREAT, 0664);
    if(fd == -1){
        perror("open test.txt fail");
        return -1;
    }
    printf("open test.txt success, fd=%d \n", fd);

    off_t off;
    off = lseek(fd, 2, SEEK_SET);
    if(off == -1){
        perror("lseek fail");
        return -1;
    }
    printf("lseek file success offset=%ld\n", off);
    // char buf[1024] = {0};
    // read(fd, buf, 10);
    // printf("buf value: %s \n", buf);
    char *p = "hello world";
    write(fd, p, strlen(p));
    printf("p value: %s \n", p);
    close(fd);
    return 0;
}