#include "dataset.h"
#include <vector>
#include <iostream>
#include <string>

int main(int argc, char* argv[]){
  Dataset set = Dataset::parseDatasetFile(argv[1]);
  std::vector<std::pair<double,double>> vec = set.determineLines(std::stod(argv[2]));
  std::cout << "Number of lines: " << vec.size() << std::endl;
  for (auto elem : vec){
    std::cout << "K-value: " << elem.first << " Length: "<< elem.second << std::endl;
  }
}
