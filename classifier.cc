#include "dataset.h"
#include "attributes.h"
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>


int main(int argc, char* argv[])
{
  Dataset set = Dataset::parseDatasetFile(argv[2]);
  Attributes attributes = set.lineAttributes(std::stod(argv[3]), std::stod(argv[4]), std::stod(argv[5]));
  
  
  std::ifstream file(argv[1]);
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
			std::cout << output << std::endl;
			break;
		}
			
	}
	return 0;
	
}
