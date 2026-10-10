#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>

int main(int argc, const char *argv[])
{
  // create socket
  int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

  if (socket_fd == -1)
  {
    perror("create socket fail:");
    return -1;
  }

  // init server address
  struct sockaddr_in serverInfo = {0};

  serverInfo.sin_family = AF_INET;
  serverInfo.sin_addr.s_addr = inet_addr("192.168.3.13");
  serverInfo.sin_port = htons(8888);

  // connect server
  int ret = connect(socket_fd, (struct sockaddr *)&serverInfo, sizeof(serverInfo));

  if (ret == -1)
  {
    perror("connect error:");
    close(socket_fd);
    return -1;
  }

  // data send
  char buf[128] = {0};
  while (1)
  {
    memset(buf, 0, sizeof(buf));
    fgets(buf, sizeof(buf), stdin);

    int nbytes = send(socket_fd, buf, sizeof(buf), 0);

    if (nbytes == -1)
    {
      perror("send fail:");
      return -1;
    }

    memset(buf, 0, sizeof(buf));
    int nbytes_recv = recv(socket_fd, buf, sizeof(buf), 0);
    if (nbytes_recv == 0)
    {
      printf("server close, exit process");
      return 0;
    }
    printf("server send data: %s \n", buf);
  }
  return 0;
}