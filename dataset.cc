#include "dataset.h"
#include <fstream>
#include <iostream>
#include <math.h>
#include <fstream>

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
  int endIndex = floor(endAngle/angleInc);
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

void Dataset::outputDatasetFile(std::string dir){
  std::ofstream file;
  file.open(dir + "/dataset" + name + ".txt");

  if (file.is_open()){
    file << name << std::endl;
    file << nbrPoints << std::endl;
    file << angleInc << std::endl;
    for (auto elem : map){
      file << elem.first << " " << elem.second.getAccumulatedAngle() << " " << elem.second.getDistance() << std::endl;
    }

    file.flush();
    file.close();
  }else{
    std::cerr << "Could not open: " << dir << "/plot" << name << ".txt" << std::endl;
  }
}

Dataset Dataset::parseDatasetFile(std::string name){
  std::ifstream file(name);
  if (file.is_open()){
    std::string name;
    int nbrPoints;
    double angleInc;
    file >> name;
    file >> nbrPoints;
    file >> angleInc;
    double fieldOfView = (nbrPoints - 1)*angleInc;
    Dataset set(name,nbrPoints,angleInc);
    for (int i = 0; i != nbrPoints; ++i){
      int index;
      double accumulatedAngle;
      double distance;
      file >> index;
      file >> accumulatedAngle;
      file >> distance;
      Point p(index,accumulatedAngle,distance,fieldOfView);
      set.addPoint(p);
    }
    file.close();
    return set;
  }else{
    throw "File could not be opened!";
  }
}


void Dataset::lerp(int points){

	std::vector<double> 
    for (int i = 0; i!= nbrPoints-1; ++i){

      file << elem.second.getXCoord() << " " << elem.second.getYCoord() << std::endl;
    }

}