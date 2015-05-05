#ifndef POINT_H
#define POINT_H

#include <cmath>
#include <utility>

class Point{
public:
  // Point(int index, double accumulatedAngle, double distance, double xCoord, double yCoord);

  Point(int index, double accumulatedAngle, double distance, double fieldOfView);

  Point(const Point& p) = default;
  // Point& operator=(const Point& p) = delete;

  int getIndex();
  void setIndex(int index);
  double getAccumulatedAngle();
  double getDistance();
  double getXCoord();
  double getYCoord();
  double getFieldOfView();
  double distanceTo(Point p);
  void shiftAndTransform(double deltaAngle, double deltaDistance, double newFieldOfView);
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
