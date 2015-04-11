#ifndef POINT_H
#define POINT_H

class Point{
public:
  Point(int index, double accumulatedAngle, double distance, double xCoord, double yCoord);

  int getIndex();
  double getAccumulatedAngle();
  double getDistance();
  double getXCoord();
  double getYCoord();
private:
  int index;
  double accumulatedAngle;
  double distance;
  double xCoord;
  double yCoord;
};



#endif
