/**
  \file      TD20210510.c
  \brief     bitmap file
  \author    Pierre BRESSY
  \version   1.0
  \date      2021-05-10 13:15:00
  \details

**/

#include <stdio.h>  // standard library for inputs and ouputs
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>
#include "bitmap.h"

int main(int argc, char const *argv[])
{
  const char *filename = "data/face.bmp";
  const char *mode = "rb";
  FILE *f = NULL;
  int32_t height = 0;
  int32_t width = 0;
  int ret = 0;
  sBitmapFileHeader fileHeader;
  sBitMapInfoHeader infoHeader;
  sRGB pixel;
  uint32_t count = 0;
  uint32_t whitePixelsCount = 0;

  f = fopen(filename, mode);
  if(NULL!=f) {

    ret = fread(&fileHeader, sizeof(sBitmapFileHeader), 1, f);
    ret += fread(&infoHeader, sizeof(sBitMapInfoHeader), 1, f);

    if(2==ret) {

      height = infoHeader.biHeight;
      width = infoHeader.biWidth;

      printf("Image size : %3d rows x %3d cols.\n", height, width);

      for (count = 0; count < 3;count++) {
        ret=fread(&pixel, sizeof(sRGB),1,f);
        if(ret==1) {
          printf("%3d %3d %3d\n", pixel.R, pixel.G, pixel.B);
        }
        else {
          printf("Error while reading data of %s\n", filename);
        }
      }

      // count white pixels
      fseek(f, sizeof(sBitmapFileHeader)+sizeof(sBitMapInfoHeader), SEEK_SET);
      for (count = 0; count < width*height; count++)
      {
        ret = fread(&pixel, sizeof(sRGB), 1, f);
        if(ret==1){
          if( pixel.R>127 && pixel.G>127 && pixel.B>127) {
            whitePixelsCount++;
          }
        }
        else {
          printf("Error while reading data from %s\n", filename);
        }
      }
      printf("%u white pixels.\n", whitePixelsCount);

    }
    else {
      printf("Error while reading header of %s\n", filename);
    }

    if(0!=fclose(f))
    {
      printf("Error while closing file %s\n", filename);
    }
  }
  else {
    printf("Error while opening file %s\n", filename);
  }

  return 0;
}

