#ifndef LINE_H
#define LINE_H

class Line {
public:
  Line(double k, double m, double length);
  double getK();
  double getM();
  double getLength();
private:
  double k;
  double m;
  double length;
};





#endif
