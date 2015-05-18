#include "line.h"


Line::Line(double k, double m, double length) : k(k),m(m),length(length) {}

double Line::getK(){
  return k;
}

double Line::getM(){
  return m;
}

double Line::getLength(){
  return length;
}
