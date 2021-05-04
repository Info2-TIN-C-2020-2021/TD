/**
  \file      TD20210419.c
  \brief     Memory allocation
  \author    Pierre BRESSY
  \version   1.0
  \date      2021-03-29 13:15:00
  \details

**/

#include <stdio.h>  // standard library for inputs and ouputs
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "wav.h"

#define MAX_LINE_LENGTH 100

typedef struct {
  int16_t left;
  int16_t right;

} sStereoSample;



int writeOutput(sStereoSample *area, const double fs, const uint32_t numSamples) {

  int returnCode = 0;
  const char *filename = "output.wav";
  const char *mode = "wb";
  FILE *fOut = NULL;
  sWavHeader h;

  // 1. prepare header
  wavPrepareHeader(&h, E_STEREO, fs, numSamples, E_16B_SAMPLE);
  // 2. create file
  fOut = fopen(filename, mode);
  if(fOut!=NULL) {

    // 3. write header
    if(1!=fwrite(&h, sizeof(sWavHeader),1, fOut)) {
      printf("Error while writing header to %s\n", filename);
      returnCode = -1;
    }
    // 4. write data
    if(numSamples!=fwrite(area, sizeof(sStereoSample),numSamples, fOut)) {
      printf("Error while writing data to %s\n", filename);
      returnCode = -1;
    }
    // 5. close file
    if(0!=fclose(fOut)) {
      printf("Error while closing %s\n", filename);
      returnCode = -1;
    }  
  }
  else {
    printf("Error while creating %s\n", filename);
    returnCode = -1;
  }

  return returnCode;
}



int getWavData(const char *filename, sStereoSample *area) {

  int returnCode = 0;
  const char *mode = "rb";
  FILE *fIn = NULL;
  sWavHeader h;
  uint32_t numSamples = 0;

  fIn = fopen(filename, mode);
  if(NULL!=fIn) {
    if(1==fread(&h, sizeof(sWavHeader), 1, fIn)) {

      numSamples = h.data.length / h.format.bytesPerSample;
      if(numSamples!=fread(area, sizeof(sStereoSample), numSamples, fIn)) {
        printf("Error while reading data of %s\n", filename);
        returnCode = -1;
      }

    }
    else {
      printf("Error while reading header of %s\n", filename);
      returnCode = -1;
    }

    if(0!=fclose(fIn)) {
      printf("Error while clsing %s\n", filename);
      returnCode = -1;
    }
  }
  else {
    printf("Error while opening %s\n", filename);
    returnCode = -1;
  }
  return returnCode;
}



int getWavInfo(const char *filename, uint32_t *fs, uint32_t *numSamples) {

  int returnCode = 0;
  const char *mode = "rb";
  FILE *fIn = NULL;
  sWavHeader h;

  fIn = fopen(filename, mode);
  if(NULL!=fIn) {

    if(1==fread(&h, sizeof(sWavHeader), 1, fIn)) {

      *fs = h.format.samplingRate;
      *numSamples = h.data.length / h.format.bytesPerSample;
    }
    else {
      printf("Error while reading header of %s\n", filename);
      returnCode = -1;
    }
    if(0!=fclose(fIn)) {
      printf("Error while closing %s\n", filename);
      returnCode = -1;
    }
  }
  else {
    printf("Error while opening %s\n", filename);
    returnCode = -1;
  }
  return returnCode;
}


int main(int argc, char const *argv[])
{
  const char *filename = "melody.txt";
  const char *mode = "r";
  FILE *fIn = NULL;
  char s[MAX_LINE_LENGTH];
  uint32_t fs = 0;
  uint32_t numSamples = 0;
  sStereoSample *t = NULL;
  sStereoSample *newT = NULL;
  uint32_t totalNumSamples = 0;

  fIn = fopen(filename, mode);
  if(NULL!=fIn) {

    while(!feof(fIn)) {
      fgets(s, MAX_LINE_LENGTH, fIn); // read one line at a time
      if(strchr(s,'\n')) { // remove \n if any
        s[strlen(s) - 1] = '\0';
      }
      printf("%s\t", s); // s is the filename of the wav file to process
      if(getWavInfo(s, &fs, &numSamples)) {
        printf("Error while getting wave info for %s\n", s);
      }
      printf("%6u[Hz] %6u[samples]\n", fs, numSamples);

      totalNumSamples += numSamples;
      newT=(sStereoSample*)realloc(t, totalNumSamples * sizeof(sStereoSample));
      if(newT==NULL) {
        printf("Error while reallocating %lu bytes.\n", totalNumSamples * sizeof(sStereoSample));
      }
      else {
        t = newT;

        // lire les données du .wav et le copier dans t (à la bonne position)
        //getWavData(s, &t[totalNumSamples - numSamples]); // ok
        if(getWavData(s, t + totalNumSamples - numSamples)) {
          printf("Error while getting wave data for %s\n", s);
        }
      }
    }
    printf("totalNumSamples=%u\n", totalNumSamples);

    /*for (uint32_t k = 0; k < totalNumSamples;k+=10000){
       printf("%8hd %8hd\n", t[k].left, t[k].right);
    }*/

    if(writeOutput(t, fs, totalNumSamples)) {
      printf("Error while writing output wav file.\n");
    }

    if (t != NULL)
    {
      free(t);
      t = NULL;
    }

    if(0!=fclose(fIn)) {
      printf("Error while closing %s\n", filename);
    }
  }
  else {
    printf("Error while opening %s\n", filename);
  }

  return 0;
}


