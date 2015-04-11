#include "point.h"

Point::Point(int index, double accumulatedAngle, double distance, double xCoord, double yCoord) : index(index), accumulatedAngle(accumulatedAngle), distance(distance), xCoord(xCoord), yCoord(yCoord) {}


int Point::getIndex(){
  return index;
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
