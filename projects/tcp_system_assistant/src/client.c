#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/epoll.h>
#include "message.h"

#define PORT 8888
#define SERVERIP "192.168.44.100"

int main(){
    signal(SIGPIPE, SIG_IGN);
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

    int epfd = epoll_create1(0);
    if(epfd == -1){
        perror("epoll_create1");
        close(sockfd);
        exit(1);
    }


    
    struct epoll_event e_events[2];

    connection * in_peer = (connection *)malloc(sizeof(connection));
    if(in_peer == NULL){
        printf("in_peer malloc fail \n");
        close(sockfd);
        close(epfd);
        exit(1);
    }
    memset(in_peer, 0, sizeof(connection));
    in_peer->fd = STDIN_FILENO;
    e_events[0].data.ptr = in_peer;
    e_events[0].events = EPOLLIN;
    if(-1 == epoll_ctl(epfd, EPOLL_CTL_ADD, STDIN_FILENO, &e_events[0])){
        perror("epoll_ctl add");
        close(sockfd);
        close(epfd);
        exit(1);
    }

    connection * peer = (connection *)malloc(sizeof(connection));
    if(peer == NULL){
        printf("malloc fail \n");
        close(sockfd);
        close(epfd);
        exit(1);
    }

    memset(peer, 0, sizeof(connection));
    peer->fd = sockfd;

    e_events[1].data.ptr = peer;
    e_events[1].events = EPOLLIN;
    if(-1 == epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &e_events[1])){
        perror("epoll_ctl add");
        close(sockfd);
        close(epfd);
        exit(1);
    }
    char buf[BUFSIZ];
    while(1){
        int ready_num = epoll_wait(epfd, e_events, 2, -1);
        if(ready_num == -1){
            perror("epoll_wait");
            break;
        }
        
        for (int i = 0; i < ready_num; i++)
        {
            connection *ptr = e_events[i].data.ptr;
            int fd = ptr->fd;
            if(fd == STDIN_FILENO){
                if(NULL == fgets(buf, BUFSIZ, stdin)){
                    close(epfd);
                    close(sockfd);
                    exit(1);
                }
                message_header header;
                header.type = 1;
                header.body_len = strlen(buf);


                ssize_t nbytes = send_msg(sockfd, header, buf);
                if(-1 == nbytes){
                    perror("send fail");
                    close(epfd);
                    close(sockfd);
                    exit(1);
                }
                printf("send success \n");
            }else if(fd == sockfd){
                ssize_t nbytes = recv_msg(ptr);
                // nbytes == 0时, 消息体未接收完成.
                if(nbytes < 0){
                    free(ptr);
                    close(epfd);
                    close(sockfd);
                    exit(1);
                }else if(nbytes > 0){
                    printf("recv server echo: %s\n", ptr->state.body_buf);
                    memset(&(ptr->state), 0, sizeof(ptr->state));
                }
            }else{
                close(epfd);
                close(sockfd);
                exit(1);
            }
        }
    }
    close(epfd);
    close(sockfd);
    return 0;
}