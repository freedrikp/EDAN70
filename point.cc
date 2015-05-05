#include "point.h"
#include <cmath>


/*std::pair<double,double>*/ void Point::transform(){
double angle;
int sign;
if ((fieldOfView/2) > accumulatedAngle){
  angle = fieldOfView/2 - accumulatedAngle;
  sign = 1;
}else{
  angle = accumulatedAngle - fieldOfView/2;
  sign = -1;
}
// double x = sign*distance*sin(angle);
// double y = distance*cos(angle);
// return std::make_pair(x,y);
xCoord = sign*distance*sin(angle);
yCoord = distance*cos(angle);
}

Point::Point(int index, double accumulatedAngle, double distance, double fieldOfView) : index(index), accumulatedAngle(accumulatedAngle), distance(distance), fieldOfView(fieldOfView) {

  /*std::pair<double,double> coords =*/ transform();
  //xCoord = coords.first;
  //yCoord = coords.second;

}

// Point::Point(const Point& p) : index(p.index), accumulatedAngle(p.accumulatedAngle), distance(p.distance), fieldOfView(p.fieldOfView), xCoord(p.xCoord), yCoord(p.yCoord) {}

// Point::Point(int index, double accumulatedAngle, double distance, double xCoord, double yCoord) : index(index), accumulatedAngle(accumulatedAngle), distance(distance), xCoord(xCoord), yCoord(yCoord) {}


int Point::getIndex(){
  return index;
}

void Point::setIndex(int index){
  this->index = index;
}

double Point::getAccumulatedAngle(){
  return accumulatedAngle;
}

double Point::getDistance(){
  return distance;
}

double Point::getXCoord(){
  return xCoord;
}

double Point::getYCoord(){
  return yCoord;
}

double Point::getFieldOfView(){
  return fieldOfView;
}

double Point::distanceTo(Point p){
  return sqrt(pow(p.xCoord-xCoord,2)+pow(p.yCoord- yCoord,2));
}

void Point::shiftAndTransform(double deltaAngle, double deltaDistance, double newFieldOfView){
  accumulatedAngle += deltaAngle;
  distance += deltaDistance;
  fieldOfView = newFieldOfView;
  transform();
}
