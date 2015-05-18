#include "line.h"


Line::Line(double k, double m, double length) : k(k),m(m),length(length) {}

double Line::getK() const{
  return k;
}

double Line::getM() const{
  return m;
}

double Line::getLength() const{
  return length;
}

bool Line::operator==(const Line& rhs) const{
  return rhs.getK() == k && rhs.getM() == m && rhs.getLength() == length;
}

bool Line::operator!=(const Line& rhs) const{
  return !operator==(rhs);
}
