#ifndef DATASET_H
#define DATASET_H

#include <unordered_map>
#include "attributes.h"
#include "point.h"
#include "line.h"
#include <string>
#include <vector>
#include <utility>

class Dataset {
public:
  Dataset(std::string name, int nbrPoints, double angleInc);
  void addPoint(Point p);

  void outputPlotFile(std::string dir, std::string fileName);
  Dataset datasetInterval(double startAngle, double endAngle, double distance);

  void outputDatasetFile(std::string dir);
  static Dataset parseDatasetFile(std::string name);
  std::vector<Line> determineLines(double threshold);
  Attributes lineAttributes(double err1, double err2, double err3);
  std::vector<std::pair<double,double>> lerp(int points);
private:
  std::string name;
  int nbrPoints;
  double angleInc;
  std::unordered_map<int,Point> map;
};






#endif
