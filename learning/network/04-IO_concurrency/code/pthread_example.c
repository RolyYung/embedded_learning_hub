#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8888
#define SERVER_IP "192.168.136.130"
#define BUFFER_SIZE 128

// 自定义结构体 -> 封装客户端连接信息，用于在线程间传递
typedef struct MSG
{
  int acceptfd;                  // 客户端套接字描述符
  struct sockaddr_in clientaddr; // 客户端地址信息
} msg_t;

// 创建线程处理函数
void *deal_read_write(void *arg)
{
  msg_t msg = *(msg_t *)arg;
  char buf[BUFFER_SIZE] = {0};
  int nbytes = 0;
  printf("客户端【%s:%d】连接到了服务器\n", inet_ntoa(msg.clientaddr.sin_addr), ntohs(msg.clientaddr.sin_port));

  // 客户端数据接收与发送
  while (1)
  {
    nbytes = recv(msg.acceptfd, buf, BUFFER_SIZE, 0);
    if (nbytes == -1)
    {
      perror("读取客户端消息失败：");
    }
    else if (nbytes == 0)
    {
      printf("客户端【%s:%d】断开连接\n", inet_ntoa(msg.clientaddr.sin_addr), ntohs(msg.clientaddr.sin_port));
      break;
    }

    printf("客户端【%s:%d】发来数据：%s\n", inet_ntoa(msg.clientaddr.sin_addr), ntohs(msg.clientaddr.sin_port), buf);

    // 回显数据给客户端
    strcat(buf, "--服务器");
    if (send(msg.acceptfd, buf, BUFFER_SIZE, 0) == -1)
    {
      perror("回显数据失败：");
    }
  }
  close(msg.acceptfd);
  pthread_exit(NULL);
}

int main()
{
  // 创建套接字-配置服务器地址结构体
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1)
  {
    perror("创建套接字失败：");

    return -1;
  }

  struct sockaddr_in server_addr;
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
  socklen_t serveraddr_len = sizeof(server_addr);

  // 绑定、监听、处理客户端的连接
  if (bind(sockfd, (struct sockaddr *)&server_addr, serveraddr_len) == -1)
  {
    perror("绑定失败：");
    close(sockfd);
    return -1;
  }

  if (listen(sockfd, 5) == -1)
  {
    perror("监听失败：");
    close(sockfd);
    return -1;
  }

  struct sockaddr_in client_addr;
  socklen_t clientaddr_len = sizeof(client_addr);

  int acceptfd = 0;
  pthread_t pthread_id = 0;
  msg_t msg;
  int ret = 0;
  // 主线程：接受连接并创建子线程
  while (1)
  {
    if ((acceptfd = accept(sockfd, (struct sockaddr *)&client_addr, &clientaddr_len)) == -1)
    {
      perror("接受连接失败：");
      return -1;
    }

    msg.acceptfd = acceptfd;
    msg.clientaddr = client_addr;

    // 创建子线程
    ret = pthread_create(&pthread_id, NULL, deal_read_write, &msg);
    if (ret == -1)
    {
      printf("错误码：%d，错误信息：%s\n", ret, strerror(ret));
      close(sockfd);
      return -1;
    }

    ret = pthread_detach(pthread_id);

    if (ret == -1)
    {
      printf("错误码：%d，错误信息：%s\n", ret, strerror(ret));
      close(sockfd);
      return -1;
    }
  }

  close(sockfd);
  return 0;
}