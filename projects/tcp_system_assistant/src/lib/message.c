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