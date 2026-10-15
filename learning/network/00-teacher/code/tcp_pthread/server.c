#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#define DEF_VAL 0
#define ERR_VAL -1
#define PORT 8888

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void *client_handler(void *arg)
{
  int confd = *(int *)arg;
  pthread_mutex_unlock(&mutex);
  int ret = 0;
  char buf[1024] = {0};
  while (1)
  {
    ret = read(confd, buf, sizeof(buf));
    if (ret == ERR_VAL)
    {
      perror("read failed");
      break;
    }
    else if (ret == 0)
    {
      printf("client disconected \n");
      break;
    }
    printf("recv message: %s\n", buf);
    write(confd, buf, ret);
    memset(&buf, 0, sizeof(buf));
  }
  close(confd);
  return;
}

int main()
{
  int ret;
  int sockfd = socket(AF_INET, SOCK_STREAM, DEF_VAL);
  if (sockfd == ERR_VAL)
  {
    perror("create socket failed");
    exit(1);
  }

  struct sockaddr_in server_addr;
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = INADDR_ANY;
  ret = bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  if (ret == ERR_VAL)
  {
    perror("bind socket failed");
    close(sockfd);
    return -1;
  }

  ret = listen(sockfd, 5);
  if (ret == ERR_VAL)
  {
    perror("listen socket failed");
    close(sockfd);
    exit(1);
  }

  int acceptfd;
  struct sockaddr_in client_addr;
  memset(&client_addr, 0, sizeof(client_addr));
  socklen_t client_addr_len = sizeof(client_addr_len);

  pthread_t tid;
  while (1)
  {
    pthread_mutex_lock(&mutex);
    acceptfd = accept(sockfd, (struct sockaddr *)&client_addr, &client_addr_len);
    if (acceptfd == ERR_VAL)
    {
      perror("accept failed");
      exit(1);
    }
    char caddr[20] = {0};
    printf("client connect: %s:%d\n", inet_ntop(AF_INET, &client_addr.sin_addr, caddr, sizeof(caddr)), ntohs(client_addr.sin_port));

    pthread_create(&tid, NULL, client_handler, (void *)&acceptfd);
    pthread_detach(tid);
  }
  pthread_mutex_destroy(&mutex);
  close(sockfd);

  return 0;
}