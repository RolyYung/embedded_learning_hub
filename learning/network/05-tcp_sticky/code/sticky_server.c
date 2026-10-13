#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 4096
#define PORT 8888

int recv_message_with_length(int socket, char *buf, size_t b_size)
{
  unsigned int network_len;
  ssize_t bytes_recv = recv(socket, &network_len, sizeof(network_len), 0);
  if (bytes_recv == -1)
  {
    return -1;
  }

  uint32_t message_len = ntohl(network_len);

  if (message_len >= b_size)
  {
    printf("message_len >= buffer_size\n");
    return -1;
  }

  size_t total_bytes = 0;
  while (total_bytes < message_len)
  {
    bytes_recv = recv(socket, buf + total_bytes, message_len - total_bytes, 0);
    if (bytes_recv <= 0)
    {
      return -1;
    }
    total_bytes += bytes_recv;
  }
  buf[total_bytes] = '\0';
  return total_bytes;
}

int main()
{
  int ret;
  int server_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (server_fd == -1)
  {
    perror("create socket fail");
    return -1;
  }

  struct sockaddr_in server_addr;
  int opt = 1;
  ret = setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
  if (ret == -1)
  {
    perror("setsockopt fail");
    close(server_fd);
    return -1;
  }

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  ret = bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  if (ret == -1)
  {
    close(server_fd);
    perror("bind fail");
    return -1;
  }

  ret = listen(server_fd, 3);
  if (ret == -1)
  {
    close(server_fd);
    perror("listen fail");
    return -1;
  }

  struct sockaddr_in client_addr;
  socklen_t client_addr_len = sizeof(client_addr);

  int accept_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_addr_len);
  if (accept_fd == -1)
  {
    perror("accept fail");
    close(server_fd);
    return -1;
  }

  char buf[BUFFER_SIZE];
  while (1)
  {
    memset(buf, 0, BUFFER_SIZE);
    int ret_recv = recv_message_with_length(accept_fd, buf, BUFFER_SIZE);

    printf("ret_recv:%d\n", ret_recv);

    if (ret_recv <= 0)
    {
      printf("Client disconnected\n");
      break;
    }

    printf("recv msg: %s\n", buf);

    usleep(500000);
  }

  close(accept_fd);
  close(server_fd);

  return 0;
}