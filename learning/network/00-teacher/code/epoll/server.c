#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <errno.h>

#define PORT 8888
#define MAX_EVENTS 1024
#define BUF_SIZE 1024

int main(){
    int ret;
    int listenfd = socket(AF_INET, SOCK_STREAM, 6);
    if(listenfd == -1){
        perror("create socket fail");
        exit(1);
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    ret = bind(listenfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if(ret == -1){
        perror("bind fail");
        exit(1);
    }

    ret = listen(listenfd, 5);
    if(ret == -1){
        perror("listen fail");
        exit(1);
    }

    int epfd = epoll_create1(0);
    if(epfd == -1){
        perror("epoll_create1 fail");
        close(listenfd);
        exit(1);
    }

    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = listenfd;

    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &ev);
    if(ret == -1){
        perror("epoll_ctl fail");
        close(listenfd);
        exit(1);
    }

    printf("server listening on port %d...\n", PORT);

    struct epoll_event events[MAX_EVENTS];

    while(1){
        int read_num = epoll_wait(epfd, events, MAX_EVENTS, -1);
        if(read_num == -1){
            if(errno == EINTR){
                continue;
            }

            perror("epoll_wait");
            break;
        }

        for (int i = 0; i < read_num; i++)
        {
            int fd = events[i].data.fd;

            // 有新的连接请求接入
            if(fd == listenfd){
                struct sockaddr_in client_addr;
                socklen_t client_len = sizeof(client_addr);

                int connfd = accept(listenfd, (struct sockaddr*)&client_addr, &client_len);
                if(connfd == -1){
                    perror("accept");
                    continue;
                }

                ev.events = EPOLLIN;
                ev.data.fd = connfd;

                if(epoll_ctl(epfd, EPOLL_CTL_ADD, connfd, &ev) == -1){
                    perror("epoll_ctl connfd");
                    close(connfd);
                    continue;
                }
            }else {
                char buf[BUF_SIZE];
                ssize_t n = recv(fd, buf, sizeof(buf), 0);

                if(n > 0){
                    printf("recv %d bytes \n", n);
                    
                }else if(n == 0){
                    printf("client closed \n");
                    epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL);
                    close(fd);
                }else{
                    perror("recv");
                    epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL);
                    close(fd);
                }
            }
        }
        
    }
    close(epfd);
    close(listenfd);

    return 0;
}