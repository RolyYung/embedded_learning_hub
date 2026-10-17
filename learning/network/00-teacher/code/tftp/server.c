#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <libgen.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>


#define BASE_DIR "/home/roly/embedded/tftp" 
#define BLOCK_SIZE 512  
#define SERVER_IP "127.0.0.1"
#define PORT 3456 // 服务器监听端口

typedef enum{
    OP_RRQ = 1,
    OP_WRQ,
    OP_DATA,
    OP_ACK,
    OP_ERROR
}tftp_opcode;

void ensure_dir_exists(path);
void handle_upload(int socket, struct sockaddr_in *client_addr, char *filename);
void handle_download(int socket, struct sockaddr_in *client_addr, char *filename);

int main(){

    ensure_dir_exists(BASE_DIR);
    printf("base dir path: %s", BASE_DIR);

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    // server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
    inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);

    bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    while(1){
        uint8_t buf[516];
        struct sockaddr_in client_addr;
        client_addr.sin_family = AF_INET;
        socklen_t client_len = sizeof(client_addr);
        
        ssize_t nbytes = recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr*)&client_addr, &client_addr);

        if(nbytes > 2){
            char *filename = (char *)(buf + 2);
            char *mode = filename + strlen(filename) + 1;
            char client_ip[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, INET_ADDRSTRLEN);
            printf("收到了来自客户端%s:%d的请求\n", client_ip, ntohs(client_addr.sin_port));

            
            if(buf[1] == OP_RRQ){
                // 读
                handle_download(sockfd, &client_addr, filename);
            }else if(buf[1] == OP_WRQ){
                // 写
                handle_upload(sockfd, &client_addr, filename);
            }else{
                printf("other op code \n");
            }
        }

    }

    return 0;
}

void ensure_dir_exists(path){
    struct stat st;
    if(stat(path, &st) == -1){
        mkdir(path, 0755);
        printf("dir dont exist, mkdir success \n");
    }else{
        printf("dir exist \n");
    }
    return ;
}

void handle_download(int socket, struct sockaddr_in *client_addr, char *filename){
    // pure filename
    char * fname_copy = strdup(filename);
    char * pure_filename = basename(fname_copy);

    char fullpath[256];
    snprintf(fullpath, sizeof(fullpath), "%s/%s", BASE_DIR, pure_filename);
    
    int fd = open(fullpath, O_RDONLY);
    if(fd < 0){
        perror("open fail");
        return ;
    }

    uint8_t buf[BLOCK_SIZE + 4];
    uint16_t block = 1;
    ssize_t bytes_read;
    while((bytes_read = read(socket, buf+4, BLOCK_SIZE)) > 0){
        buf[0] = 0;
        buf[1] = OP_DATA;
        buf[2] = block >> 8;
        buf[3] = block;

        sendto(socket, buf, bytes_read+4, 0, (struct sockaddr *)client_addr, sizeof(*client_addr));

        fd_set read_fds;
        FD_ZERO(&read_fds);  
        FD_SET(socket, &read_fds); 
        struct timeval timeout = {5, 0}; 

        select(socket + 1, &read_fds, NULL, NULL, &timeout);
        
    }
}

void handle_upload(int socket, struct sockaddr_in *client_addr, char *filename){}