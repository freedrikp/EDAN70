#include "dataset.h"
#include "attributes.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

void classify(std::string treeFile, Attributes attributes){
	std::ifstream file(treeFile);
	std::string line;
	std::string next = "";
	while (std::getline(file,line)){
		std::istringstream stream(line);
		std::string firstWord;
		stream >> firstWord;
		if(!next.empty() && next != firstWord){
			continue;
		}
		char ch;
		stream >> ch;
		stream >> ch;
		double value;
		if ( ch == '<' ){
			stream >> ch;
			stream >> value;
			double attrValue = attributes.getValueOfAttr(firstWord);
			if(attrValue > value){
				next = firstWord;
				continue;
			}
			stream >> ch;
		}else if(ch == '>'){
			stream >> value;
			double attrValue = attributes.getValueOfAttr(firstWord);
			if(attrValue <= value){
				next = firstWord;
				continue;
			}
		}
		stream >> ch;
		if(stream.good() && ch == ':'){
			std::string output;
			stream >> output;
			std::cout << "result: " << output << std::endl;
			break;
		}else{
			next = "";
		}
			
	}
	std::cout << "loop done" << std::endl;
}

int main(int argc, char* argv[]){
  if (argc != 6){
	std::cout << "Usage: Tree-file Dataset-file Line-tolerance Parallel-tolerance Perpendicular-tolerance" << std::endl;
	  exit(1);
  }
  Dataset set = Dataset::parseDatasetFile(argv[2]);
  Attributes attributes = set.lineAttributes(std::stod(argv[3]), std::stod(argv[4]), std::stod(argv[5]));
  classify(argv[1], attributes);
  return 0;
	
}
