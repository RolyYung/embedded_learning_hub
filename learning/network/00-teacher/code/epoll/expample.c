#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/epoll.h>

#define PORT 8888
#define MAX_EVENTS 1024
#define BUF_SIZE 1024

int main(void)
{
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    int opt = 1;
    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR,
                   &opt, sizeof(opt)) == -1) {
        perror("setsockopt");
        close(listenfd);
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(listenfd,
             (struct sockaddr *)&server_addr,
             sizeof(server_addr)) == -1) {
        perror("bind");
        close(listenfd);
        exit(EXIT_FAILURE);
    }

    if (listen(listenfd, 128) == -1) {
        perror("listen");
        close(listenfd);
        exit(EXIT_FAILURE);
    }

    int epfd = epoll_create1(0);
    if (epfd == -1) {
        perror("epoll_create1");
        close(listenfd);
        exit(EXIT_FAILURE);
    }

    struct epoll_event ev;
    ev.events = EPOLLIN;
    ev.data.fd = listenfd;

    if (epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &ev) == -1) {
        perror("epoll_ctl listenfd");
        close(epfd);
        close(listenfd);
        exit(EXIT_FAILURE);
    }

    printf("server listening on port %d...\n", PORT);

    struct epoll_event events[MAX_EVENTS];

    while (1) {
        int ready_num = epoll_wait(epfd, events, MAX_EVENTS, -1);
        if (ready_num == -1) {
            if (errno == EINTR) {
                continue;
            }

            perror("epoll_wait");
            break;
        }

        for (int i = 0; i < ready_num; i++) {
            int fd = events[i].data.fd;

            if (fd == listenfd) {
                struct sockaddr_in client_addr;
                socklen_t client_len = sizeof(client_addr);

                int connfd = accept(
                    listenfd,
                    (struct sockaddr *)&client_addr,
                    &client_len
                );

                if (connfd == -1) {
                    perror("accept");
                    continue;
                }

                char client_ip[INET_ADDRSTRLEN];

                if (inet_ntop(AF_INET,
                              &client_addr.sin_addr,
                              client_ip,
                              sizeof(client_ip)) != NULL) {
                    printf("client connected: %s:%d, fd=%d\n",
                           client_ip,
                           ntohs(client_addr.sin_port),
                           connfd);
                }

                ev.events = EPOLLIN;
                ev.data.fd = connfd;

                if (epoll_ctl(epfd,
                              EPOLL_CTL_ADD,
                              connfd,
                              &ev) == -1) {
                    perror("epoll_ctl connfd");
                    close(connfd);
                    continue;
                }
            } else {
                char buf[BUF_SIZE];

                ssize_t n = recv(fd, buf, sizeof(buf), 0);

                if (n > 0) {
                    printf("recv fd=%d, %zd bytes\n", fd, n);

                    ssize_t total = 0;

                    while (total < n) {
                        ssize_t sent = send(
                            fd,
                            buf + total,
                            n - total,
                            0
                        );

                        if (sent == -1) {
                            perror("send");
                            break;
                        }

                        total += sent;
                    }
                } else if (n == 0) {
                    printf("client closed, fd=%d\n", fd);

                    epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL);
                    close(fd);
                } else {
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