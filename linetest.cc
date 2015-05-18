#include "dataset.h"
#include <vector>
#include <iostream>
#include <string>
#include <cmath>
#include <unordered_set>
#include <utility>
#include "line.h"
#include <fstream>
#include <dirent.h>
#include <cstring>

struct Hash {
  size_t operator()(const Line& line) const {
    return std::hash<double>()(line.getK() * 31 + line.getM() * 17 + line.getLength());
  }
};

void doLineTest(std::ofstream& file, char* argv[], std::string name){
  Dataset set = Dataset::parseDatasetFile(name);
  std::vector<Line> vec = set.determineLines(std::stod(argv[2]));
  std::cout << "Attributes: " << std::endl;
  std::cout << "Number of lines: " << vec.size() << std::endl;
  double length = 0;
  int nbr_parallell = 0;
  int nbr_perpend = 0;



  std::unordered_set<Line, Hash> already_checked_parallel;
  std::unordered_set<Line, Hash> already_checked_perpend;


  for (auto elem : vec){
    std::cout << "K-value: " << elem.getK() << " M-value: " << elem.getM() << " Length: "<< elem.getLength() << std::endl;
    length += elem.getLength();
    for(auto elem1 : vec){
      //check if it is not current element
      if(elem != elem1){
        //calculate angle between lines
        double angle = (std::atan(std::abs((elem.getK() - elem1.getK())/(1 + (elem.getK()*elem1.getK())))))*180/3.141592;
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

  file << vec.size() << "," << (length/vec.size()) << "," << nbr_perpend << "," << nbr_parallell << "," << argv[1] << std::endl;
}

int main(int argc, char* argv[]){

  std::ofstream file("arff.arff");

  file << "@relation arff" << std::endl;
  file << "@attribute nbrOfLines real" << std::endl;
  file << "@attribute avgLength real" << std::endl;
  file << "@attribute perpendicular real" << std::endl;
  file << "@attribute parallell real" << std::endl;
  file << "@attribute isdoor {yes, no}" << std::endl;
  file << "@data" << std::endl;

  DIR *dir;
  struct dirent *ent;
  if ((dir = opendir (argv[1])) != NULL) {
    /* print all the files and directories within directory */
    while ((ent = readdir (dir)) != NULL) {
      if (ent->d_name[0] == '.'){
        continue;
      }
      std::cout << ent->d_name << std::endl;
      doLineTest(file, argv,std::string(argv[1]) + "/" + ent->d_name);


    }
    closedir (dir);
  } else {
    /* could not open directory */
    perror ("");
    return EXIT_FAILURE;
  }








}
