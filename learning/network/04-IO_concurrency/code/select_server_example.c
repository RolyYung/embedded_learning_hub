#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/time.h>

#define PORT 8888
#define SERVER_IP "192.168.26.128"
#define BUFFER_SIZE 128

int main()
{

  // 创建监听套接字
  int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (listen_fd == -1)
  {
    perror("创建套接字失败：");
    return -1;
  }

  // 服务器地址配置
  struct sockaddr_in server_addr;
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
  socklen_t serveraddr_len = sizeof(server_addr);

  int ret = bind(listen_fd, (struct sockaddr *)&server_addr, serveraddr_len);
  if (ret == -1)
  {
    perror("绑定失败：");
    close(listen_fd);
    return -1;
  }

  // 监听
  if (listen(listen_fd, 10) == -1)
  {
    perror("监听失败：");
    close(listen_fd);
    return -1;
  }

  // seletc机制初始化
  // fd_set 文件描述符集合，用于’select()’监控
  // raedfd_save_set:保存所有监控的文件描述符
  // readfd_modify_set:每次调用select前的临时集合（select会修改这个集合）
  fd_set readfd_save_set, readfd_modify_set;
  FD_ZERO(&readfd_save_set);           // 清空集合
  FD_SET(listen_fd, &readfd_save_set); // 将监听套接字加入集合，监控新连接

  int max_fd = listen_fd;
  char buf[BUFFER_SIZE] = {0};

  printf("开启小型的select并发服务器\n");
  // 主循环与select调用
  while (1)
  {
    readfd_modify_set = readfd_save_set;
    int fds = select(max_fd + 1, &readfd_modify_set, NULL, NULL, NULL);
    if (fds == -1)
    {
      perror("select失败：");
      continue;
    }
    // 处理文件描述符事件
    int event_fd = 3;
    struct sockaddr_in client_addr;
    socklen_t clientaddr_len = sizeof(client_addr);

    for (event_fd; event_fd < max_fd + 1; event_fd++)
    {
      if (FD_ISSET(event_fd, &readfd_modify_set))
      {
        if (event_fd == listen_fd)
        {
          int acceptfd = accept(event_fd, (struct sockaddr *)&client_addr, &clientaddr_len);
          if (acceptfd == -1)
          {
            perror("accept失败：");
            continue;
          }
          FD_SET(acceptfd, &readfd_save_set);
          max_fd = max_fd > acceptfd ? max_fd : acceptfd;
          printf("客户端【%s：%d】连接服务器\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
        }
        else
        {
          // 处理客户端数据读写
          memset(buf, 0, sizeof(buf));
          int nbytes = recv(event_fd, buf, BUFFER_SIZE, 0);
          if (nbytes == -1)
          {
            perror("获取客户端信息失败：");
            continue;
          }
          else if (nbytes == 0)
          {
            printf("客户端【%s：%d】断开连接\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
            FD_CLR(event_fd, &readfd_save_set);
            close(event_fd);
            continue;
          }
          printf("客户端【%s：%d】发来数据：%s\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), buf);
          // 回显
          nbytes = send(event_fd, buf, BUFFER_SIZE, 0);
          if (nbytes == -1)
          {
            perror("回显失败：");
            continue;
          }
        }
      }
    }
  }

  return 0;
}
