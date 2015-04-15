#ifndef POINT_H
#define POINT_H

#include <cmath>
#include <utility>

class Point{
public:
  // Point(int index, double accumulatedAngle, double distance, double xCoord, double yCoord);

  Point(int index, double accumulatedAngle, double distance, double fieldOfView);

  int getIndex();
  double getAccumulatedAngle();
  double getDistance();
  double getXCoord();
  double getYCoord();
private:
  int index;
  double accumulatedAngle;
  double distance;
  double fieldOfView;
  double xCoord;
  double yCoord;

  /*std::pair<double,double>*/ void transform();
};



#endif
