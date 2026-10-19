#include <stdio.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>


#define ERR_VAL -1
#define PORT 8888
#define SERVER_IP "192.168.44.100"
int main(){
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

    struct sockaddr_in client_addr;
    client_addr.sin_family = AF_INET;
    socklen_t addrlen = sizeof(client_addr);
    int acceptfd = accept(listenfd, (struct sockaddr *)&client_addr, &addrlen);
    if(acceptfd == -1){
        perror("accept fail");
        exit(1);
    }

    while (1)
    {
        
        char buf[BUFSIZ] = {0};
        ssize_t nbytes;
        nbytes = recv(acceptfd, buf, BUFSIZ, 0);
        if(nbytes == -1){
            perror("recv fail");
            break;
        }
        if(nbytes == 0){
            printf("client closed \n");
            close(acceptfd);
            break;
        }
        char ip[20] = {0};
        printf("recv client[%s:%d] message: %s\n", inet_ntop(AF_INET, &client_addr.sin_addr, ip, 20 ), ntohs(client_addr.sin_port), buf);

        strcat(buf, "--from server");
        if(-1 == send(acceptfd, buf, BUFSIZ, 0)){
            perror("send fail");
            continue;
        }
    }
    close(listenfd);
    
    return 0;
}