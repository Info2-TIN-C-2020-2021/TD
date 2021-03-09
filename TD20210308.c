/**
  \file      TD20210308.c
  \brief     read txt file char by char
  \author    Pierre BRESSY
  \version   1.0
  \date      2021-01-11 13:55:00
  \details

**/

#include <stdio.h>  // standard library for inputs and ouputs
#include <math.h>
int main(int argc, const char *argv[]) {

  const char *filename = "./data.csv";
  const char *mode = "r";

  FILE *fp = NULL;
  unsigned int count = 0;
  char c = ' ';

  fp = fopen(filename, mode);
  if(NULL==fp){
    printf("Error while opening %s\n", filename);
  }
  else {

    do {

      c = fgetc(fp); // read ONE character from file

      if(c!=EOF) {
        count++;
      }

      // count+= c==EOF ? 0 : 1
      
    } while (c!=EOF);

    printf("%u bytes.\n", count);

    if (0 != fclose(fp))
    {
      printf("Error while closing %s\n", filename);
    }
  }

  return 0;
}
