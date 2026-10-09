#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define PORT 8888
#define SERVER_IP "127.0.0.1"
#define BUFFER_SIZE 1024

int main(void)
{

  int sock_fd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sock_fd == -1)
  {
    perror("create socket fail:");
    return -1;
  }

  struct sockaddr_in serverInfo = {0};
  serverInfo.sin_addr.s_addr = inet_addr(SERVER_IP);
  serverInfo.sin_port = htons(PORT);
  serverInfo.sin_family = AF_INET;

  char message[] = "Hello! Server";
  ssize_t ret_sendto = sendto(sock_fd, message, strlen(message), 0, (struct sockaddr *)&serverInfo, sizeof(serverInfo));

  if (ret_sendto == -1)
  {
    perror("send fail: ");
    close(sock_fd);
    return -1;
  }

  printf("send data: %s \n", message);

  // echo data
  char buf[BUFFER_SIZE] = {0};
  struct sockaddr_in fromInfo;
  socklen_t fromInfo_len = sizeof(fromInfo);
  ssize_t ret_recvfrom = recvfrom(sock_fd, buf, sizeof(buf) - 1, 0, (struct sockaddr *)&fromInfo, &fromInfo_len);

  if (ret_recvfrom == -1)
  {
    perror("recive fail: ");
  }
  else
  {
    buf[ret_recvfrom] = '\0';
    printf("server echo: %s \n", buf);
  }

  close(sock_fd);

  return 0;
}