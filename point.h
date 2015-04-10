#ifndef POINT_H
#define POINT_H

class Point{
public:
  Point(double accumulatedAngle, double distance, double xCoord, double yCoord);
private:
  double accumulatedAngle;
  double distance;
  double xCoord;
  double yCoord;
};



#endif
