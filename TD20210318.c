/**
  \file      TD20210318.c
  \brief     wav header
  \author    Pierre BRESSY
  \version   1.0
  \date      2021-03-18 16:00:00
  \details

**/

#include <stdio.h>  // standard library for inputs and ouputs
#include <stdint.h>

typedef struct {

  uint32_t chunkId;
  uint32_t chunkSize;
  uint32_t format;
  uint8_t x;
} sTestWithPadding;

#pragma pack (1)
typedef struct {

  uint32_t chunkId;
  uint32_t chunkSize;
  uint32_t format;
} sRiff;

typedef struct {

  uint32_t chunkId;
  uint32_t chunkSize;
  uint32_t format;
  uint8_t x;
} sTestNoPadding;

typedef struct {

  uint32_t subChunk1Id;
  uint32_t subChunk1Size;
  uint16_t audioFormat;
  uint16_t numChannels;
  uint32_t sampleRate;
  uint32_t byteRate;
  uint16_t blockAlign;
  uint16_t bitsPerSample;

} sFmt;

typedef struct {

  uint32_t subChunk2Id;
  uint32_t subChunk2Size;

} sData;

typedef struct {

  sRiff riff;
  sFmt  fmt;
  sData data;

} sWavHeader;
#pragma pack (0)

int main(int argc, const char *argv[])
{
    char *filename = "data/42s.wav";
  char *mode = "rb";
  FILE *f = NULL;

  printf("size of sRiff:      %ld\n", sizeof(sRiff));
  printf("size of sFmt:       %ld\n", sizeof(sFmt));
  printf("size of sData:      %ld\n", sizeof(sData));
  printf("size of sWavHeader: %ld\n", sizeof(sWavHeader));
  printf("size of sTestWithPadding: %ld\n", sizeof(sTestWithPadding));
  printf("size of sTestNoPadding:   %ld\n", sizeof(sTestNoPadding));
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
  return 0;
}
