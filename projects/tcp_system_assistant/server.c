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

#define ERR_VAL -1
#define PORT 8888
#define SERVER_IP "192.168.44.100"
#define MAX_EVENTS 1024


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
    ev.data.fd = listenfd;
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
            int fd = e_events[i].data.fd;
            if(fd == listenfd){
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
                ev.data.fd = acceptfd;
                ev.events = EPOLLIN;
                ret = epoll_ctl(epfd, EPOLL_CTL_ADD, acceptfd, &ev);
                if(ret == -1){
                    perror("epoll_ctl");
                    close(acceptfd);
                    continue;
                }

            }
            else {
                // 连接fd, 有新的读取数据, 也就是有客户端发送消息来了.
                char buf[BUFSIZ] = {0};
                ssize_t nbytes = 0;
                
                nbytes = recv(fd, buf, BUFSIZ-1, 0);
                if(nbytes == 0){
                    // 断开连接
                    printf("client closed \n");
                    // 删除epoll池
                    ret = epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL);
                    if(ret == -1){
                        perror("epoll ctl - del fd");
                    }
                    close(fd);
                    continue;
                }else if(nbytes < 0){
                    perror("recv fail");
                     // 删除epoll池
                    ret = epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL);
                    if(ret == -1){
                        perror("epoll ctl - del fd");
                    }
                    close(fd);
                    continue;
                }
                buf[nbytes] = '\0';
                printf("recv data msg: %s \n", buf);
                char buf_2[BUFSIZ + 13] = {0};
                strcpy(buf_2, buf);
                strcat(buf_2, "--from server");
                if(-1 == send(fd, buf_2, strlen(buf_2), 0)){
                    perror("send fail");
                     // 删除epoll池
                    ret = epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL);
                    if(ret == -1){
                        perror("epoll ctl - del fd");
                    }
                    close(fd);
                    continue;
                }
            }
        }
    }
    close(epfd);
    close(listenfd);
    
    return 0;
}