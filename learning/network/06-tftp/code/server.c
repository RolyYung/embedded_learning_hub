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
  // read request
  OP_RRQ = 1,
  // write request
  OP_WRQ = 2,
  // data bolck
  OP_DATA = 3,
  // acknowlege
  OP_ACK = 4,
  // error
  OP_ERROR = 5
} tftp_opcode;

void ensure_dir_exists(const char *path)
{
  struct stat st = {0};
  if (stat(path, &st) == -1)
  {
    if (mkdir(path, 0755) == -1)
    {
      perror("create dirctory fail");
    }
    else
    {
      printf("create dirctory: %s\n", path);
    }
  }

  return;
};

void send_ack(int socket, struct sockaddr_in *addr, uint16_t block)
{
  uint8_t ack[4] = {0, OP_ACK, block >> 8, block & 0xFF}; // 构建ACK包
  // 包头结构 ： 2字节操作码（0x0004）+ 2字节块号（大端序）
  sendto(socket, ack, 4, 0, (struct sockaddr *)addr, sizeof(*addr)); // 发送UDP包
}

void handle_download(int socket, struct sockaddr_in *client_addr, char *filename)
{
  printf("trying to download(%s) ... \n", filename);

  char *fname_copy = strdup(filename);
  char *pure_filename = basename(fname_copy);

  char fullpath[256];
  snprintf(fullpath, sizeof(fullpath), "%s/%s", BASE_DIR, pure_filename);
  free(fname_copy);
  printf("server file path: %s \n", fullpath);

  int fd = open(fullpath, O_RDONLY);
  if (fd < 0)
  {
    perror("open file fail");
    uint8_t err[5 + sizeof("File not found")] = {0, OP_ERROR, 1};
    strcpy((char *)err + 4, "File not found");

    sendto(socket, err, sizeof(err), 0, (struct sockaddr *)client_addr, sizeof(*client_addr));
    return;
  }

  uint8_t buf[BLOCK_SIZE + 4];
  uint16_t block = 1;
  ssize_t bytes_read;
  while ((bytes_read = read(fd, buf + 4, BLOCK_SIZE)) > 0)
  {
    buf[0] = 0;
    buf[1] = OP_DATA;
    buf[2] = block >> 8;
    buf[3] = block & 0xFF;
    printf("block: %d, size: %zd bytes\n", block, bytes_read);

    // send data block
    sendto(socket, buf, bytes_read + 4, 0, (struct sockaddr *)client_addr, sizeof(*client_addr));

    fd_set read_fds;
    FD_ZERO(&read_fds);
    FD_SET(socket, &read_fds);

    struct timeval timeout = {5, 0};

    int ret = select(socket + 1, &read_fds, NULL, NULL, &timeout);
    if (ret <= 0)
    {
      printf("waiting ack overtime, re-send data%d \n", block);
      continue;
    }

    ssize_t ack_size = recvfrom(socket, buf, 4, 0, NULL, NULL);

    if (ack_size < 4 || buf[1] != OP_ACK || ntohs(*(uint16_t *)(buf + 2)) != block)
    {
      printf("invalid ack, re-send data: %d\n", block);
      continue;
    }

    printf("receive block %d ACK\n", block);
    block++;
  }

  if (bytes_read == 0)
  {
    buf[0] = 0;
    buf[1] = OP_DATA;
    buf[2] = block >> 8;
    buf[3] = block & 0xFF;
    sendto(socket, buf, 4, 0, (struct sockaddr *)client_addr, sizeof(*client_addr)); // empty data
    printf("send end data\n");
    recvfrom(socket, buf, 4, 0, NULL, NULL);
  }
  close(socket);
  printf("send data done \n");
  return;
}

void handle_upload(int socket, struct sockaddr_in *client_addr, char *filename)
{
  printf("trying upload file(%s)... \n", filename);
  char *fname_copy = strdup(filename);
  char *pure_filename = basename(fname_copy);

  char fullpath[256];
  snprintf(fullpath, sizeof(fullpath), "%s/%s", BASE_DIR, pure_filename);
  free(fname_copy);

  char *dir = strdup(fullpath);
  ensure_dir_exists(dirname(dir));
  free(dir);

  int fd = open(fullpath, O_WRONLY | O_TRUNC | O_CREAT, 0644);
  if (fd < 0)
  {
    perror("create file fail \n");
    return;
  }

  uint8_t buf[BLOCK_SIZE + 4];
  uint16_t block = 1;

  send_ack(socket, client_addr, 0);

  while (1)
  {
    socklen_t len = sizeof(*client_addr);

    ssize_t nbytes = recvfrom(socket, buf, sizeof(buf), 0, (struct sockaddr *)client_addr, &len);
    if (nbytes < 4)
    {
      printf("receive data fail\n");
      break;
    }

    if (buf[1] == OP_DATA && ntohs(*(uint16_t *)(buf + 2)) == block)
    {
      ssize_t data_size = nbytes - 4;
      printf("receive block %d, size: %zd bytes", block, data_size);

      write(fd, buf + 4, data_size);
      send_ack(socket, client_addr, block);

      if (data_size < BLOCK_SIZE)
      {
        printf("receive last block, upload done \n");
        break;
      }

      block++;
    }
    else if (buf[1] == OP_ERROR)
    {
      printf("error: %s \n", buf + 4);
      break;
    }
    else
    {
      printf("receive other block: option code: %d, block num: %d\n", ntohs(*(uint16_t *)(buf + 2)), block);
    }
  }
  close(socket);

  return;
}

int main()
{
  int ret;
  printf("storage directory: %s \n", BASE_DIR);
  // target storage dirctory, if don't exist create the directory
  ensure_dir_exists(BASE_DIR);

  int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

  ret = bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  if (ret == -1)
  {
    perror("bind fail");
    close(sockfd);
    return -1;
  }
  printf("tftp server is running...(server IP: %s, port: %d) \n", SERVER_IP, PORT);
  printf("waiting client connecting");

  while (1)
  {
    uint8_t buf[516];

    struct sockaddr_in client_addr = {0};
    socklen_t len = sizeof(client_addr);

    ssize_t nbytes = recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&client_addr, &len);
    if (nbytes > 2)
    {
      char *filename = (char *)(buf + 2);
      char *mode = filename + strlen(filename) + 1;
      char client_ip[INET_ADDRSTRLEN];

      inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, INET_ADDRSTRLEN);
      printf("收到了来自客户端%s:%d的请求\n", client_ip, ntohs(client_addr.sin_port));

      if (buf[1] == OP_RRQ)
      {
        printf("donwload req: %s \n", filename);
        handle_download(sockfd, &client_addr, filename);
        printf("download done \n");
      }
      else if (buf[2] == OP_WRQ)
      {
        printf("upload request: %s\n", filename);
        handle_upload(sockfd, &client_addr, filename);
        printf("upload done \n");
      }
      else
      {
        printf("other option code: %d\n", buf[1]);
      }
    }
  }
  return 0;
}