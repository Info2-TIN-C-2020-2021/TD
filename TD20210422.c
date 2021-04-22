/**
  \file      TD20210422.c
  \brief     read txt file  (with memory allocation)
  \author    Pierre BRESSY
  \version   1.0
  \date      2021-04-22 14:45:00
  \details

**/

#include <stdio.h>  // standard library for inputs and ouputs
#include <assert.h>
#include <stdint.h>
#include <stdlib.h> // for malloc / free

typedef struct {
  double time;
  double position;
} sData;

int main(int argc, char const *argv[])
{
  FILE *f = NULL;
  const char *filename = "data/data.txt";
  const char *mode = "r";
  uint32_t n = 0;
  uint32_t index = 0;
  sData *t = NULL;
  double minValue = 0.;
  double maxValue = 0.;
  double meanValue = 0.;
  double sum = 0.;
  int ret = 0;

  f = fopen(filename, mode);

  if(NULL!=f) {

    ret=fscanf(f, "%u", &n);
    if(ret==1) {

      t = (sData *)malloc(n * sizeof(sData));
      if(NULL!=t) {

        for (index = 0; index < n;index++) {
          // var to update:
          //   t[index].time
          //   t[index].position
          ret = fscanf(f, "%lf%lf", &t[index].time, &t[index].position);
          if(2!=ret) {
            printf("Error, bad format in line %u in %s\n", index+2, filename);
          }
        }

        minValue = maxValue = t[0].position;
        sum=t[0].position;
        for (index = 1; index < n; index++)
        {
          sum += t[index].position;
          minValue = t[index].position < minValue ? t[index].position : minValue;
          maxValue = t[index].position > maxValue ? t[index].position : maxValue;
        }

        meanValue = sum / n;

        printf("Min  = %+6.3lf\n", minValue);
        printf("Max  = %+6.3lf\n", maxValue);
        printf("Mean = %+.10lf\n", meanValue);

        free(t);
        t = NULL;
      }
      else {
        printf("Error while allocating %lu bytes\n", n * sizeof(sData));
      }
    }
    else {
      printf("Error, bad format in line 1 in %s\n", filename);
    }

    if(0!=fclose(f)) {
      printf("Error while closing %s\n", filename);
    }

  }
  else {
    printf("Error while opening %s\n", filename);
  }

  return 0;
}


