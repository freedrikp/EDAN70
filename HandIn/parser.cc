#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include "point.h"
#include "parser.h"



Dataset parseDataset(std::string line, int lineNo){
  std::stringstream data(line);
  double floatval;
  long intval;
  data >> floatval; //unknown
  data >> floatval; //unknown
  int nbrPoints;
  data >> nbrPoints; //number of points
  data >> intval; //timestamp_sec
  data >> intval; //timestamp_micsec
  data >> floatval; //unknown
  data >> floatval; //unknown
  data >> floatval; //unknown
  data >> floatval; //unknown
  data >> floatval; //unknown
  data >> floatval; //unknown
  double angleInc;
  data >> angleInc; //angle_increment
  data >> floatval; //unknown
  data >> floatval; //unknown
  data >> floatval; //unknown
  Dataset set(std::to_string(lineNo),nbrPoints,angleInc);
  double fieldOfView = (nbrPoints - 1)*angleInc;
  double dist;
  int index = 0;
  while(data >> dist){
    Point p(index,index*angleInc,dist,fieldOfView);
    set.addPoint(p);
    ++index;
  }
  return set;
}

std::vector<Dataset> parseFile(std::ifstream& stream){
  std::vector<Dataset> vec;
  std::string line;
  bool correctAmount = true;
  int lineNo = 1;
  while (correctAmount && getline(stream,line)){
    Dataset set = parseDataset(line,lineNo);
    vec.push_back(set);
    ++lineNo;
  }
  return vec;
}
