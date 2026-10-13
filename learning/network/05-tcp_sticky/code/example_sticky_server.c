#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8888
#define BUFFER_SIZE 4096

int recv_message_with_length(int socket, char *buf, size_t buffer_size)
{
  uint32_t network_len;
  ssize_t bytes_recv = recv(socket, &network_len, sizeof(network_len), 0);
  if (bytes_recv <= 0)
  {
    return -1;
  }

  uint32_t message_len = ntohl(network_len);

  if (message_len >= buffer_size)
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

  int server_fd, new_socket;
  struct sockaddr_in server_addr;
  int opt = 1;
  char buf[BUFFER_SIZE] = {0};
  socklen_t serveraddr_len = sizeof(server_addr);

  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
  {
    perror("socket failed");
    return -1;
  }

  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
  {
    perror("setsockopt");
    close(server_fd);
    return -1;
  }

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
  {
    perror("bind failed");
    close(server_fd);
    return -1;
  }

  if (listen(server_fd, 3) < 0)
  {
    perror("listen");
    close(server_fd);
    return -1;
  }

  if ((new_socket = accept(server_fd, (struct sockaddr *)&server_addr, &serveraddr_len)) < 0)
  {
    perror("accept");
    close(server_fd);
    return -1;
  }

  while (1)
  {
    memset(buf, 0, BUFFER_SIZE);
    int ret_recv = recv_message_with_length(new_socket, buf, BUFFER_SIZE);

    printf("ret_recv:%d\n", ret_recv);

    if (ret_recv <= 0)
    {
      printf("Client disconnected\n");
      break;
    }

    printf("recv msg: %s\n", buf);

    usleep(500000);
  }

  close(new_socket);
  close(server_fd);

  return 0;
}
