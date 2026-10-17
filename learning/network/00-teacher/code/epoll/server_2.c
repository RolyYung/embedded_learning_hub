#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/epoll.h>

#define PORT 8888
#define MAX_EVENTS 1024
int main(){
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(listenfd == -1){
        perror("socket fail");
        exit(1);
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    if(bind(listenfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1){
        perror("bind");
        exit(EXIT_FAILURE);
    }

    if(listen(listenfd, 5) == -1){
        perror("listen");
        exit(EXIT_FAILURE);
    }

    struct epoll_event ev;
    ev.data.fd = listenfd;
    ev.events = EPOLLIN;

    int epfd = epoll_create1(0);
    if(epfd == -1){
        perror("epoll_create1");
        close(listenfd);
        exit(EXIT_FAILURE);
    }

    if(epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &ev) == -1){
        perror("epoll_ctl");
        close(listenfd);
        exit(EXIT_FAILURE);
    }

    struct epoll_event events[MAX_EVENTS];
    while (1)
    {
        int ready_num = epoll_wait(epfd, &events, MAX_EVENTS, -1);
        if(-1 == ready_num){
            perror("epoll_wait");
            break;
        }
        else if(ready_num > 0){
            for (int i = 0; i < ready_num; i++)
            {
                int fd = events[i].data.fd;
                if(fd == listenfd){
                    struct sockaddr_in client_addr;
                    socklen_t client_len = sizeof(client_addr);
                    int connfd = accept(listenfd, (struct sockaddr *)&client_addr, &client_len);

                    ev.data.fd = connfd;
                    ev.events = EPOLLIN;
                    epoll_ctl(epfd, EPOLL_CTL_ADD, connfd, &ev);

                }else{
                    int connfd = events[i].data.fd;
                    char buf[1024];
                    int nbytes = recv(connfd, buf, 1024, 0);
                    if(nbytes == 0){
                        printf("client closed \n");
                        close(connfd);
                        epoll_ctl(epfd, EPOLL_CTL_DEL,connfd, &events[i]);
                        continue;
                    }else if(nbytes == -1){
                        perror("recv failed");
                        continue;
                    }else {
                        printf("recv message: %s \n", buf);
                    }
                }
            }
            
        }
    }

    close(listenfd);
    close(epfd);
    


    return 0;
}