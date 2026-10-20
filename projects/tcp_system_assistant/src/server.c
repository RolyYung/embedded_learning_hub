#include <stdio.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/epoll.h>
#include "message.h"

#define ERR_VAL -1
#define PORT 8888
#define SERVER_IP "192.168.44.100"
#define MAX_EVENTS 1024

typedef struct {
    int fd;
    struct sockaddr_in addr;
    message_recv_state state;
}connection;


int main(){
    signal(SIGPIPE, SIG_IGN);
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(listenfd == ERR_VAL){
        perror("socket fail");
        return -1;
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);

    if(-1 == bind(listenfd, (struct sockaddr*)&server_addr, sizeof(server_addr))){
        perror("bind fail");
        close(listenfd);
        return -1;
    }

    if(-1 == listen(listenfd, 5)){
        perror("listen fail");
        close(listenfd);
        return -1;
    }

    int epfd = epoll_create1(0);
    if(epfd == -1){
        perror("epoll create1");
        close(listenfd);
        exit(1);
    }

    struct epoll_event ev;
    connection *listen_peer = (connection*)malloc(sizeof(connection));
    if(listen_peer == NULL){
        close(listenfd);
        exit(1);
    }
    memset(listen_peer, 0, sizeof(connection));
    listen_peer->fd = listenfd;
    ev.data.ptr = listen_peer;
    ev.events = EPOLLIN;
    int ret = epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &ev);
    if(ret == -1){
        perror("epoll_ctl add");
        close(listenfd);
        close(epfd);
        exit(1);
    }

    struct epoll_event e_events[MAX_EVENTS];
    while (1)
    {
        int ready_num = epoll_wait(epfd, e_events, MAX_EVENTS, -1);
        if(ready_num == -1){
            perror("epoll_wait");
            close(epfd);
            close(listenfd);
            exit(1);
        }
        for(int i=0;i<ready_num;i++){
            connection * peer = e_events[i].data.ptr;
            if(peer->fd == listenfd){
                // 监听fd有新的读取任务了. 也就是有新的连接请求.
                // accept接收新的连接, 并将连接加入到epoll池中.
                struct sockaddr_in client_addr;
                client_addr.sin_family = AF_INET;
                socklen_t addrlen = sizeof(client_addr);
                int acceptfd = accept(listenfd, (struct sockaddr *)&client_addr, &addrlen);
                if(acceptfd == -1){
                    perror("accept fail");
                    continue;
                }
                char ip[20];
                inet_ntop(AF_INET, &client_addr.sin_addr, ip, 20);
                printf("client info: [%s:%d]\n", ip, ntohs(client_addr.sin_port));
                

                // 加入连接池.
                connection* peer = (connection*)malloc(sizeof(connection));
                if(peer == NULL){
                    close(acceptfd);
                    continue;
                }
                memset(peer, 0, sizeof(connection));
                peer->fd = acceptfd;
                peer->addr = client_addr;

                ev.data.ptr = peer;
                ev.events = EPOLLIN;
                ret = epoll_ctl(epfd, EPOLL_CTL_ADD, acceptfd, &ev);
                if(ret == -1){
                    perror("epoll_ctl");
                    free(peer);
                    close(acceptfd);
                    continue;
                }

            }
            else {
                int fd = peer->fd;
                message_recv_state* state = &peer->state;
                if(state->header_received == HEADER_SIZE){
                    uint32_t body_len = state->header.body_len;
                    ssize_t n_body = recv(fd, state->body_buf + state->body_received, body_len-state->body_received, 0);
                    if(n_body <= 0){
                        if(n_body == 0){
                            printf("client closed \n");
                        }else{
                            perror("recv error");
                        }
                        // 删除epoll池
                        ret = epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL);
                        if(ret == -1){
                            perror("epoll ctl - del fd");
                        }
                        close(fd);
                        free(peer);
                        continue;
                    }
                    state->body_received += n_body;
                    if(state->body_received == body_len){
                        state->body_buf[state->body_received] = '\0';
                        printf("recv done: %s \n", state->body_buf);
                        send_msg(fd, state->header, state->body_buf);

                        state->body_received = 0;
                        state->header_received = 0;
                        
                    }
                    continue;
                }
                // 连接fd, 有新的读取数据, 也就是有客户端发送消息来了.
                
                ssize_t nbytes = 0;
                
                nbytes = recv(fd, state->header_buf + state->header_received, HEADER_SIZE - state->header_received, 0);
                if(nbytes == 0){
                    // 断开连接
                    printf("client closed \n");
                    // 删除epoll池
                    ret = epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL);
                    if(ret == -1){
                        perror("epoll ctl - del fd");
                    }
                    close(fd);
                    free(peer);
                    continue;
                }else if(nbytes < 0){
                    perror("recv fail");
                     // 删除epoll池
                    ret = epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL);
                    if(ret == -1){
                        perror("epoll ctl - del fd");
                    }
                    close(fd);
                    free(peer);
                    continue;
                }
                
                state->header_received += nbytes;
                if(state->header_received < HEADER_SIZE){
                    continue;
                }

                // 取出消息类型; 消息长度
                uint32_t net_type;
                uint32_t net_len;

                memcpy(&net_type, state->header_buf, 4);
                memcpy(&net_len, state->header_buf+4, 4);

                state->header.type = ntohl(net_type);
                state->header.body_len = ntohl(net_len);

                if(net_len == 0){
                    printf("recv done: empty message\n");
                    state->header_received = 0;
                    state->body_received = 0;
                    continue;
                }

                printf("message type: %d, message length: %d \n", state->header.type, state->header.body_len);

                // buf[nbytes] = '\0';
                // printf("recv data msg: %s \n", buf);
                // char buf_2[BUFSIZ + 13] = {0};
                // strcpy(buf_2, buf);
                // strcat(buf_2, "--from server");
                // if(-1 == send(fd, buf_2, strlen(buf_2), 0)){
                //     perror("send fail");
                //      // 删除epoll池
                //     ret = epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL);
                //     if(ret == -1){
                //         perror("epoll ctl - del fd");
                //     }
                //     close(fd);
                //     free(peer);
                //     continue;
                // }
            }
        }
    }
    close(epfd);
    free(listen_peer);
    close(listenfd);
    
    return 0;
}