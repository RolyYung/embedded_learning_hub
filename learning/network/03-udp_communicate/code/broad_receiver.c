#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>

#define PORT 9999
#define BUFFER_SIZE 1024

int main()
{
  int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if (sockfd == -1)
  {
    perror("create socket fail");
    return -1;
  }

  struct sockaddr_in local_addr;
  memset(&local_addr, 0, sizeof(local_addr));
  local_addr.sin_family = AF_INET;
  local_addr.sin_port = htons(PORT);
  local_addr.sin_addr.s_addr = htonl(INADDR_ANY);

  int ret_bind = bind(sockfd, (struct sockaddr *)&local_addr, sizeof(local_addr));
  if (ret_bind == -1)
  {
    perror("bind fail");
    close(sockfd);
    return -1;
  }

  printf("listen broadcast port: %d\n", PORT);

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
    printf("get broadcast info: %s(from %s:%d)\n", buf, inet_ntoa(sender_addr.sin_addr), ntohs(sender_addr.sin_port));
  }
  close(sockfd);

  return 0;
}