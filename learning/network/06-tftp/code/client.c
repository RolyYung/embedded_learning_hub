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

void send_request(int sockfd, struct sockaddr_in *addr, char *filename, int is_write)
{
  uint8_t buf[516] = {0};
  buf[1] = is_write ? OP_WRQ : OP_RRQ;

  strcpy((char *)(buf + 2), filename);

  strcpy((char *)(buf + 2 + strlen(filename + 1)), "octet");

  int len = 2 + strlen(filename) + 1 + strlen("octet") + 1;
  sendto(sockfd, buf, len, 0, (struct sockaddr *)addr, sizeof(*addr));

  return;
}

void download_file(int sockfd, struct sockaddr_in *addr, char *remote_filename, char *local_path)
{
  struct stat st; // local path status

  // check local path is directory
  if (stat(local_path, &st) == 0 && S_ISDIR(st.st_mode))
  {
    char *filename = basename(remote_filename);
    char fullpath[256];
    snprintf(fullpath, sizeof(fullpath), "%s/%s", local_path, filename);
    local_path = fullpath;
  }

  printf("file will save to: %s \n", local_path);

  int fd = open(local_path, O_WRONLY | O_CREAT | O_TRUNC, 0664);
  if (fd < 0)
  {
    perror("open file fail");
    return;
  }

  uint8_t buf[BLOCK_SIZE + 4];
  uint16_t block = 1;

  while (1)
  {
    socklen_t len = sizeof(*addr);
    ssize_t nbytes = recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)addr, &len);

    if (nbytes < 4)
    {
      break;
    }

    if (buf[1] == OP_DATA && ntohs(*(uint16_t *)(buf + 2)) == block)
    {
      write(fd, buf + 4, nbytes - 4);
      uint8_t ack[4] = {0, OP_ACK, buf[2], buf[3]};
      sendto(sockfd, ack, 4, 0, (struct sockaddr *)addr, sizeof(*addr));

      if (nbytes < BLOCK_SIZE + 4)
      {
        break;
      }
      block++;
    }
    else if (buf[1] == OP_ERROR)
    {
      printf("error: %s \n", buf + 4);
      break;
    }
  }
  close(fd);
  return;
}

void upload_file(int sockfd, struct sockaddr_in *addr, char *local_path, char *remote_filname)
{
  int fd = open(local_path, O_RDONLY);
  if (fd == -1)
  {
    perror("open file fail");
    return;
  }

  uint8_t buf[BLOCK_SIZE + 4];
  uint16_t block = 1;
  ssize_t bytes_read;

  recvfrom(sockfd, buf, 4, 0, NULL, NULL);

  while ((bytes_read = read(fd, buf + 4, BLOCK_SIZE)) > 0)
  {
    buf[0] = 0;
    buf[1] = OP_DATA;
    buf[2] = block >> 8;
    buf[3] = block & 0xFF;

    sendto(sockfd, buf, bytes_read + 4, 0, (struct sockaddr *)addr, sizeof(*addr));

    recvfrom(sockfd, buf, 4, 0, NULL, NULL);
    block++;
  }

  close(fd);
}

int main(int argc, char *argv[])
{
  if (argc != 6)
  {
    // 6个参数 ： 程序名 + 5个参数
    printf("用法：%s <get|put> <本地路径> <远程文件名> <服务端ip地址> <端口号>\n", argv[0]);
    printf("示例：\n 下载：%s get /local/path remote.txt 192.168.1.100 69\n", argv[0]);
    return 1;
  }

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