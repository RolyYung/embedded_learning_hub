#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

#define PORT 8888
#define SERVERIP "192.168.44.100"

int main(){
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1){
        perror("socket fail");
        exit(1);
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVERIP);

    if(-1 == connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr))){
        perror("connect fail");
        close(sockfd);
        exit(1);
    }
    
    signal(SIGPIPE, SIG_IGN);
    while(1){
        char buf[BUFSIZ];
        if(NULL == fgets(buf, BUFSIZ, stdin)){
            close(sockfd);
            exit(1);
        }

        ssize_t nbytes = send(sockfd, buf, strlen(buf), 0);
        if(-1 == nbytes){
            perror("send fail");
            close(sockfd);
            exit(1);
        }
        if(nbytes == strlen(buf)){
            printf("send success \n");
        }

        memset(&buf, 0, sizeof(buf));
        ssize_t recv_nbytes = recv(sockfd, buf, BUFSIZ - 1 , 0);
        if(recv_nbytes == 0){
            printf("server closed \n");
            break;
        }
        if(recv_nbytes == -1){
            perror("recv fail");
            break;
        }
        buf[recv_nbytes] = '\0';
        printf("receive message: %s \n", buf);
    }
    
    close(sockfd);
    return 0;
}