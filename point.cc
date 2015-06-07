#include "point.h"
#include <cmath>


void Point::transform(){
  double angle;
  int sign;
  if ((fieldOfView/2) > accumulatedAngle){
    angle = fieldOfView/2 - accumulatedAngle;
    sign = 1;
  }else{
    angle = accumulatedAngle - fieldOfView/2;
    sign = -1;
  }

  xCoord = sign*distance*sin(angle);
  yCoord = distance*cos(angle);
}

Point::Point(int index, double accumulatedAngle, double distance, double fieldOfView) : index(index), accumulatedAngle(accumulatedAngle), distance(distance), fieldOfView(fieldOfView) {

  transform();

}


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

double Point::calcK(Point p){
  return (yCoord-p.yCoord)/(xCoord-p.xCoord);
}

void Point::shiftAndTransform(double deltaAngle, double deltaDistance, double newFieldOfView){
  accumulatedAngle += deltaAngle;
  distance += deltaDistance;
  fieldOfView = newFieldOfView;
  transform();
}
