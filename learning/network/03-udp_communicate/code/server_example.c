#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8888
#define BUFFER_SIZE 1024

int main()
{
  // 创建UDP套接字
  int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd == -1)
  {
    perror("Socket创建失败：");
    return -1;
  }

  // 配置服务器地址结构体
  struct sockaddr_in serverInfo;

  memset(&serverInfo, 0, sizeof(serverInfo));
  serverInfo.sin_family = AF_INET;
  serverInfo.sin_port = htons(PORT);
  serverInfo.sin_addr.s_addr = INADDR_ANY; // 这里表示要监听所有网卡

  // 绑定套接字到地址和端口
  int ret_bind = bind(sockfd, (struct sockaddr *)&serverInfo, sizeof(serverInfo));
  if (ret_bind == -1)
  {
    perror("绑定失败：");
    close(sockfd);
    return -1;
  }

  printf("UDP服务器已启动， 监听端口：%d \n", PORT);

  // 循环接收并且回显数据
  while (1)
  {
    char buf[BUFFER_SIZE] = {0};
    struct sockaddr_in clientInfo;
    socklen_t clientInfo_len = sizeof(clientInfo);

    // 接收数据
    ssize_t recv_len = recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&clientInfo, &clientInfo_len);
    if (recv_len == -1)
    {
      perror("接收数据失败：");
      continue; // 继续等待下一个数据包
    }

    // 打印客户端信息
    printf("收到来自%s：%d的信息：%s\n", inet_ntoa(clientInfo.sin_addr), ntohs(clientInfo.sin_port), buf);

    // 回显数据
    ssize_t send_len = sendto(sockfd, buf, recv_len, 0, (struct sockaddr *)&clientInfo, clientInfo_len);
    if (send_len == -1)
    {
      perror("回显数据失败：");
    }
  }
  close(sockfd);
  return 0;
}