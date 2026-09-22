#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>


int main(int argc, const char *argv[]){
    int fd = open("test.txt", O_RDWR | O_TRUNC | O_CREAT, 0666);
    if(fd == -1){
        perror("open file fasil");
        return -1;
    }
    printf("open file success \n");

    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;

    fcntl(fd, F_SETLK, &lock);
    printf("add lock success \n");

    char *str = "hello world";
    write(fd, str, strlen(str));
    printf("write done \n");
    lock.l_type = F_UNLCK;
    fcntl(fd, F_UNLCK, &lock);
    printf("unlock success \n");

    close(fd);
    printf("close file success \n");
    return 0;
}