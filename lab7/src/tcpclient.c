#include <arpa/inet.h>
#include <getopt.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>


#define SADDR struct sockaddr
#define SIZE sizeof(struct sockaddr_in)

int main(int argc, char** argv)
{
  int bufsize = -1;
  int port = -1;
  char* addr = NULL;

   while (1)
  {
    int current_optind = optind ? optind : 1;

    static struct option options[] = {{"bufsize", required_argument, 0, 0},
                                      {"port", required_argument, 0, 0},
                                      {"addr", required_argument, 0, 0},
                                      {0, 0, 0, 0}};

    int option_index = 0;
    int c = getopt_long(argc, argv, "", options, &option_index);

    if (c == -1)
    break;

    switch (c)
    {
      case 0:
      {
        switch (option_index)
        {
          case 0:
          {
            bufsize = atoi(optarg);
            if (bufsize < 0)
            {
              printf("\nThe bufsize is a positive number\n\n");
              return 1;
            }
          }
          break;

          case 1:
          {
            port = atoi(optarg);
            if (port <= 0)
            {
              printf("\nThe port is a positive number\n\n");
              return 1;
            }
          }
          break;

          case 2:
          {
            addr = (char*)malloc(strlen(optarg) * sizeof(char));
            memcpy(addr, optarg, strlen(optarg) * sizeof(char));
          }
          break;
        
          default:
          printf("\nIndex %d is out of options\n\n", option_index);
        }
      }
      break;

      case '?':
      {
        printf("\nArguments error\n\n");
      }
      break;

      default:
      fprintf(stderr, "\ngetopt returned character code 0%o?\n\n", c);
    }
  }

  if (optind < argc)
  {
    printf("\nHas at least one no option argument\n\n");
    return 1;
  }

  if (bufsize == -1 || port == -1 || addr == NULL)
  {
    printf("\nUsage: %s --bufsize \"num\" --port \"num\" --addr \"num\" \n\n", argv[0]);
    return 1;
  }

  int fd;
  int nread;
  struct sockaddr_in servaddr;

  char buf[bufsize];

  if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    perror("\nCan\'t create socket\n\n");
    exit(1);
  }

  memset(&servaddr, 0, SIZE);
  servaddr.sin_family = AF_INET;

  // функция преобразует строку символов (argv[1]) в сетевой адрес (типа AF_INET (IPv4)), затем копирует полученную структуру с адресом в servaddr.sin_addr
  if (inet_pton(AF_INET, addr, &servaddr.sin_addr) <= 0)
  {
    perror("\nBad address\n\n");
    exit(1);
  }

  // преобразует узловой порядок расположения байтов положительного целого argv[2] в сетевой порядок расположения байтов
  servaddr.sin_port = htons(port);

  if (connect(fd, (SADDR*)&servaddr, SIZE) < 0)
  {
    perror("\nCan\'t connect\n\n");
    exit(1);
  }

  write(1, "Input message to send\n", 22);

  while ((nread = read(0, buf, bufsize)) > 0)
  {
    if (write(fd, buf, nread) < 0)
    {
      perror("\nCan\'t write\n\n");
      exit(1);
    }
  }

  close(fd);
  exit(0);
}
