#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

#define PORT 8888
#define SERVER_IP "192.168.26.128"
#define BUFFER_SIZE 128

// 信号处理函数
void sig_func(int signum)
{
  wait(NULL); // 处理SIGUSR1信号，回收子进程资源，避免僵尸进程
}

int main()
{

  // 套接字创建与服务器配置
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1)
  {
    perror("套接字创建失败：");
    return -1;
  }

  struct sockaddr_in server_addr;
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
  socklen_t serveraddr_len = sizeof(server_addr);

  // 绑定、监听、信号注册
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
  pid_t pid = 0;
  int ret = 0;

  signal(SIGUSR1, sig_func);

  // 主循环：接受连接并且创建子进程
  while (1)
  {
    acceptfd = accept(sockfd, (struct sockaddr *)&client_addr, &clientaddr_len);
    if (acceptfd == -1)
    {
      perror("接受连接失败：");
      close(sockfd);
    }

    pid = fork();
    if (pid == -1)
    {
      perror("创建子进程失败：");
      close(acceptfd);
      break;
    }
    else if (pid == 0)
    {
      // 处理客户端通信
      char buf[BUFFER_SIZE] = {0};
      int nbytes = 0;
      printf("客户端【%s：%d】连接到服务器\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

      // 接收数据
      nbytes = recv(acceptfd, buf, BUFFER_SIZE, 0);
      if (nbytes == -1)
      {
        printf("接收失败：");
      }
      else if (nbytes == 0)
      {
        printf("客户端【%s：%d】断开连接\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
        break;
      }

      printf("客户端【%s：%d】发来数据：%s\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), buf);

      strcat(buf, "--来自服务端");
      // 回显
      if (send(acceptfd, buf, BUFFER_SIZE, 0) == -1)
      {
        perror("回显失败：");
      }
      close(acceptfd);
      kill(getpid(), SIGUSR1);
      exit(0);
    }
    else if (pid > 0)
    {
      close(acceptfd);
    }
  }

  close(sockfd);
  return 0;
}