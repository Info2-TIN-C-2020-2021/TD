/**
  \file      TD20210322.c
  \brief     write data to binary file
  \author    Pierre BRESSY
  \version   1.0
  \date      2021-03-22 16:00:00
  \details

**/

#include <stdio.h>  // standard library for inputs and ouputs
#include <stdint.h>
#include <math.h>

#define N 4

typedef struct {

  double x;
  double y;

} s2DCartesian;

int main(int argc, const char *argv[])
{
  const double pi = 3.141592654;
  const double radius = 1.0;
  const double deltaTheta = 2. * pi / N;
  s2DCartesian t[N] = {0};
  double theta = 0.;
  int index = 0;
  uint32_t numElements = N;
  int n = 0;
  FILE *f = NULL;
  char *filename = "data/data.bin";
  char *mode = "wb";

  for (index = 0; index < N;index++) {
    theta = deltaTheta * index;
    t[index].x = radius * cos(theta);
    t[index].y = radius * sin(theta);
  }

  for (index = 0; index < N;index++) {
    printf("%7.2lf %+.20lf %+.20lf\n",
           deltaTheta * index * 180 / pi, t[index].x, t[index].y);
  }

  f = fopen(filename, mode);
  if(NULL!=f) {
    n = fwrite(&numElements, sizeof(uint32_t), 1, f); // write header
    if(1!=n) {
      printf("error while writing header\n");
    }
    else {
      n = fwrite(t, sizeof(s2DCartesian), numElements, f);
      if(numElements!=n) {
        printf("error while writing data\n");
      }
    }
    if (fclose(f))
    {
        printf("error while closing file\n");
    }
  }
  else {
    printf("error while creating file\n");
  }

  return 0;
}


















  #if 0
#define N 9
typedef struct {
  double x;
  double y;
} s2DCartesian;

  const double pi = 3.141592654;
  s2DCartesian t[N];
  int index = 0;
  const double deltaTheta = 2 * pi / N;
  const double radius = 1.0;

  for (index = 0; index < N;index++) {
    t[index].x = radius * cos(index * deltaTheta);
    t[index].y = radius * sin(index * deltaTheta);
  }

  for (index = 0; index < N;index++) {
    printf("%+7.2lf  %+6.3lf %+6.3lf\n",180.*index * deltaTheta/pi,t[index].x,t[index].y);
  }

  char *filename = "data/data.bin";
  char *mode = "wb";
  FILE *f = NULL;

  f = fopen(filename, mode);

  if(!f) {
    printf("error while opening %s\n", filename);
  }
  else {
    sWavHeader h;
    fread(&h, sizeof(sWavHeader), 1, f);
    printf("%-20s: %s\n", "File",filename);
    printf("%-20s: %x\n", "chunkID",h.riff.chunkId);
    printf("%-20s: %u\n", "chunkSize",h.riff.chunkSize);
    printf("%-20s: %x\n", "format",h.riff.format);

    printf("%-20s: %x\n", "subChunk1Id",h.fmt.subChunk1Id);
    printf("%-20s: %u\n", "subChunk1Size",h.fmt.subChunk1Size);
    printf("%-20s: %u\n", "audioFormat",h.fmt.audioFormat);
    printf("%-20s: %u\n", "numChannels",h.fmt.numChannels);
    printf("%-20s: %u\n", "sampleRate",h.fmt.sampleRate);
    printf("%-20s: %u\n", "byteRate",h.fmt.byteRate);
    printf("%-20s: %u\n", "blockAlign",h.fmt.blockAlign);
    printf("%-20s: %u\n", "bitsPerSample",h.fmt.bitsPerSample);

    printf("%-20s: %u\n", "subChunk2Id",h.data.subChunk2Id);
    printf("%-20s: %u\n", "subChunk2Size",h.data.subChunk2Size);

    fclose(f);
  }
#endif
