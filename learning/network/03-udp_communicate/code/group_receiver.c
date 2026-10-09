#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 12345
#define MULTICAST_IP "239.255.0.1"
#define BUFFER_SIZE 1024

int main(void)
{

  int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd == -1)
  {
    perror("create socket fail");
    return -1;
  }

  struct sockaddr_in local_addr = {0};
  local_addr.sin_family = AF_INET;
  local_addr.sin_port = htons(PORT);
  local_addr.sin_addr.s_addr = INADDR_ANY;

  int ret = bind(sockfd, (struct sockaddr *)&local_addr, sizeof(local_addr));

  if (ret == -1)
  {
    perror("bind fail");
    close(sockfd);
    return -1;
  }

  // join group
  struct ip_mreq mreq;
  mreq.imr_multiaddr.s_addr = inet_addr(MULTICAST_IP);
  mreq.imr_interface.s_addr = htonl(INADDR_ANY);

  int ret_set = setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq));

  if (ret_set == -1)
  {
    perror("join group fail");
    close(sockfd);
    return -1;
  }

  printf("joined the group: %s, listen port: %d", MULTICAST_IP, PORT);

  while (1)
  {
    char buf[BUFFER_SIZE];
    struct sockaddr_in sender_addr;
    socklen_t sender_addr_len = sizeof(sender_addr);

    ssize_t ret_recv = recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr *)&sender_addr, &sender_addr_len);
    if (ret_recv == -1)
    {
      perror("receive fail");
      continue;
    }

    buf[ret_recv] = '\0';
    printf("receive form: %s:%d data: %s \n", inet_ntoa(sender_addr.sin_addr), ntohs(sender_addr.sin_port), buf);
  }

  return 0;
}