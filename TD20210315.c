/**
  \file      TD20210315.c
  \brief     structures
  \author    Pierre BRESSY
  \version   1.0
  \date      2021-01-11 13:55:00
  \details

**/

#include <stdio.h>  // standard library for inputs and ouputs
#include <math.h>

void displayPoint(const char *name, const double x, const double y);
double computeDistance(const double x1, const double y1,const double x2, const double y2);

int main(int argc, const char *argv[]) {

  double x1 = 2.;
  double y1 = 3.;
  double x2 = 4.;
  double y2 = 2.1;
  double dist = 0.;

  displayPoint("P1", x1, y1);
  displayPoint("P2", x2, y2);
  dist = computeDistance(x1, y1, x2, y2);
  printf("dist=%+6.3lf\n", dist);
  return 0;
}


void displayPoint(const char *name, const double x, const double y){
  printf("%s: (%+6.3lf,%+6.3lf)\n", name, x, y);
  return;
}

double computeDistance(const double x1, const double y1,const double x2, const double y2) {

  return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}
