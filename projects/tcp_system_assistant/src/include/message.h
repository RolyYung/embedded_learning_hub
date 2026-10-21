#ifndef MESSAGE_H
#define MESSAGE_H

#include <sys/types.h>
#include <stdio.h>
#include <stdint.h>

#define HEADER_SIZE 8

// 消息头结构体 1. 消息类型 2. 消息体长度.
typedef struct {
    uint32_t type;
    uint32_t body_len;
}message_header;

// 接收状态 1. 消息头部缓存区 2. 已接收到的头部字节数 3. 消息头部 4. 消息体缓存 5. 已接收的消息字节数
typedef struct {
    char header_buf[HEADER_SIZE];
    size_t header_received;

    message_header header;

    char body_buf[BUFSIZ + 1];
    size_t body_received;
} message_recv_state;

typedef struct {
    int fd;
    struct sockaddr_in addr;
    message_recv_state state;
}connection;

ssize_t send_msg(int fd, message_header header, const char * message);
ssize_t recv_msg(connection* peer);

#endif