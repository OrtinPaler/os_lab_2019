
/* Программа для отображения адресной информации о процессе
 * Adapted from Gray, J., program 1.4
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

// макроопределение
#define SHW_ADR(ID, I) (printf("ID %s is at virtual address: %8X\n", ID, &I))

// глобальные переменные для памяти процесса
extern int etext, edata, end;

// инициализированные данные
char *cptr = "This message is output by the function showit()\n\n";

// неинициализированные данные
char buffer1[25];

int showit();

int main() 
{
  int i = 0; 

  // Печать адресной информации
  printf("\nAddress etext: %8X \n", &etext);
  printf("Address edata: %8X \n", &edata);
  printf("Address end  : %8X \n\n", &end);

  SHW_ADR("main", main);
  SHW_ADR("showit", showit);
  SHW_ADR("cptr", cptr);
  SHW_ADR("buffer1", buffer1);
  SHW_ADR("i", i);
  strcpy(buffer1, "\nA demonstration\n");
  write(1, buffer1, strlen(buffer1) + 1); // Системный вызов
  showit(cptr);
  return 0;
}

int showit(p) char *p;
{
  char *buffer2;
  SHW_ADR("buffer2", buffer2);
  if ((buffer2 = (char *)malloc((unsigned)(strlen(p) + 1))) != NULL) 
  {
    printf("Alocated memory at %X\n", buffer2);
    strcpy(buffer2, p);
    printf("%s", buffer2);
    free(buffer2);
  } 
  else 
  {
    printf("Allocation error\n");
    exit(1);
  }
}