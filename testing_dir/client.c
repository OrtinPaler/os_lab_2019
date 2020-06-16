#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

void write_text(int socket_fd, const char* text)
{
  // указывается число байтов в строке, включая NULL (поэтому + 1)
  int leng = strlen(text) + 1;
  write(socket_fd, &leng, sizeof(leng));
  
  // записываем строку
  write(socket_fd, text, leng);
}

int main(int argc, char* const argv[])
{
  const char* const socket_name = argv[1];
  const char* const message = argv[2];
  struct sockaddr_un name;

  int socket_fd = socket(PF_LOCAL, SOCK_STREAM, 0);

  name.sun_family = AF_LOCAL;

  strcpy(name.sun_path, socket_name);

  // подключение к серверному сокету
  connect(socket_fd, (struct sockaddr*)&name, sizeof(struct sockaddr_un));

  // передача сообщения
  write_text(socket_fd, message);

  close(socket_fd);
  return 0;
}