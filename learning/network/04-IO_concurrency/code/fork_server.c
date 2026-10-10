#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <sys/types.h>

#define PORT 8888
#define SERVER_IP "192.168.3.13"
#define BUFFER_SIZE 128

void sig_func(int signum)
{
  wait(NULL); // 处理SIGUSR1信号, 回收子进程资源, 避免僵尸进程.
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

  struct sockaddr_in server_addr;
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);
  socklen_t serveraddr_len = sizeof(server_addr);

  ret = bind(sockfd, (struct sockaddr *)&server_addr, serveraddr_len);
  if (ret == -1)
  {
    perror("bind fail");
    close(sockfd);
    return -1;
  }

  ret = listen(sockfd, 5);
  if (ret == -1)
  {
    perror("listen fail");
    close(sockfd);
    return -1;
  }

  struct sockaddr_in client_addr;
  socklen_t clientaddr_len = sizeof(client_addr);
  int acceptfd = 0;
  pid_t pid = 0;

  signal(SIGUSR1, sig_func);

  while (1)
  {
    acceptfd = accept(sockfd, (struct sockaddr *)&client_addr, &clientaddr_len);
    if (acceptfd == -1)
    {
      perror("accept connect fail");
      close(sockfd);
    }

    pid = fork();
    if (pid == -1)
    {
      perror("fork process fail");
      close(acceptfd);
      break;
    }
    else if (pid == 0)
    {
      char buf[BUFFER_SIZE] = {0};
      int nbytes = 0;
      printf("client [%s:%d] connect the server", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

      nbytes = recv(acceptfd, buf, BUFFER_SIZE, 0);
      if (nbytes == -1)
      {
        printf("receive fail");
      }
      else if (nbytes == 0)
      {
        printf("client disconncet\n");
      }
      printf("client send data: %s", buf);
      strcat(buf, "--from server");
      send(acceptfd, buf, BUFFER_SIZE, 0);
      close(acceptfd);
      kill(getpid(), SIGUSR1);
      exit(0);
    }
    else if (pid > 0)
    {
      close(acceptfd);
    }
  }

  return 0;
}