#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "find_min_max.h"
#include "utils.h"

int main(int argc, char **argv) {
  if (argc != 3) {
    printf("\nUsage: %s seed arraysize\n\n", argv[0]);
    
    int array_size = strlen(argv[0]), seed = array_size;

    int *array = malloc(array_size * sizeof(int));
    GenerateArray(array, array_size, seed);
    struct MinMax min_max = GetMinMax(array, 0, array_size);
    free(array);
    
    printf("\nmin: %d\n", min_max.min);
    printf("max: %d\n\n", min_max.max);
    return 1;
  }

  int seed = atoi(argv[1]);
  if (seed <= 0) {
    printf("seed is a positive number\n");
    return 1;
  }

  int array_size = atoi(argv[2]);
  if (array_size <= 0) {
    printf("array_size is a positive number\n");
    return 1;
  }

  int *array = malloc(array_size * sizeof(int));
  GenerateArray(array, array_size, seed);
  struct MinMax min_max = GetMinMax(array, 0, array_size);
  free(array);

  printf("\nmin: %d\n", min_max.min);
  printf("max: %d\n\n", min_max.max);

  return 0;
}
