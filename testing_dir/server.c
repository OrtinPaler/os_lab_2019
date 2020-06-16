#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

int server (int client_socket)
{
  while(1)
  {
    int length;
    char* text;

    // читаем длину сообщения
    if (read(client_socket, &length, sizeof(length)) == 0)
    return 0;

    // выделяем память для хранения текста
    text = (char*)malloc(length);

    // читаем сообщение и выводи его на экран
    read(client_socket, text, length);
    printf("\n%s\n\n", text);

    // отчищаем память
    free(text);

    // если клиент послал сообщение "quit", то работа сервера
    // завершается
    if (!strcmp(text, "quit"))
    return 1;
  }    
}

int main(int argc, char* const argv[])
{
  const char* const socket_name = argv[1];
  struct sockaddr_un name;
  int client_sent_quit_message;

  // создание сокета
  // параметры (пространство имен, тип взаимодействия, протокол)
  // SOCK_STREAM - сокет ориентирован на соединения (TCP); 
  // SOCK_DGRAM - дейтаграммный сокет (UDP);
  int socket_fd = socket(PF_LOCAL, SOCK_STREAM, 0);

  // адрес находиться в локальном пространстве имен
  name.sun_family = AF_LOCAL;


  strcpy(name.sun_path, socket_name);

  // назначаем адрес, чтобы клиент смог найти сокет
  // параметры (дескриптор сокета, указатель на адресную структуру, длина адресной структуры в байтах)
  bind(socket_fd, (struct sockaddr*)&name, sizeof(struct sockaddr_un));

  // сокет обозначает себя как сервер
  // размер очереди равен 5
  listen(socket_fd, 5);

  do
  {
    struct sockaddr_un client_name;
    socklen_t client_name_len;
    
    // сервер принимает запрос от клиента на подключение
    // параметры (дескриптор сокета, указатель на адресную структуру клиентского сокета, длина адресной структуры в байтах)
    // создается новый сокет для обслуживания клиентского соединения
    int client_socket_fd = accept(socket_fd, (struct sockaddr*)&client_name, &client_name_len);

    client_sent_quit_message = server(client_socket_fd);
    close(client_socket_fd);
  } while (!client_sent_quit_message);
  
  close(socket_fd);

  // удаление локального сокета
  unlink(socket_name);
  return 0;
}