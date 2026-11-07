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
#include <unordered_map>

#define ERR_VAL -1
#define PORT 8888
#define SERVER_IP "192.168.44.100"
#define MAX_EVENTS 1024

using namespace std;

int main(){
    // ----初始化
    signal(SIGPIPE, SIG_IGN);
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(listenfd == ERR_VAL){
        perror("socket fail");
        return -1;
    }

    int opt = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

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
    unordered_map<int, connection> clients;
    connection listen_peer{};
    listen_peer.fd = listenfd;
    clients[listenfd] = listen_peer;
    ev.data.fd = listenfd;

    ev.events = EPOLLIN;
    int ret = epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &ev);
    if(ret == -1){
        perror("epoll_ctl add");
        close(listenfd);
        close(epfd);
        exit(1);
    }
    // ----初始化结束.

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
            auto& peer = clients.at(e_events[i].data.fd);
            if(peer.fd == listenfd){
                // ----- 接受连接
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
                connection peer{};
                peer.addr = client_addr;
                peer.fd = acceptfd;
                clients[acceptfd] = peer;
                ev.data.fd = acceptfd;
                ev.events = EPOLLIN;
                ret = epoll_ctl(epfd, EPOLL_CTL_ADD, acceptfd, &ev);
                if(ret == -1){
                    perror("epoll_ctl");
                    close(acceptfd);
                    clients.erase(acceptfd);
                    continue;
                }
                // -----接受连接完成 加入epoll等待池

            }
            else {
                int fd = peer.fd;
                // -----接收数据
                ssize_t nbytes = recv_msg(&peer);
                if(nbytes < 0){
                    // -----接收数据报错
                    // 删除epoll池
                    ret = epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL);
                    if(ret == -1){
                        perror("epoll ctl - del fd");
                    }
                    close(fd);
                    clients.erase(fd);
                    continue;
                }
                else if(nbytes > 0){
                    // ----接收数据完成.
                    message_recv_state * state = &(peer.state);
                    ssize_t nbytes_send = send_msg(fd, state->header, state->body_buf);

                    if(-1 == nbytes_send){
                        perror("send fail");
                        close(epfd);
                        close(listenfd);
                        exit(1);
                    }

                    char ip[20];
                    inet_ntop(AF_INET, &(peer.addr.sin_addr), ip, sizeof(ip));
                    printf("====client[%s:%d], send message==== \n\n", ip, ntohs(peer.addr.sin_port));
                    printf("message type: %d, message length: %d \n", state->header.type, state->header.body_len);
                    printf("message content: %s \n", state->body_buf);
                    printf("====client[%s:%d], send message==== \n", ip, ntohs(peer.addr.sin_port));
                    // 重置接收结构体.
                    memset(state, 0 ,sizeof(message_recv_state));
                }
            }
        }
    }
    close(epfd);
    close(listenfd);
    
    return 0;
}
