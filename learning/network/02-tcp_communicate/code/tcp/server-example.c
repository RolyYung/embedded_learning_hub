#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdbool.h>

int main(int argc, const char *argv[])
{
  // 创建流式套接字
  int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (listen_fd == -1)
  {
    perror("socket创建失败：");
    return -1;
  }

  // 定义配置服务器地址结构体
  struct sockaddr_in serverInfo;

  // 清空结构体
  memset(&serverInfo, 0, sizeof(serverInfo));

  // 初始化IPV4协议族
  serverInfo.sin_family = AF_INET;

  // 初始化端口号 （主机字节序->网络字节序）
  serverInfo.sin_port = htons(8888);

  // 初始化IP
  serverInfo.sin_addr.s_addr = inet_addr("192.168.26.128");

  // 绑定套接字与地址
  int ret = bind(listen_fd, (struct sockaddr *)&serverInfo, sizeof(serverInfo));

  if (ret == -1)
  {
    perror("绑定失败：");
    return -1;
  }

  // 设置监听状态
  int ret_1 = listen(listen_fd, 5);

  if (ret_1 == -1)
  {
    perror("监听失败：");
    return -1;
  }

  // 初始化客户端地址信息结构体
  struct sockaddr_in clientInfo;
  memset(&clientInfo, 0, sizeof(clientInfo));
  socklen_t clientInfo_len = sizeof(clientInfo);

  // 循环等待客户端的连接
  printf("服务器启动！！！\n");
  while (true)
  {
    int connect_fd = accept(listen_fd, (struct sockaddr *)&clientInfo, &clientInfo_len);
    if (connect_fd == -1)
    {
      perror("等待连接失败：");
      return -1;
    }

    printf("客户端【%s:%d】连接到服务器!!!\n", inet_ntoa(clientInfo.sin_addr), ntohs(clientInfo.sin_port));

    // 处理客户端通信（内部循环）
    while (true)
    {
      char buf[128] = {0};
      // int nbtyes = read(connect_fd, buf, sizeof(buf));
      int nbtyes = recv(connect_fd, buf, sizeof(buf), 0);

      if (nbtyes == -1)
      {
        perror("读取失败：");
        return -1;
      }

      if (nbtyes == 0)
      {
        printf("客户端断开连接\n");
        break;
      }

      printf("客户端【%s:%d】发来的数据：%s\n", inet_ntoa(clientInfo.sin_addr), ntohs(clientInfo.sin_port), buf);

      // 回显数据
      int nbtyes_send = send(connect_fd, buf, sizeof(buf), 0);

      if (nbtyes_send == -1)
      {
        perror("发送失败：");
        return -1;
      }
    }
  }
  return 0;
}