#ifndef LINE_H
#define LINE_H

class Line {
public:
  Line(double k, double m, double length);
  double getK() const;
  double getM() const;
  double getLength() const;
  bool operator==(const Line& rhs) const;
  bool operator!=(const Line& rhs) const;
private:
  double k;
  double m;
  double length;
};





#endif
