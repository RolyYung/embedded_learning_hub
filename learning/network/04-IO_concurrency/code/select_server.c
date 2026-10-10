#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <sys/select.h>
#include <unistd.h>

#define PORT 8888
#define SERVER_IP "192.168.3.13"
#define BUFFER_SIZE 128

int main()
{
  int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (listen_fd == -1)
  {
    perror("create listen socket fail");
    return -1;
  }

  struct sockaddr_in server_addr;
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

  int ret_bind = bind(listen_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
  if (ret_bind == -1)
  {
    perror("bind fail");
    close(listen_fd);
    return -1;
  }

  int ret_listen = listen(listen_fd, 5);
  if (ret_listen == -1)
  {
    close(listen_fd);
    perror("listen fail");
    return -1;
  }

  fd_set readfd_save_fd, readfd_modify_set;
  FD_ZERO(&readfd_save_fd);
  FD_SET(listen_fd, &readfd_save_fd);

  int max_fd = listen_fd;
  char buf[BUFFER_SIZE] = {0};

  while (1)
  {
    readfd_modify_set = readfd_save_fd;
    int fds = select(max_fd + 1, &readfd_modify_set, NULL, NULL, NULL);
    if (fds == -1)
    {
      perror("select fail");
      continue;
    }

    int event_fd = 3;
    struct sockaddr_in client_addr;
    socklen_t clientaddr_len = sizeof(client_addr);

    for (; event_fd < max_fd + 1; event_fd++)
    {
      if (FD_ISSET(event_fd, &readfd_modify_set))
      {
        if (event_fd == listen_fd)
        {
          int acceptfd = accept(event_fd, (struct sockaddr *)&client_addr, &clientaddr_len);
          if (acceptfd == -1)
          {
            perror("accept fail");
            continue;
          }

          FD_SET(acceptfd, &readfd_save_fd);
          max_fd = max_fd > acceptfd ? max_fd : acceptfd;

          printf("client %s: %d connect the server", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
        }
        else
        {
          memset(buf, 0, sizeof(buf));
          int nbytes = recv(event_fd, buf, BUFFER_SIZE, 0);
          if (nbytes == -1)
          {
            perror("get client data fail");
            continue;
          }
          else if (nbytes == 0)
          {
            printf("client [%s:%d] disconnect \n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));
            FD_CLR(event_fd, &readfd_save_fd);
            close(event_fd);
            continue;
          }
          printf("客户端【%s：%d】发来数据：%s\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), buf);
          // 回显
          nbytes = send(event_fd, buf, BUFFER_SIZE, 0);
          if (nbytes == -1)
          {
            perror("回显失败：");
            continue;
          }
        }
      }
    }
  }

  return 0;
}