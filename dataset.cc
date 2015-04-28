#include "dataset.h"
#include <fstream>
#include <iostream>
#include <math.h>

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


/*Kod för att plotta ut ett interval*/
Dataset Dataset::datasetInterval(double startAngle, double endAngle, double distance){

  // int startIndex = ceil(startAngle/angleInc);
  // int endIndex = ceil(endAngle/angleInc);
  int startIndex = ceil(startAngle/angleInc);
  int endIndex = ceil(endAngle/angleInc);
  if(endIndex<startIndex){
    std::cerr << "Invalid interval start: " << startAngle << " end: " << endAngle << std::endl;
  }

  Dataset set(name + "interval_start" + std::to_string(startIndex) + "end" + std::to_string(endIndex),endIndex-startIndex+1,angleInc);

  double newFieldOfView = endAngle - startAngle;

  //  std::cout << "StartIndex: " << startIndex << " | "<< "EndIndex: " << endIndex << std::endl;


  for(int i = startIndex; i<=endIndex;++i){
    Point p = map.find(i)->second;
    if (p.getDistance() <= distance){
      p.setIndex(i-startIndex);
      p.shiftAndTransform(-startAngle,0,newFieldOfView);
      set.addPoint(p);
    }
  }
  return set;
}
