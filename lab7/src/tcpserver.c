#include <getopt.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define SADDR struct sockaddr

int main(int argc, char** argv)
{
  int bufsize = -1;
  int port = -1;

   while (1)
  {
    int current_optind = optind ? optind : 1;

    static struct option options[] = {{"bufsize", required_argument, 0, 0},
                                      {"port", required_argument, 0, 0},
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

  if (bufsize == -1 || port == -1)
  {
    printf("\nUsage: %s --bufsize \"num\" --port \"num\" \n\n", argv[0]);
    return 1;
  }
  
  const size_t kSize = sizeof(struct sockaddr_in);

  int lfd, cfd;
  int nread;
  struct sockaddr_in servaddr;
  struct sockaddr_in cliaddr;

  char buf[bufsize];

  if ((lfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    perror("\nCan\'t create socket\n\n");
    exit(1);
  }

  memset(&servaddr, 0, kSize);
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(port);

  if (bind(lfd, (SADDR*)&servaddr, kSize) < 0)
  {
    perror("\nCan\'t bind\n\n");
    exit(1);
  }

  if (listen(lfd, 5) < 0)
  {
    perror("\nCan't listen\n\n");
    exit(1);
  }

  while (1)
  {
    unsigned int clilen = kSize;

    if ((cfd = accept(lfd, (SADDR *)&cliaddr, &clilen)) < 0)
    {
      perror("\nCan\'t accept\n\n");
      exit(1);
    }
    printf("\nConnection established\n\n");

    while ((nread = read(cfd, buf, bufsize)) > 0)
    {
      write(1, &buf, nread);
    }

    if (nread == -1)
    {
      perror("\nCan\'t read\n\n");
      exit(1);
    }
    close(cfd);
  }
}
