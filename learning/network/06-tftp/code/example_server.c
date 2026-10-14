#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <libgen.h>
#include <sys/stat.h>
#include <sys/select.h>

#define PORT 3456 // 服务器监听端口
#define SERVER_IP "127.0.0.1"
#define BLOCK_SIZE 512                                      // TFTP数据块的大小
#define BASE_DIR "/Users/aaayun/Desktop/wrong/embeded/tftp" // 文件存储根目录

typedef enum
{
  // 读请求
  OP_RRQ = 1,
  // 写请求
  OP_WRQ = 2,
  // 数据块
  OP_DATA = 3,
  // 确认包
  OP_ACK = 4,
  // 错误包
  OP_ERROR = 5
} tftp_opcode;

// 目录创建函数
void ensure_dir_exists(const char *path)
{

  // 用于存储文件/目录状态
  struct stat st = {0};
  if (stat(path, &st) == -1)
  {
    // 0755 -- rwxr-xr-x (所有者可读可写可执行，其他用户可读可执行)
    if (mkdir(path, 0755) == -1)
    {
      perror("创建目录失败：");
    }
    else
    {
      printf("创建目录：%s\n", path);
    }
  }
}

void send_ack(int socket, struct sockaddr_in *addr, uint16_t block)
{
  uint8_t ack[4] = {0, OP_ACK, block >> 8, block & 0xFF}; // 构建ACK包
  // 包头结构 ： 2字节操作码（0x0004）+ 2字节块号（大端序）
  sendto(socket, ack, 4, 0, (struct sockaddr *)addr, sizeof(*addr)); // 发送UDP包
}

// 下载函数
void handle_download(int socket, struct sockaddr_in *client_addr, char *filename)
{
  printf("尝试下载文件（%s）...\n", filename);

  // 提纯文件名（过滤路径，防止../遍历）
  char *fname_copy = strdup(filename);        // 复制文件名（basename会修改原字符串）
  char *pure_filename = basename(fname_copy); // 提纯文件名（"/a/b.txt" -> "b.txt"）

  // 构建存储路径（BASE_DIR + 纯文件名）
  char fullpath[256];
  snprintf(fullpath, sizeof(fullpath), "%s/%s", BASE_DIR, pure_filename); // 防止缓冲区溢出
  free(fname_copy);                                                       // 释放临时内存

  printf("服务器文件路径：%s\n", fullpath);

  int fd = open(fullpath, O_RDONLY); // 以只读模式打开文件
  if (fd < 0)
  {
    // 打开失败
    perror("文件打开失败：");
    // 构造错误包：操作5 + 错误码1（文件未找到）+ 消息
    uint8_t err[5 + sizeof("File not found")] = {0, OP_ERROR, 1};
    strcpy((char *)err + 4, "File not found");                                                 // 错误消息是从第五个字节开始
    sendto(socket, err, sizeof(err), 0, (struct sockaddr *)client_addr, sizeof(*client_addr)); // 发送错误包
    return;
  }

  uint8_t buf[BLOCK_SIZE + 4]; // 缓冲区：4个字节包头 + 512字节数据
  uint16_t block = 1;          // 块号从1开始
  ssize_t bytes_read;          // 实际读取的字节数
  while ((bytes_read = read(fd, buf + 4, BLOCK_SIZE)) > 0)
  {
    // 读取文件数据
    // 构建DATA包头
    buf[0] = 0;            // 操作码高位（OP_DATA为3， 0x0003）
    buf[1] = OP_DATA;      // 操作码低位
    buf[2] = block >> 8;   // 块号高位 （大端序）
    buf[3] = block & 0xFF; // 块号低位

    printf("发送块：%d，大小：%zd 字节\n", block, bytes_read);

    // 发送数据块
    sendto(socket, buf, bytes_read + 4, 0, (struct sockaddr *)client_addr, sizeof(*client_addr));

    // 设置5秒超时等待ACK
    fd_set read_fds;
    FD_ZERO(&read_fds);              // 清空文件描述符集合
    FD_SET(socket, &read_fds);       // 添加socket到集合中
    struct timeval timeout = {5, 0}; // 设置5秒超时

    int ret = select(socket + 1, &read_fds, NULL, NULL, &timeout); // 等待可读事件
    if (ret <= 0)                                                  // 超时（ret == 0）或者 错误（ret == -1）
    {
      printf("等待ACK超时，重发包%d\n", block);
      continue;
    }

    // 接收ACK包 4字节
    ssize_t ack_size = recvfrom(socket, buf, 4, 0, NULL, NULL);
    // 验证ACK有效性 ： 操作码是否为OP_ACK,块号是否匹配
    if (ack_size < 4 || buf[1] != OP_ACK || ntohs(*(uint16_t *)(buf + 2)) != block)
    {
      printf("无效的ACK，重发包%d\n", block);
      continue;
    }

    printf("收到块%d的ACK\n", block);
    block++;
  }

  // 发送结束包（空数据块，4字节包头，块号为最后一块 + 1）
  if (bytes_read == 0)
  {
    // 文件读取完毕
    buf[0] = 0;
    buf[1] = OP_DATA;
    buf[2] = block >> 8;
    buf[3] = block & 0xFF;
    sendto(socket, buf, 4, 0, (struct sockaddr *)client_addr, sizeof(*client_addr)); // 空包
    printf("发送结束包\n");

    // 等待客户端回应对结束包的ACK
    recvfrom(socket, buf, 4, 0, NULL, NULL);
  }
  close(socket);
  printf("文件发送完成\n");
}

