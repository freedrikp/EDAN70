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

/*
Kod för att plotta ut ett interval
void Dataset::outputPlotFileInterval(std::string dir, double startAngle, double endAngle){
	std::ofstream file;
	int startIndex = ceil(startAngle/angleInc);
	int endIndex = floor(endAngle/angleInc);
	if(endIndex<startIndex)
		std:cerr << "Invalid interval start: " << startAngle << " end: " << endAngle << std::endl;
	
	file.open(dir + "/plot" + name + "start" + startAngle + "end" + endAngle + ".txt");
	if(file.is_open()){
		for(auto it = map.begin() + startIndex; it<=map.begin()+endIndex;it++){
			file << it.second.getXCoord() << " " << it.second.getYCoord() << std::endl;	
		}
	}else{
		std:cerr << "Could not open: " << dir  << "/plot" << name << "start"  << startAngle << "end" << endAngle << ".txt" << std::endl;
	}
*/

