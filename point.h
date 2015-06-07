#ifndef POINT_H
#define POINT_H


class Point{
public:
  Point(int index, double accumulatedAngle, double distance, double fieldOfView);

  Point(const Point& p) = default;
  Point() = default;

  int getIndex();
  void setIndex(int index);
  double getAccumulatedAngle();
  double getDistance();
  double getXCoord();
  double getYCoord();
  double getFieldOfView();
  double distanceTo(Point p);
  double calcK(Point p);
  void shiftAndTransform(double deltaAngle, double deltaDistance, double newFieldOfView);
private:
  int index;
  double accumulatedAngle;
  double distance;
  double fieldOfView;
  double xCoord;
  double yCoord;

  void transform();
};



#endif
