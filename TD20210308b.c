/**
  \file      TD20210308b.c
  \brief     read txt file line by line
  \author    Pierre BRESSY
  \version   1.0
  \date      2021-01-11 13:55:00
  \details

**/

#include <stdio.h>  // standard library for inputs and ouputs
#include <string.h>
#define MAX_LENGTH 10

int main(int argc, const char *argv[]) {

  const char *filename = "./data.csv";
  const char *mode = "r";
  char s[MAX_LENGTH] = {0};
  FILE *fp = NULL;
  unsigned int count = 0;
  char *r = NULL; // fgets result

  fp = fopen(filename, mode);
  if(NULL==fp){
    printf("Error while opening %s\n", filename);
  }
  else {

    do {
      r = fgets(s, MAX_LENGTH, fp);
      if(r!=NULL && NULL!=strchr(s,'\n')) {   // strchr
        count++;
      }
    } while (r!=NULL);

    printf("%u lines.\n", count);

    if (0 != fclose(fp))
    {
      printf("Error while closing %s\n", filename);
    }
  }

  return 0;
}
