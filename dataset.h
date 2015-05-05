#ifndef DATASET_H
#define DATASET_H

#include <unordered_map>
#include "point.h"
#include <string>

class Dataset {
public:
  Dataset(std::string name, int nbrPoints, double angleInc);
  void addPoint(Point p);

  void outputPlotFile(std::string dir);
  Dataset datasetInterval(double startAngle, double endAngle, double distance);

  void outputDatasetFile(std::string dir);
  static Dataset parseDatasetFile(std::string name);
  std::vector<std::pair<double,double>> Dataset::lerp(int points);
private:
  std::string name;
  int nbrPoints;
  double angleInc;
  std::unordered_map<int,Point> map;
};






#endif
