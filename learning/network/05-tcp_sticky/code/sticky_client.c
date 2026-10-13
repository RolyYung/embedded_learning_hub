#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>

#define PORT 8888
#define SERVER_IP "127.0.0.1"
#define MESSAGE_COUNT 20

void sned_message_with_length(int socket, const char *message)
{
  uint32_t len = strlen(message);
  uint32_t network_len = htonl(len);

  send(socket, &network_len, sizeof(network_len), 0);
  send(socket, message, len, 0);
  return;
}

int main()
{
  int ret;

  int client_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (client_fd == -1)
  {
    perror("socket fail");
    return -1;
  }

  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  ret = inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);
  if (ret == -1)
  {
    perror("change ip fail");
    close(client_fd);
    return -1;
  }

  ret = connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  if (ret == -1)
  {
    perror("connect fail");
    close(client_fd);
    return -1;
  }

  char message[1024] = {0};
  int flag = 1;
  ret = setsockopt(client_fd, IPPROTO_TCP, TCP_NODELAY, (char *)&flag, sizeof(flag));
  if (ret == -1)
  {
    perror("setsockopt fail");
  }

  for (int i = 0; i < MESSAGE_COUNT; i++)
  {
    sprintf(message, "Message %d from client: ", i + 1);

    int remaining = sizeof(message) - strlen(message) - 1;
    // memset(message + strlen(message), 'A', remaining);
    message[sizeof(message) - 1] = '\0';
    sned_message_with_length(client_fd, message);
    printf("send message:%d\n", i + 1);
    usleep(1000);
  }

  close(client_fd);

  return 0;
}