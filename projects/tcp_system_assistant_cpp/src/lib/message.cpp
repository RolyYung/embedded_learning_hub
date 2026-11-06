#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdint.h>
#include <errno.h>
#include "message.h"


ssize_t send_msg(int fd, message_header header, const char * message){
    // to net byte order
    uint32_t len = header.body_len;
    if(len > BUFSIZ){
        errno = EMSGSIZE;
        return -1;
    }

    uint32_t net_type = htonl(header.type);
    uint32_t net_len = htonl(len);
    unsigned char msg_buf[BUFSIZ + 8];
    memcpy(msg_buf,     &net_type, 4);
    memcpy(msg_buf + 4, &net_len,  4);
    if (len > 0) {
        memcpy(msg_buf + 8, message, len);
    }

    size_t total = 8 + len;
    size_t sent = 0;
    while (sent < total) {
        ssize_t n = send(fd, msg_buf + sent, total - sent, 0);

        if (n <= 0) {
            return -1;
        }

        sent += (size_t)n;
    }
    return (ssize_t)sent;
}

ssize_t recv_msg(connection* peer){
    int fd = peer->fd;
    message_recv_state * state = &(peer->state);
    if(state->header_received != HEADER_SIZE){
        // 获取完整头部信息
        ssize_t n = recv(fd, state->header_buf+state->header_received, HEADER_SIZE-state->header_received, 0);
        if(n <= 0){
            if(n == 0){
                printf("connect closed \n");
            }else{
                perror("recv fail");
            }
            return -1;
        }
        state->header_received+=(size_t)n;
        // 获得完整头部后, 进行头部封装. 方便后续消息体接收.
        if(state->header_received == HEADER_SIZE){
            uint32_t net_type;
            uint32_t net_len;
            memcpy(&net_type, state->header_buf, 4);
            memcpy(&net_len, state->header_buf+4, 4);
            state->header.type = ntohl(net_type);
            state->header.body_len = ntohl(net_len);
            // 如果消息体长度为0, 重置消息体接收结构体, 重新等待新的接收.
            if(state->header.body_len == 0){
                printf("empty message \n");
                state->header_received = 0;
                state->body_received = 0;
            }
        }
    }else{
        // 根据body_len 接收消息体数据
        uint32_t body_len = state->header.body_len;
        ssize_t nbytes = recv(fd, state->body_buf+state->body_received, body_len-state->body_received, 0);
        if(nbytes <=0){
            // 报错/连接完成 处理
            if(nbytes == 0){
                perror("server closed");
            }else{
                perror("recv fail");
            }
            return -1;
        }else{
            state->body_received += (size_t)nbytes;
            if(state->body_received == body_len){
                // 接收消息完成, 添加结尾符. 返回接收的字节数.
                state->body_buf[body_len] = '\0';
                return state->header_received + state->body_received;
            }
        }
    }
    return 0;
}