#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#define PORT 8888
#define BUFFER_SIZE 1024

int main(int argc, const char *argv[])
{
  int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);

  if (sock_fd == -1)
  {
    perror("create socket fail:");
    return -1;
  }

  // init server addr struct
  struct sockaddr_in serverInfo = {0};

  serverInfo.sin_family = AF_INET;
  serverInfo.sin_addr.s_addr = INADDR_ANY;
  serverInfo.sin_port = htons(PORT);

  int ret_bind = bind(sock_fd, (struct sockaddr *)&serverInfo, sizeof(serverInfo));
  if (ret_bind == -1)
  {
    perror("bind socket fail:");
    close(sock_fd);
    return -1;
  }
  printf("UDP server starting! listen port: %d", PORT);

  // loop recive data & echo data
  while (1)
  {
    char buf[BUFFER_SIZE] = {0};
    struct sockaddr_in clientInfo;
    socklen_t clientInfo_len = sizeof(clientInfo);
    ssize_t recv_len = recvfrom(sock_fd, buf, sizeof(buf), 0, (struct sockaddr *)&clientInfo, &clientInfo_len);

    if (recv_len == -1)
    {
      perror("recive data fail:");
      continue;
    }

    // print client info
    printf("recive from %s:%d data: %s \n", inet_ntoa(clientInfo.sin_addr), ntohs(clientInfo.sin_port), buf);

    // echo data
    ssize_t send_len = sendto(sock_fd, buf, recv_len, 0, (struct sockaddr *)&clientInfo, clientInfo_len);

    if (send_len == -1)
    {
      perror("echo data fail:");
    }
  }
  close(sock_fd);

  return 0;
}