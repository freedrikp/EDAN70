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



void doLineTest(std::ofstream& file, char* argv[], std::string name){
  Dataset set = Dataset::parseDatasetFile(name);
  Attributes attributes = set.lineAttributes(std::stod(argv[2]),std::stod(argv[3]),std::stod(argv[4]));

  file << attributes.getNbrLines() << "," << attributes.getMeanLength() << "," << attributes.getPerpendicular() << "," << attributes.getParallell() << "," << argv[1] << std::endl;
}

int main(int argc, char* argv[]){

  std::ofstream file("arff.arff");

  file << "@relation arff" << std::endl;
  file << "@attribute " << Attributes::NBR_LINES << " real" << std::endl;
  file << "@attribute " << Attributes::MEAN_LENGTH << " real" << std::endl;
  file << "@attribute " << Attributes::PERPENDICULAR << " real" << std::endl;
  file << "@attribute " << Attributes::PARALLELL << " real" << std::endl;
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
