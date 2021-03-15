/**
  \file      TD20210315c.c
  \brief     structure, point 2D cartesian and polar
  \author    Pierre BRESSY
  \version   1.0
  \date      2021-01-11 13:55:00
  \details

**/

#include <stdio.h>  // standard library for inputs and ouputs
#include <math.h>  // standard library for math computation


typedef struct {
  double x;
  double y;
} sCartesian;

typedef struct {
  double rho;
  double theta;
} sPolar;


void displayPointCartesian(const sCartesian p);
void displayPointPolar(const sPolar p);
sPolar c2p(const sCartesian c);

void displayPointCartesian(const sCartesian p) {
  printf("x=%+6.3lf, y=%+6.3lf\n", p.x, p.y);
  return;
}

void displayPointPolar(const sPolar p) {
  printf("r=%+6.3lf, theta=%+6.3lf°\n", p.rho, p.theta);
  return;
}

sPolar c2p(const sCartesian c) {
  sPolar p;
  const double pi = 3.141592654;
  p.rho = sqrt(pow(c.x, 2) + pow(c.y, 2));
  p.theta = 180.*atan2(c.y, c.x)/pi;
  return p;
}

int main(int argc, const char *argv[])
{
  sCartesian p1 = {2., 3.};
  sPolar p2 = {0.,0.};
  
  displayPointCartesian(p1);
  p2 = c2p(p1);
  displayPointPolar(p2);
  return 0;
}
