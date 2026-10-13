#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

#define PORT 8888
#define SERVER_IP "192.168.3.10"
#define MESSAGE_COUNT 20
#define MAX_MESSAGE_SIZE 1024

// 发送带长度前缀的消息
void send_message_with_length(int sock, const char *message)
{
  uint32_t len = strlen(message);
  // 转换为网络字节序
  uint32_t network_len = htonl(len);

  // 发送长度前缀
  send(sock, &network_len, sizeof(network_len), 0);
  // 发送消息内容
  send(sock, message, len, 0);
}

int main()
{
  int sock = 0;
  struct sockaddr_in serv_addr;

  // 创建socket文件描述符
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    printf("\nSocket creation error\n");
    return -1;
  }

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(PORT);

  // 将IPv4地址从点分十进制转换为二进制形式
  if (inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr) <= 0)
  {
    printf("\nInvalid address/ Address not supported\n");
    return -1;
  }

  // 连接到服务器
  if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
  {
    printf("\nConnection Failed\n");
    return -1;
  }

  printf("Connected to server\n");

  // 准备消息
  char message[MAX_MESSAGE_SIZE];

  // 连续发送多条消息
  for (int i = 0; i < MESSAGE_COUNT; i++)
  {
    // 在消息中包含序号以便识别
    sprintf(message, "Message %d from client", i + 1);
    send_message_with_length(sock, message);
    printf("Sent: %s\n", message);
    usleep(1000); // 1毫秒
  }

  // 关闭socket
  close(sock);
  return 0;
}