#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>
#include <libgen.h>
#include <sys/stat.h>
#include <sys/select.h>

#define BLOCK_SIZE 512 // TFTP数据块的大小

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

// 发送请求函数
void send_request(int sockfd, struct sockaddr_in *addr, char *filename, int is_write)
{
  // 初始化缓冲区
  uint8_t buf[516] = {0};
  buf[1] = is_write ? OP_WRQ : OP_RRQ; // 设置操作码 is_write :1表示上传WRQ; 0表示下载RRQ

  // 写入文件名(从第3个字节开始，第1、2字节为操作码)
  strcpy((char *)(buf + 2), filename);

  // 写入模式（octet表示二进制传输，从文件名后+1字节开始）
  strcpy((char *)(buf + 2 + strlen(filename) + 1), "octet");

  // 计算数据包长度：操作码（2） + 文件名（len） + 0 + 模式（len） + 0
  // 数据包格式：
  //  [0x00][0x01/0x02][filename][0x00][octet][0x00]
  int len = 2 + strlen(filename) + 1 + strlen("octet") + 1;
  sendto(sockfd, buf, len, 0, (struct sockaddr *)addr, sizeof(*addr)); // 发送请求包
}

// 文件下载函数
void download_file(int sockfd, struct sockaddr_in *addr, char *remote_filename, char *local_path)
{
  struct stat st; // 用于存储本地路径状态

  // 检查本地路径是否为目录
  if (stat(local_path, &st) == 0 && S_ISDIR(st.st_mode))
  {
    // 若是目录，使用远程文件名作为本地文件名
    char *filename = basename(remote_filename);
    char fullpath[256];
    snprintf(fullpath, sizeof(fullpath), "%s/%s", local_path, filename);
    local_path = fullpath; // 更新为完整的路径
  }

  printf("将文件保存到:%s\n", local_path);
  // 创建或者打开本地文件
  int fd = open(local_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
  if (fd < 0)
  {
    perror("open failed：");
    return;
  }

  uint8_t buf[BLOCK_SIZE + 4]; // 接收数据块的缓冲区大小
  uint16_t block = 1;          // 期待接收的块号从1开始

  while (1)
  {
    // 服务器地址长度
    socklen_t len = sizeof(*addr);
    // 接收服务器发送的数据块（包含服务器地址）
    ssize_t nbytes = recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)addr, &len);

    // 如果数据包过小，终止
    if (nbytes < 4)
    {
      break;
    }

    // 处理数据块 （OP_DATA）
    if (buf[1] == OP_DATA && ntohs(*(uint16_t *)(buf + 2)) == block)
    {
      write(fd, buf + 4, nbytes - 4); // 写入数据（跳过4个字节的包头）
      // 构建ACK包（直接使用接收到的块号字节）
      uint8_t ack[4] = {0, OP_ACK, buf[2], buf[3]};
      sendto(sockfd, ack, 4, 0, (struct sockaddr *)addr, sizeof(*addr)); // 发送ACK
      // 如果数据块不足512+4字节， 视为最后一块数据包块（nbytes < 516,数据部分为 nbytes -4 < 512）
      if (nbytes < BLOCK_SIZE + 4)
      {
        break;
      }
      block++;
    }
    else if (buf[1] == OP_ERROR)
    {
      // 处理错误包
      printf("错误：%s\n", buf + 4); // 打印错误消息
      break;
    }
  }
  // 关闭文件
  close(fd);
}

void upload_file(int sockfd, struct sockaddr_in *addr, char *local_path, char *remote_filename)
{
  // 以只读模式打开本地文件
  int fd = open(local_path, O_RDONLY);
  if (fd < 0)
  {
    perror("open failed：");
    return;
  }

  // 发送数据块缓冲区
  uint8_t buf[BLOCK_SIZE + 4];
  uint16_t block = 1;
  ssize_t bytes_read;

  // 等待服务器响应WRQ的初始ACK，块号0
  recvfrom(sockfd, buf, 4, 0, NULL, NULL); // 阻塞等待ACK0

  while ((bytes_read = read(fd, buf + 4, BLOCK_SIZE)) > 0)
  {
    // 构建DATA包头
    buf[0] = 0;
    buf[1] = OP_DATA;
    buf[2] = block >> 8;
    buf[3] = block & 0xFF;

    // 发送数据块
    sendto(sockfd, buf, bytes_read + 4, 0, (struct sockaddr *)addr, sizeof(*addr));

    // 等待服务器响应
    recvfrom(sockfd, buf, 4, 0, NULL, NULL);

    block++;
  }

  close(fd);
}

// 文件传输逻辑
// 下载
// 1、客户端“发送RRQ(操作码1 + 文件名 + octet) 到服务器中”
// 2、服务器“解析RRQ，检查文件存在性”
// 存在：分块发送DATA包（块号从1开始），每发送一块等待ACK回应
// 不存在：返回ERROR包（操作码5 + 错误码1）
// 3、客户端“接收DATA包，验证块号后写入文件， 返回对应的ACK”
// 4、服务器“发送空DATA包（4字节）表示结束，客户端发送最后一个ACK”

// 上传
// 1、客户端“发送WRQ”
// 2、服务器“解析WRQ，创建文件并且返回ACK0”
// 3、客户端“接收ACK0，分块发送DATA包（块号从1开始），每发送一块等待ACK”
// 4、服务器“接收DATA”包，验证块号写入文件，然后ACK
// 5、客户端“发送完所有数据（最后一块 < 512字节），服务器接收后结束”

int main(int argc, char *argv[])
{

  if (argc != 6)
  {
    // 6个参数 ： 程序名 + 5个参数
    printf("用法：%s <get|put> <本地路径> <远程文件名> <服务端ip地址> <端口号>\n", argv[0]);
    printf("示例：\n 下载：%s get /local/path remote.txt 192.168.1.100 69\n", argv[0]);
    return 1;
  }

  // 创建UDPsocket
  int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(atoi(argv[5]));
  server_addr.sin_addr.s_addr = inet_addr(argv[4]);

  // 打印操作信息
  printf("操作：%s\n", argv[1]);
  printf("本地路径：%s\n", argv[2]);
  printf("远程文件：%s\n", argv[3]);

  // 根据操作类型执行上传或者下载
  if (strcmp(argv[1], "get") == 0)
  {
    // 下载（RRQ）
    // 发送读请求
    send_request(sockfd, &server_addr, argv[3], 0);

    // 接收数据
    download_file(sockfd, &server_addr, argv[3], argv[2]);
  }
  else if (strcmp(argv[1], "put") == 0)
  {
    // 上传 (WRQ)
    // 发送写请求
    send_request(sockfd, &server_addr, argv[3], 1);

    // 发送数据
    upload_file(sockfd, &server_addr, argv[2], argv[3]);
  }
  else
  {
    printf("无效命令\n");
  }

  close(sockfd);
  return 0;
}