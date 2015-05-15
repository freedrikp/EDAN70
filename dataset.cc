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
  int endIndex = floor(endAngle/angleInc);
  if(endIndex<startIndex){
    std::cerr << "Invalid interval start: " << startAngle << " end: " << endAngle << std::endl;
  }

  Dataset set(name + "interval_start" + std::to_string(startIndex) + "end" + std::to_string(endIndex),endIndex-startIndex+1,angleInc);

  double newFieldOfView = endAngle - startAngle;

  //  std::cout << "StartIndex: " << startIndex << " | "<< "EndIndex: " << endIndex << std::endl;
  int index = 0;
  for(int i = startIndex; i<=endIndex;++i){
    Point p = map.find(i)->second;
    if (p.getDistance() <= distance){
      p.setIndex(index);
      ++index;
      p.shiftAndTransform(-startAngle,0,newFieldOfView);
      set.addPoint(p);
    }
  }
  set.nbrPoints = index;
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
      file << elem.first << " " << elem.second.getAccumulatedAngle() << " " << elem.second.getDistance() << " " << elem.second.getFieldOfView() <<  std::endl;
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
    Dataset set(name,nbrPoints,angleInc);
    for (int i = 0; i != nbrPoints; ++i){
      int index;
      double accumulatedAngle;
      double distance;
      double fieldOfView;
      file >> index;
      file >> accumulatedAngle;
      file >> distance;
      file >> fieldOfView;
      Point p(index,accumulatedAngle,distance,fieldOfView);
      set.addPoint(p);
    }
    file.close();
    return set;
  }else{
    throw "File could not be opened!";
  }
}

std::vector<std::pair<double,double>> Dataset::lerp(int points){

  std::unordered_map<int,double> cal;
  double distance = 0;
  cal.insert({0,distance});
  for (int i = 0; i!= map.size()-1; ++i){
    distance += map[i].distanceTo(map[i+1]);
    cal.insert({i+1,distance});
  }

  unsigned beg = 0;
  unsigned end = 1;
  double distIncrement = distance/points;
  std::vector<std::pair<double,double>> list;
  for(double i = 0; i!= distance; i += distIncrement){
    double lower = cal[beg];
    double higher = cal[end];
    double x;
    double y;
    if(lower<i && i<higher){
      /*make new point in data structure*/
      double progress = (i-lower)/(higher-lower);
      x = map[beg].getXCoord()*progress;
      y = map[beg].getYCoord()*progress;
      list.push_back(std::make_pair(x,y));
    }else if(lower == i){
      /*point is equal to map[beg]*/
      x = map[beg].getXCoord();
      y = map[beg].getYCoord();
      list.push_back(std::make_pair(x,y));
    }else if(higher == i){
      /*point is equal to map[end]*/
      x = map[end].getXCoord();
      y = map[end].getYCoord();
      list.push_back(std::make_pair(x,y));
    }else{
      while(end<cal.size()-1 && i>higher){
        ++beg;
        ++end;
      }
    }
  }
  return list;
}
