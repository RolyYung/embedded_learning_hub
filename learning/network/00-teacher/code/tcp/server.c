#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>

#define DEF_VAL 0
#define ERR_VAL -1
#define ERR_EXIT(msg) \
  do                  \
  {                   \
    perror(msg);      \
    exit(1);          \
  } while (0)
#define SERVER_IP "192.168.3.11"
#define PORT 8888
#define BUFFER_SIZE 1024

int main()
{
  int ret;
  int sockfd = socket(AF_INET, SOCK_STREAM, DEF_VAL);
  if (sockfd == ERR_VAL)
  {
    ERR_EXIT("create socket failed");
  }

  struct sockaddr_in server_addr = {0};
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr);

  ret = bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  if (ret == ERR_VAL)
  {
    ERR_EXIT("bind fail");
  }

  ret = listen(sockfd, 5);
  if (ret == ERR_VAL)
  {
    ERR_EXIT("listen fail");
  }

  int acceptfd;
  struct sockaddr_in client_addr = {0};
  socklen_t client_addr_len = sizeof(client_addr);
  char buf[BUFFER_SIZE];
  while (1)
  {
    acceptfd = accept(sockfd, (struct sockaddr *)&client_addr, &client_addr_len);
    if (acceptfd == ERR_VAL)
    {
      perror("accept fail");
      continue;
    }

    while (1)
    {
      int nbytes = recv(acceptfd, buf, sizeof(buf), 0);
      if (nbytes == ERR_VAL)
      {
        perror("recv fail");
        close(acceptfd);
        break;
      }
      else if (nbytes == 0)
      {
        printf("client disconnected \n");
        close(acceptfd);
        break;
      }
      char client_ip[16];
      printf("recv %d bytes, from [%s:%d], message: %s", nbytes, inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, sizeof(client_ip)), ntohs(client_addr.sin_port), buf);

      send(acceptfd, strcat(buf, " -- from server"), sizeof(buf), 0);
    }
  }

  close(sockfd);

  return 0;
}