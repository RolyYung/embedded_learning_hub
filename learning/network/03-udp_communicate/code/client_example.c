#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 8888
#define SERVER_IP "192.168.26.128"
#define BUFFER_SIZE 1024

int main()
{

  // 创建套接字
  int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd == -1)
  {
    perror("创建套接字失败：");
    return -1;
  }

  // 配置服务器地址信息
  struct sockaddr_in serverInfo;
  memset(&serverInfo, 0, sizeof(serverInfo));
  serverInfo.sin_family = AF_INET;
  serverInfo.sin_port = htons(PORT);
  serverInfo.sin_addr.s_addr = inet_addr(SERVER_IP);

  // 发送数据
  char message[] = "Hello,UDP Server!";
  ssize_t ret_sendto = sendto(sockfd, message, strlen(message), 0, (struct sockaddr *)&serverInfo, sizeof(serverInfo));
  if (ret_sendto == -1)
  {
    perror("发送失败：");
    close(sockfd);
    return -1;
  }

  printf("已经发送消息：%s\n", message);

  // 接收回显消息
  char buf[BUFFER_SIZE] = {0};
  struct sockaddr_in fromInfo;
  socklen_t fromInfo_len = sizeof(fromInfo);
  ssize_t ret_recvfrom = recvfrom(sockfd, buf, sizeof(buf) - 1, 0, (struct sockaddr *)&fromInfo, &fromInfo_len);
  if (ret_recvfrom == -1)
  {
    perror("接收失败：");
  }
  else
  {
    buf[ret_recvfrom] = '\0';
    printf("服务器回显：%s\n", buf);
  }

  close(sockfd);

  return 0;
}