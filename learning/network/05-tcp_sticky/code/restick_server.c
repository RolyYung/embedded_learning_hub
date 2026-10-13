#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8888
#define BUFFER_SIZE 4096

// 接收带长度前缀的消息
int receive_message_with_length(int sock, char *buffer, size_t buffer_size)
{
  uint32_t network_len;
  // 先接收长度前缀
  ssize_t bytes_received = recv(sock, &network_len, sizeof(network_len), 0);
  if (bytes_received <= 0)
  {
    return -1; // 连接关闭或错误
  }

  // 转换为主机字节序
  uint32_t message_len = ntohl(network_len);

  // 确保缓冲区足够大
  if (message_len >= buffer_size)
  {
    printf("消息长度超出缓冲区大小\n");
    return -1;
  }

  // 接收消息内容
  size_t total_bytes = 0;
  while (total_bytes < message_len)
  {
    bytes_received = recv(sock, buffer + total_bytes, message_len - total_bytes, 0);
    if (bytes_received <= 0)
    {
      return -1; // 连接关闭或错误
    }
    total_bytes += bytes_received;
  }

  buffer[total_bytes] = '\0'; // 添加字符串结束符
  return total_bytes;
}

int main()
{
  int server_fd, new_socket;
  struct sockaddr_in address;
  int opt = 1;
  int addrlen = sizeof(address);
  char buffer[BUFFER_SIZE] = {0};

  // 创建socket文件描述符
  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
  {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }

  // 设置socket选项，允许地址重用
  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
  {
    perror("setsockopt");
    exit(EXIT_FAILURE);
  }

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(PORT);

  // 绑定socket到指定地址和端口
  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
  {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }

  // 监听连接
  if (listen(server_fd, 3) < 0)
  {
    perror("listen");
    exit(EXIT_FAILURE);
  }

  printf("服务端监听端口： %d...\n", PORT);

  // 接受客户端连接
  if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                           (socklen_t *)&addrlen)) < 0)
  {
    perror("accept");
    exit(EXIT_FAILURE);
  }

  printf("客户端连接\n");

  // 循环接收数据
  while (1)
  {
    memset(buffer, 0, BUFFER_SIZE);
    int bytes_received = receive_message_with_length(new_socket, buffer, BUFFER_SIZE);
    if (bytes_received <= 0)
    {
      printf("客户端断开连接\n");
      break;
    }
    printf("接收到客户端数据: %s\n", buffer);
  }

  // 关闭连接
  close(new_socket);
  close(server_fd);
  return 0;
}