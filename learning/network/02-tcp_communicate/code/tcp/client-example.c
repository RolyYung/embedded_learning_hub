#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

int main(int argc, const char *argv[])
{

  // 创建流式套接字
  int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

  if (socket_fd == -1)
  {
    perror("创建套接字失败：");

    return -1;
  }

  // 配置服务器地址信息
  struct sockaddr_in serverInfo = {0};

  // IPV协议族
  serverInfo.sin_family = AF_INET;

  // 端口号（主机->网络序）
  serverInfo.sin_port = htons(8888);

  // IP
  serverInfo.sin_addr.s_addr = inet_addr("192.168.26.128");

  // 连接服务器
  int ret = connect(socket_fd, (const struct sockaddr *)&serverInfo, sizeof(serverInfo));

  if (ret == -1)
  {
    perror("连接错误：");

    return -1;
  }

  // 数据收发循环
  char buf[128] = {0};
  while (true)
  {
    // 发送数据
    memset(buf, 0, sizeof(buf));

    // 从键盘中读取输入
    fgets(buf, sizeof(buf), stdin);

    int nbytes = send(socket_fd, buf, sizeof(buf), 0);

    if (nbytes == -1)
    {
      perror("发送失败：");
      return -1;
    }

    // 接收数据
    memset(buf, 0, sizeof(buf));
    int nbytes_recv = recv(socket_fd, buf, sizeof(buf), 0);

    if (nbytes_recv == -1)
    {
      perror("读取失败：");
      return -1;
    }
    else if (nbytes_recv == 0)
    {
      printf("服务端关闭连接，退出程序\n");

      return 0;
    }
    printf("服务器发来的数据：%s \n", buf);
  }

  return 0;
}