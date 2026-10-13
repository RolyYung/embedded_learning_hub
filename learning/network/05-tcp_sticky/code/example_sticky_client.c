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

void send_message_with_length(int socket, const char *message)
{
  uint32_t len = strlen(message);
  uint32_t network_len = htonl(len);

  send(socket, &network_len, sizeof(network_len), 0);

  send(socket, message, len, 0);
}

int main()
{

  int sockfd = 0;

  struct sockaddr_in server_addr;

  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    perror("socket failed");
    return -1;
  }

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0)
  {
    perror("changed ip failed");
    close(sockfd);
    return -1;
  }

  if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
  {
    perror("connect failed");
    close(sockfd);
    return -1;
  }

  char message[1024];

  int flag = 1;
  if (setsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY, (char *)&flag, sizeof(flag)) < 0)
  {
    perror("setsockopt failed");
  }

  for (int i = 0; i < MESSAGE_COUNT; i++)
  {
    sprintf(message, "Message %d from client:", i + 1);

    size_t remaining = sizeof(message) - strlen(message) - 1;
    memset(message + strlen(message), 'A', remaining);
    message[sizeof(message) - 1] = '\0';
    // send(sockfd, message,strlen(message),0);
    send_message_with_length(sockfd, message);
    printf("send message:%d\n", i + 1);
    usleep(1000);
  }

  close(sockfd);

  return 0;
}
