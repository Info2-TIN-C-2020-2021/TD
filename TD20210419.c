/**
  \file      TD20210419.c
  \brief     Memory allocation 
  \author    Pierre BRESSY
  \version   1.0
  \date      2021-04-19 14:45:00
  \details

**/

#include <stdio.h>  // standard library for inputs and ouputs
#include <assert.h>
#include <stdint.h>
#include <stdlib.h> // for malloc / free

int main(int argc, char const *argv[])
{
  size_t n = 0;
  double *t = NULL;

  printf("How many cells ? ");
  scanf("%lu", &n);

  printf("Allocating %lu bytes...\n", n * sizeof(double));

  t = (double *)malloc(n*sizeof(double));

  if(NULL==t) {
    printf("Error while allocation %zu bytes.\n", n * sizeof(double));
  }
  else {

    printf("Memory allocated at address %p\n", t);

    printf("Freeing memory...\n");
    free(t);
    t = NULL;

  }

  return 0;
}


