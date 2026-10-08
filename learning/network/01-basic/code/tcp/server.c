#include <sys/socket.h>
#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8888

int main(int argc, const char *argv[])
{
  // create socket, IPv4, TCP, IP协议
  int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
  // -- create error tips
  if (listen_fd == -1)
  {
    perror("create socket fail:");
    return -1;
  }

  // init struct sockaddr_in
  struct sockaddr_in serverInfo;
  memset(&serverInfo, 0, sizeof(serverInfo));

  serverInfo.sin_family = AF_INET;
  serverInfo.sin_port = htons(PORT);
  serverInfo.sin_addr.s_addr = inet_addr("192.168.3.15");

  // bind (socket & addr)
  int ret_bind = bind(listen_fd, (struct sockaddr *)&serverInfo, sizeof(serverInfo));

  if (ret_bind == -1)
  {
    perror("bind fail:");
    close(listen_fd);
    return -1;
  }

  // set listen
  int ret_listen = listen(listen_fd, 5);

  if (ret_listen == -1)
  {
    perror("listen fail:");
    return -1;
  }

  // init client address info
  struct sockaddr_in clientInfo;
  memset(&clientInfo, 0, sizeof(clientInfo));

  socklen_t clientInfo_len = sizeof(clientInfo);

  // wait client connect
  printf("server start!!! \n");
  while (1)
  {
    int connect_fd = accept(listen_fd, (struct sockaddr *)&clientInfo, &clientInfo_len);
    if (connect_fd == -1)
    {
      perror("wait connect fail:");
      return -1;
    }

    printf("client [%s:%d] connect the server!!! \n", inet_ntoa(clientInfo.sin_addr), ntohs(clientInfo.sin_port));

    // handler client communication
    while (1)
    {
      char buf[128] = {0};
      int nbytes = recv(connect_fd, buf, sizeof(buf), 0);
    }
  }
  return 0;
}