#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define PORT 12345
#define MULTICAST_IP "239.255.0.1"

int main()
{

  // create socket
  int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd == -1)
  {
    perror("create socket fail");
    return -1;
  }

  // init sockaddr
  struct sockaddr_in senderInfo = {0};
  senderInfo.sin_family = AF_INET;
  senderInfo.sin_port = htons(PORT);
  senderInfo.sin_addr.s_addr = inet_addr(MULTICAST_IP);

  int ttl = 1; // TTL 1: just in local network
  int ret_set = setsockopt(sockfd, IPPROTO_IP, IP_MULTICAST_TTL, &ttl, sizeof(ttl));
  if (ret_set == -1)
  {
    perror("join group fail");
    close(sockfd);
    return -1;
  }

  // send data to the group
  char message[] = "Hello! Multicast Group";
  ssize_t ret_send = sendto(sockfd, message, strlen(message), 0, (struct sockaddr *)&senderInfo, sizeof(senderInfo));
  if (ret_send == -1)
  {
    perror("send data fail");
  }
  else
  {
    printf("send data success: %s:%zd bytes \n", message, ret_send);
  }

  return 0;
}