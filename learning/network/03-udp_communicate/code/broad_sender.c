#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define PORT 9999
#define BROADCAST_IP "255.255.255.255"

int main(void)
{

  int socketfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (socketfd == -1)
  {
    perror("create socket fail");
    return -1;
  }

  int opt = 1;
  int ret_set = setsockopt(socketfd, SOL_SOCKET, SO_BROADCAST, &opt, sizeof(opt));
  if (ret_set == -1)
  {
    perror("start broadcast fail");
    close(socketfd);
    return -1;
  }

  struct sockaddr_in broadcast_addr = {0};
  broadcast_addr.sin_family = AF_INET;
  broadcast_addr.sin_port = htons(PORT);
  broadcast_addr.sin_addr.s_addr = inet_addr(BROADCAST_IP);

  // send broadcast data
  char message[] = "Hello! Broadcast";
  int ret_send = sendto(socketfd, message, strlen(message), 0, (struct sockaddr *)&broadcast_addr, sizeof(broadcast_addr));
  if (ret_send == -1)
  {
    perror("send fail");
  }
  else
  {
    printf("broadcast send success: %s:%d bytes \n", message, ret_send);
  }
  close(socketfd);

  return 0;
}