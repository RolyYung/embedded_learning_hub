#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 9999
#define BROADCAST_IP "255.255.255.255"

int main()
{

  // 创建UDP套接字
  int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd == -1)
  {
    perror("套接字创建失败：");
    return -1;
  }

  // 启动广播权限
  int opt = 1;
  int ret_set = setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &opt, sizeof(opt));
  if (ret_set == -1)
  {
    perror("启动广播失败：");
    close(sockfd);
    return -1;
  }

  // 配置广播目标地址
  struct sockaddr_in broadcast_addr;
  memset(&broadcast_addr, 0, sizeof(broadcast_addr));
  broadcast_addr.sin_family = AF_INET;
  broadcast_addr.sin_port = htons(PORT);
  broadcast_addr.sin_addr.s_addr = inet_addr(BROADCAST_IP);

  // 发送广播数据
  char message[] = "Hello!Broadcast!";
  ssize_t ret_send = sendto(sockfd, message, strlen(message), 0, (struct sockaddr *)&broadcast_addr, sizeof(broadcast_addr));
  if (ret_send == -1)
  {
    perror("发送失败：");
  }
  else
  {
    printf("广播发送成功：%s:%zd bytes\n", message, ret_send);
  }
  close(sockfd);

  return 0;
}