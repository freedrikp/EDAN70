#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include "parser.h"
#include "dataset.h"


int main(int argc, char* argv[]){
  std::cout << "Input: startAngle endAngle distance!" << std::endl;
  double startAngle;
  double endAngle;
  double distance;
  std::cin >> startAngle;
  std::cin >> endAngle;
  std::cin >> distance;
  std::ifstream file(argv[1]);

  std::vector<Dataset> vec = parseFile(file);


  for (Dataset set : vec){
    Dataset data = set.datasetInterval((startAngle/180)*atan(1)*4,(endAngle/180)*atan(1)*4,distance);
    data.outputPlotFile("plots",argv[2]);
    data.outputDatasetFile("datasets");
  }
}
