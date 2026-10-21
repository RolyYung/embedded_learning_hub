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
                message_recv_state * state = &peer->state;
                if(state->header_received != HEADER_SIZE){
                    ssize_t n = recv(fd, state->header_buf+state->header_received, HEADER_SIZE-state->header_received, 0);
                    if(n <= 0){
                        if(n == 0){
                            printf("server closed \n");
                            
                        }else{
                            perror("recv fail");
                        }
                        free(peer);
                        close(epfd);
                        close(sockfd);
                        exit(1);
                    }
                    state->header_received+=(size_t)n;
                    if(state->header_received == HEADER_SIZE){
                        uint32_t net_type;
                        uint32_t net_len;
                        memcpy(&net_type, state->header_buf, 4);
                        memcpy(&net_len, state->header_buf+4, 4);
                        state->header.type = ntohl(net_type);
                        state->header.body_len = ntohl(net_len);
                        if(state->header.body_len == 0){
                            printf("empty message \n");
                            state->header_received = 0;
                            state->body_received = 0;
                        }
                    }
                }else{
                    uint32_t body_len = state->header.body_len;
                    ssize_t nbytes = recv(fd, state->body_buf+state->body_received, body_len-state->body_received, 0);
                    if(nbytes <=0){
                        // to do : error
                        if(nbytes == 0){
                            perror("server closed");
                        }else{
                            perror("recv fail");
                        }
                        free(peer);
                        close(epfd);
                        close(sockfd);
                        exit(1);
                    }else{
                        state->body_buf[body_len] = '\0';
                        
                        state->body_received += (size_t)nbytes;
                        if(state->body_received > body_len){
                            // error
                        }else if(state->body_received == body_len){
                            printf("recv server echo: %s\n", state->body_buf);
                            memset(state, 0, sizeof(*state));
                        }
                    }
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