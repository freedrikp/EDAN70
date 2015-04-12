#include "dataset.h"
#include <fstream>
#include <iostream>

Dataset::Dataset(std::string name, int nbrPoints, double angleInc) : name(name), nbrPoints(nbrPoints), angleInc(angleInc) {}

void Dataset::addPoint(Point p){
  map.insert(std::make_pair(p.getIndex(),p));
}

void Dataset::outputPlotFile(std::string dir){
  std::ofstream file;
  file.open(dir + "/plot" + name + ".txt");

  if (file.is_open()){
  for (auto elem : map){
    file << elem.second.getXCoord() << " " << elem.second.getYCoord() << std::endl;
  }

  file.flush();
  file.close();
}else{
  std::cerr << "Could not open: " << dir << "/plot" << name << ".txt" << std::endl;
}
}
