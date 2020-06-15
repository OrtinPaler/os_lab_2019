#include <errno.h>
#include <getopt.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

void fact_mod(void *);

struct fact_mod_param  // общая структура для потоков
{
  int number;
  int number_1;
  int module;
  int num_threads;
  int result;
};

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char **argv)
{
  int k = -1;
  int pnum = -1;
  int mod = -1;

  while(true)
  {
    int current_optind = optind ? optind : 1;

    static struct option options[] = {{"number", required_argument, 0, 0},
                                      {"pnum", required_argument, 0, 0},
                                      {"mod", required_argument, 0, 0},
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
            k = atoi(optarg);
            if(k <= 0)
            {
              printf("\nThe factorial argument is a positive number!\n\n");
              return 1;
            }
          }  
          break;

          case 1:
          {
            pnum = atoi(optarg);
            if (pnum <= 0)
            {
              printf("\nPnum is a positive number!\n\n");
              return 1;
            }
          }
          break;

          case 2:
          {
            mod = atoi(optarg);
            if(mod <= 0)
            {
              printf("\nThe factorial modul's is a positive number!\n\n");
              return 1;
            }  
          }
        }
      }
      break;

      case '?':
      break;

      default:
      printf("\ngetopt returned character code 0%o?\n\n", c);
    }
  }

  if (optind < argc)
  {
    printf("\nHas at least one no option argument\n\n");
    return 1;
  }

  if (k == -1 || pnum == -1 || mod == -1)
  {
    printf("\nUsage: %s -k \"num\" --pnum \"num\" --mod \"num\" \n\n", argv[0]);
    return 1;
  }

  struct fact_mod_param parameters;
  parameters.number = k;
  parameters.num_threads = pnum;
  parameters.module = mod;
  parameters.number_1 = 1;
  parameters.result = 1;

  pthread_t thread[pnum];

  for (int i = 0; i < pnum; ++i)
  {
    if (pthread_create(&thread[i], NULL, (void *)fact_mod, (void *)&parameters) != 0)
    {
      perror("pthread_create %i\n");
      exit(1);
    }
  }

  for (int i = 0; i < pnum; ++i)
  {
    if (pthread_join(thread[i], NULL) != 0)
    {
      perror("pthread_join %i\n");
      exit(-1);
    }
  }

  printf("\nRESULT = %i\n\n", parameters.result);

  return 0;
}

void fact_mod(void* param)
{
  struct fact_mod_param* p = (struct fact_mod_param*)param;
  for (int i = 1; i <= (p->number / p->num_threads); ++i)
  {
    pthread_mutex_lock(&mutex);
    
    p->result *= p->number_1;
    p->result %= p->module;
    p->number_1++;
      
    if (p->number_1 > p->number)
    break;

    pthread_mutex_unlock(&mutex);
  }
}