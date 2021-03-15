/**
  \file      TD20210315b.c
  \brief     structures
  \author    Pierre BRESSY
  \version   1.0
  \date      2021-01-11 13:55:00
  \details

**/

#include <stdio.h>  // standard library for inputs and ouputs
#include <math.h>

typedef struct {
  double x;
  double y;
  char *name;
} sPoint2D;

void displayPoint(sPoint2D p);
double computeDistance(sPoint2D p1,sPoint2D p2);

int main(int argc, const char *argv[]) {

  sPoint2D p1 = {2., 3., "P1"};
  sPoint2D p2 = {4., 2.1, "P2"};
  double dist = 0.;

  displayPoint(p1);
  displayPoint(p2);
  dist = computeDistance(p1,p2);
  printf("dist=%+6.3lf\n", dist);
  return 0;
}


void displayPoint(sPoint2D p) {
  printf("%s: (%+6.3lf,%+6.3lf)\n", p.name, p.x, p.y);
  return;
}

double computeDistance(sPoint2D p1,sPoint2D p2) {

  return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
}
