#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <unistd.h>

#define PORT 8888
#define SERVER_IP "192.168.3.11"
int main()
{
  int ret;
  int sockfd = socket(AF_INET, SOCK_STREAM, 6);
  if (sockfd == -1)
  {
    perror("create socket failed");
    exit(1);
  }

  struct sockaddr_in server_info;
  memset(&server_info, 0, sizeof(server_info));
  server_info.sin_family = AF_INET;
  server_info.sin_port = htons(PORT);
  inet_pton(AF_INET, SERVER_IP, &server_info.sin_addr);

  ret = connect(sockfd, (struct sockaddr *)&server_info, sizeof(server_info));
  if (ret == -1)
  {
    perror("connect failed");
    close(sockfd);
    // return -1;
    exit(1);
  }

  char buf[1024] = {0};

  fgets(buf, 1024, stdin);
  ret = send(sockfd, buf, 1024, 0);
  if (ret == -1)
  {
    perror("send failed");
    exit(1);
  }

  memset(buf, 0, sizeof(buf));
  recv(sockfd, buf, 1024, 0);
  printf("recv msg: %s\n", buf);

  close(sockfd);
  return 0;
}