#include "dataset.h"
#include <vector>
#include <iostream>
#include <string>
#include <cmath>
#include <unordered_set>
#include <utility>

struct Hash {
      size_t operator()(const std::pair<double,double>& p) const {
          return std::hash<double>()(p.first * 31 + p.second);
      }
};

int main(int argc, char* argv[]){
  Dataset set = Dataset::parseDatasetFile(argv[1]);
  std::vector<std::pair<double,double>> vec = set.determineLines(std::stod(argv[2]));
  std::cout << "Attributes: " << std::endl;
  std::cout << "Number of lines: " << vec.size() << std::endl;
  double length = 0;
  int nbr_parallell = 0;
  int nbr_perpend = 0;



  std::unordered_set<std::pair<double,double>, Hash> already_checked_parallel;
  std::unordered_set<std::pair<double,double>, Hash> already_checked_perpend;


  for (auto elem : vec){
    std::cout << "K-value: " << elem.first << " Length: "<< elem.second << std::endl;
    length += elem.second;
    for(auto elem1 : vec){
    	//check if it is not current element
    	if(elem != elem1){
    		//calculate angle between lines
    		double angle = (std::atan(std::abs((elem.first - elem1.first)/(1 + (elem.first*elem1.first)))))*180/3.141592;
    		//if angle = 0 + error margin, and the line has not already been checked.
    		if(angle<(std::stod(argv[3])) && already_checked_parallel.find(elem) == already_checked_parallel.end()){
    			++nbr_parallell;
    			already_checked_parallel.insert(elem1);
    		//if the angle is perpendicualr + error margin and the line has not already been checked.
      }else if(angle>(90-std::stod(argv[4]))&& already_checked_parallel.find(elem) == already_checked_parallel.end()){
    			++nbr_perpend;
    			already_checked_perpend.insert(elem1);
    		}
    	}
    }
  }

  std::cout << "Mean length of lines: " << (length/vec.size()) << std::endl;

  std::cout << "Parallell lines: " << nbr_parallell << std::endl;

  std::cout << "Perpendicular lines: " << nbr_perpend << std::endl;
}