// 上传处理函数
void handle_upload(int socket, struct sockaddr_in *client_addr, char *filename)
{
  printf("尝试上传文件(%s)...\n", filename);
  // 提纯文件名（过滤路径，防止../遍历）
  char *fname_copy = strdup(filename);        // 复制文件名（basename会修改原字符串）
  char *pure_filename = basename(fname_copy); // 提纯文件名（"/a/b.txt" -> "b.txt"）

  // 构建存储路径（BASE_DIR + 纯文件名）
  char fullpath[256];
  snprintf(fullpath, sizeof(fullpath), "%s/%s", BASE_DIR, pure_filename); // 防止缓冲区溢出
  free(fname_copy);                                                       // 释放临时内存

  // 创建父目录（a/b/c.txt -> 创建a/b）
  char *dir = strdup(fullpath);
  ensure_dir_exists(dirname(dir)); // dirname获取目录部分
  free(dir);

  // 创建文件
  int fd = open(fullpath, O_WRONLY | O_TRUNC | O_CREAT, 0644);
  if (fd < 0)
  {
    perror("创建文件失败\n");
    return;
  }

  uint8_t buf[BLOCK_SIZE + 4]; // 接收数据块的缓冲区
  uint16_t block = 1;

  send_ack(socket, client_addr, 0); // 响应WRQ，发送初始ACK（块号0，表示准备好接收）
  while (1)
  {
    socklen_t len = sizeof(*client_addr);

    // 接收客户端发送的数据包
    ssize_t nbytes = recvfrom(socket, buf, sizeof(buf), 0, (struct sockaddr *)client_addr, &len);
    if (nbytes < 4) // 数据包过小
    {
      printf("接收数据包失败\n");
      break;
    }

    // 处理数据块
    if (buf[1] == OP_DATA && ntohs(*(uint16_t *)(buf + 2)) == block)
    {
      ssize_t data_size = nbytes - 4; // 数据部分长度 = 总长度 - 包头长度
      printf("收到块%d，大小 %zd 字节\n", block, data_size);

      // 写入文件
      write(fd, buf + 4, data_size);
      send_ack(socket, client_addr, block);

      // 如果数据块不足512字节 视为最后一块
      if (data_size < BLOCK_SIZE)
      {
        printf("收到最后一块，上传完成\n");
        break;
      }

      block++;
    }
    else if (buf[1] == OP_ERROR)
    {
      // 处理客户端的错误包
      printf("错误：%s\n", buf + 4);
      break;
    }
    else
    {
      printf("收到意外包：操作码：%d，块号%d\n", buf[1], ntohs(*(uint16_t *)(buf + 2)));
    }
  }
  close(socket);
}

int main()
{

  // 确保文件存储根目录存在
  printf("基础存储目录：%s\n", BASE_DIR);

  // 调用目录创建函数
  ensure_dir_exists(BASE_DIR);

  // 创建UDP socket
  int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

  // 绑定socket到指定端口与地址
  int ret_bind = bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  if (ret_bind == -1)
  {
    perror("绑定失败：");
    close(sockfd);
    return -1;
  }

  printf("TFTP服务器运行中...（服务器IP:%s, 端口号%d）\n", SERVER_IP, PORT);
  printf("等待客户端连接...\n");

  // 开启主循环，持续等待处理客户端请求
  while (1)
  {
    // 接受缓冲区（最大的数据包512字节数据 + 4字节包头）
    uint8_t buf[516];

    // 客户端地址结构体
    struct sockaddr_in client_addr;
    socklen_t len = sizeof(client_addr); // 地址长度初始化

    // 接受客户端请求
    ssize_t nbytes = recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&client_addr, &len);

    if (nbytes > 2)
    {                                     // 返回字节数至少包含了操作码（2字节） +  文件名（1个字节的）
      char *filename = (char *)(buf + 2); // 文件名是从第三个字节开始的

      char *mode = filename + strlen(filename) + 1; // 固定模式字段（“octet”）
      char client_ip[INET_ADDRSTRLEN];              // 存储客户端的ip字符串

      // 将客户端ip转换为字符串
      inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, INET_ADDRSTRLEN);
      printf("收到了来自客户端%s:%d的请求\n", client_ip, ntohs(client_addr.sin_port));

      // 判断操作码，并且去调用对应的处理函数
      if (buf[1] == OP_RRQ) // 下载请求
      {
        printf("下载请求：%s\n", filename);
        // 调用处理下载函数
        handle_download(sockfd, &client_addr, filename);
        printf("下载完成\n");
      }
      else if (buf[1] == OP_WRQ) // 上传请求
      {
        printf("上传请求：%s\n", filename);
        // 调用处理上传函数
        handle_upload(sockfd, &client_addr, filename);
        printf("上传完成\n");
      }
      else
      {
        printf("其他操作码：%d\n", buf[1]);
      }
    }
  }

  close(sockfd);
  return 0;
}