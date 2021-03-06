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



void doLineTest(std::ofstream& file, char* argv[], std::string name, std::string classification){
  Dataset set = Dataset::parseDatasetFile(name);
  Attributes attributes = set.lineAttributes(std::stod(argv[1]),std::stod(argv[2]),std::stod(argv[3]));

  file << attributes.getNbrLines() << "," << attributes.getMeanLength() << "," << attributes.getPerpendicular() << "," << attributes.getParallell() << "," << classification << std::endl;
}

int main(int argc, char* argv[]){
  std::string fileName = std::string("arff-") + argv[1] + "m-" + argv[2] + "-" + argv[3] + ".arff";
  std::ofstream file(fileName);

  file << "@relation arff" << std::endl;
  file << "@attribute " << Attributes::NBR_LINES << " real" << std::endl;
  file << "@attribute " << Attributes::MEAN_LENGTH << " real" << std::endl;
  file << "@attribute " << Attributes::PERPENDICULAR << " real" << std::endl;
  file << "@attribute " << Attributes::PARALLELL << " real" << std::endl;
  file << "@attribute isdoor {yes, no}" << std::endl;
  file << "@data" << std::endl;

  DIR *dir;
  struct dirent *ent;

  if ((dir = opendir ("yes")) != NULL) {
    while ((ent = readdir (dir)) != NULL) {
      if (ent->d_name[0] == '.'){
        continue;
      }
      std::cout << ent->d_name << std::endl;
      doLineTest(file, argv,std::string("yes") + "/" + ent->d_name,"yes");
    }
  } else {
    perror ("");
    return EXIT_FAILURE;
  }
  closedir (dir);

  if ((dir = opendir ("no")) != NULL) {
    while ((ent = readdir (dir)) != NULL) {
      if (ent->d_name[0] == '.'){
        continue;
      }
      std::cout << ent->d_name << std::endl;
      doLineTest(file, argv,std::string("no") + "/" + ent->d_name,"no");


    }
    closedir (dir);
    
  } else {
    perror ("");
    return EXIT_FAILURE;
  }

}
