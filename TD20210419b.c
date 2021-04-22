/**
  \file      TD20210419.c
  \brief     read txt file to string (with memory allocation)
  \author    Pierre BRESSY
  \version   1.0
  \date      2021-04-19 14:45:00
  \details

**/

#include <stdio.h>  // standard library for inputs and ouputs
#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h> // for malloc / free

int main(int argc, char const *argv[])
{
  FILE *f = NULL;
  const char *filename = "info.txt";
  const char *mode = "r";
  long n = 0;
  char *s = NULL;
  uint32_t wc = 0;
  bool inWord = false;
  uint32_t index = 0;

  f = fopen(filename, mode);
#if 0
  n = ftell(f);
  printf("n=%ld\n", n);
  char c = fgetc(f);
  n = ftell(f);
  printf("n=%ld\n", n);
  c = fgetc(f);c = fgetc(f);c = fgetc(f);
  n = ftell(f);
  printf("n=%ld\n", n);
#endif

  if(NULL!=f) {

    fseek(f, 0, SEEK_END); // reading index at the end of file
    n = ftell(f);
    printf("file size=%ld bytes\n", n);

    s = (char *)malloc((n+1) * sizeof(char)); // +1 for '\0'
    if(s!=NULL) {
      rewind(f); // reading index at the beginning of file
      fgets(s, n + 1, f);
      printf("s=[%s]\n", s);

      for (index = 0; index < n;index++) {
        if(!inWord && s[index]!=' ') { // detect beginning of a word
          inWord = true;
          wc++;
        }
        else if(inWord && s[index]==' ') { // detect end of a word
          inWord = false;
        }
      }
      printf("%d word%s in the string.\n", wc, wc > 1 ? "s" : "");

      free(s);
      s = NULL;
    }
    else {
      printf("Error while allocating %ld bytes\n", n + 1);
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


