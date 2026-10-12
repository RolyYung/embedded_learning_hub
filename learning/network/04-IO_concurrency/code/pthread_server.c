#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netinet/ip.h>

#define PORT 8888
#define SERVER_IP "192.168.3.10"
#define BUFFER_SIZE 128

typedef struct MSG
{
  int acceptfd;
  struct sockaddr_in clientInfo;
} msg_t;

void *deal_read_write(void *arg)
{
  msg_t msg = *(msg_t *)arg;
  printf("client[%s:%d], connect server", inet_ntoa(msg.clientInfo.sin_addr), ntohs(msg.clientInfo.sin_port));

  char buf[BUFFER_SIZE] = {0};
  int nbytes = 0;

  while (1)
  {
    nbytes = recv(msg.acceptfd, buf, BUFFER_SIZE, 0);
    if (nbytes == -1)
    {
      perror("receive meg fail");
    }
    else if (nbytes == 0)
    {
      printf("client[%s:%d], disconnect the serve", inet_ntoa(msg.clientInfo.sin_addr), ntohs(msg.clientInfo.sin_port));
      break;
    }

    printf("client [%s:%d] send data: %s", inet_ntoa(msg.clientInfo.sin_addr), ntohs(msg.clientInfo.sin_port), buf);

    // echo to client
    strcat(buf, "--server");
    int ret = send(msg.acceptfd, buf, BUFFER_SIZE, 0);
    if (ret == -1)
    {
      perror("send error");
    }
    close(msg.acceptfd);
    pthread_exit(NULL);
  }

  return NULL;
}

int main()
{
  int ret;
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1)
  {
    perror("create socket fail");
    return -1;
  }

  struct sockaddr_in serverInfo;
  memset(&serverInfo, 0, sizeof(serverInfo));
  serverInfo.sin_family = AF_INET;
  serverInfo.sin_port = htons(PORT);
  serverInfo.sin_addr.s_addr = inet_addr(SERVER_IP);
  socklen_t serverInfo_len = sizeof(serverInfo);

  ret = bind(sockfd, (struct sockaddr *)&serverInfo, serverInfo_len);
  if (ret == -1)
  {
    perror("bind socket fail");
    close(sockfd);
    return -1;
  }
  printf("bind success \n");

  ret = listen(sockfd, 5);
  if (ret == -1)
  {
    perror("listen socket fail");
    close(sockfd);
    return -1;
  }
  printf("listen success \n");

  struct sockaddr_in clientInfo;
  socklen_t clientInfo_len = sizeof(clientInfo);

  int acceptfd = 0;
  pthread_t pid;
  msg_t msg;

  while (1)
  {
    printf("accepting \n");
    acceptfd = accept(sockfd, (struct sockaddr *)&clientInfo, &clientInfo_len);
    printf("accept success \n");
    if (acceptfd == -1)
    {
      perror("accpet connection fail");
      close(sockfd);
      return -1;
    }

    msg.acceptfd = acceptfd;
    msg.clientInfo = clientInfo;

    ret = pthread_create(&pid, NULL, deal_read_write, &msg);
    if (ret != 0)
    {
      printf("errorno: %d, error msg: %s \n", ret, strerror(ret));
      close(sockfd);
      return -1;
    }

    pthread_detach(pid);
  }

  close(sockfd);

  return 0;
}