/**
  \file      TD20210301.c
  \brief     for test
  \author    Pierre BRESSY
  \version   1.0
  \date      2021-01-11 13:55:00
  \details

**/

#include <stdio.h>  // standard library for inputs and ouputs

int main(int argc, const char *argv[]) {

  const char *filename = "toto/texte.txt";
  const char *mode = "w";

  FILE *fp = NULL;

  fp = fopen(filename, mode);
  if(NULL==fp){
    printf("Error while opening %s\n", filename);
  }
  else {
    //

    if(0!=fclose(fp)) {
      printf("Error while closing %s\n", filename);
    }
    else {
      printf("File %s created.\n", filename);
    }
  }

  return 0;
}
