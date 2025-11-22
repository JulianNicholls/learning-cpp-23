#include "stdio.h"

void print(int *array, size_t size)
{
  for (size_t i = 0; i < size; ++i)
  {
    printf("%2d, ", array[i]);
  }
}
