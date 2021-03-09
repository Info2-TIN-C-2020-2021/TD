/**
  \file      TD20210308c.c
  \brief     enumerated types
  \author    Pierre BRESSY
  \version   1.0
  \date      2021-01-11 13:55:00
  \details

**/

#include <stdio.h>  // standard library for inputs and ouputs
#include <string.h>

typedef enum
{
  BLACK=0,
  WHITE=1,
  RED=2,
  GREEN=3,
  BLUE=4,
  YELLOW=5,
  BROWN, // 6 
  GRAY   // 7

} eColor;


int main(int argc, const char *argv[]) {

  eColor c1=RED;
  eColor c2 = GREEN;

  printf("c1=%d\n", c1);
  printf("c2=%d\n", c2);

  return 0;
}

