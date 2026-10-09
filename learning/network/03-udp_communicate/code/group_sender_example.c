#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT 12345
#define MULTICAST_IP "239.255.0.1"

int main()
{
  // 创建UDP套接字
  int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd == -1)
  {
    perror("创建套接字失败：");
    return -1;
  }

  // 配置组播目标地址
  struct sockaddr_in multicast_addr;
  memset(&multicast_addr, 0, sizeof(multicast_addr));
  multicast_addr.sin_family = AF_INET;
  multicast_addr.sin_port = htons(PORT);
  multicast_addr.sin_addr.s_addr = inet_addr(MULTICAST_IP);

  // 设置组播包的TTL（TTL -> Time to Live）
  int ttl = 1; // TTL = 1表示数据包仅在局域网内进行传播
  int ret_set = setsockopt(sockfd, IPPROTO_IP, IP_MULTICAST_TTL, &ttl, sizeof(ttl));
  if (ret_set == -1)
  {
    perror("加入组播失败：");
    close(sockfd);
    return -1;
  }

  // 发送数据到组播组
  char message[] = "Hello! Multicast Group!";
  ssize_t ret_send = sendto(sockfd, message, strlen(message), 0, (struct sockaddr *)&multicast_addr, sizeof(multicast_addr));
  if (ret_send == -1)
  {
    perror("发送失败：");
  }
  else
  {
    printf("数据发送成功：%s:%zd bytes\n", message, ret_send);
  }

  return 0;
}