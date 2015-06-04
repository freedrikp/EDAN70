#include "dataset.h"
#include "line.h"
#include <fstream>
#include <iostream>
#include <cmath>
#include <unordered_set>

struct Hash {
  size_t operator()(const Line& line) const {
    return std::hash<double>()(line.getK() * 31 + line.getM() * 17 + line.getLength());
  }
};

Dataset::Dataset(std::string name, int nbrPoints, double angleInc) : name(name), nbrPoints(nbrPoints), angleInc(angleInc) {}

void Dataset::addPoint(Point p){
  map.insert(std::make_pair(p.getIndex(),p));
}

void Dataset::outputPlotFile(std::string dir, std::string fileName){
  std::ofstream file;
  name = std::string(fileName) + name;
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

std::vector<Line> Dataset::determineLines(double threshold){
	/*Har tweakat denna metoden lite för att få ut bättre resultat. Jag har testat den mot ett
	par olika inputs och det verkar som den får rätt bra resultat även på rätt noisy inputfiler.

	Det jag har gjort är att jämföra vinkeln mellan två olika linjer som är bestämmda från startpunkt->första punkten
	och startpunkt -> andra punkten, vinkeln (låt oss kalla den v) mellan dessa måste vara mindre än threshold.
	Dock har jag lagt till att beroende på anvståndet från orginalpunkten så har vi större felmarginal att röra oss på.
	Dvs avståndet från start * err(v) < threshold. Och det verkar som detta ger ett väldigt bra resultat.
	Har inte kollat matten för det men jag tror det kan vara en bra approximering till regression.

	Förutom detta så uppdaterar jag startK varje iteration för att få en bättre approximerig till linjen,
	detta är helt enkelt medelvärdet för de två dvs: startK =(startK + newK)/2 (detta händer enbart om det är under threshold).
	*/
	std::vector<Line> lineVector;
	unsigned start = 0;
	Point startPoint = map[start];
	bool done = false;
	while(!done){
		unsigned index = 1;
		if(start+index >= map.size()){
			done = true;
			break;
		}
		Point p1 = map[start+index];
		if(p1.distanceTo(startPoint)>0.3){
			start++;
			startPoint = p1;
			continue;
		}
		double startK = startPoint.calcK(p1);
		bool isLine = true;
    double errLimit = threshold;
    std::cout << "---------------------------------------------------------------------------------" << std::endl;
    std::cout << "---------------------------------------------------------------------------------" << std::endl;
		while(isLine){
			++index;
			if(start+index >= map.size()){
				done = true;
				break;
			}
			Point p2 = map[start+index];
			if(p2.distanceTo(p1)>0.3){
				isLine = false;
				break;
			}
			double m = startPoint.getYCoord() - startK*startPoint.getXCoord();
			double mountain = (p2.getYCoord()-m)/startK + errLimit;
			double valley = (p2.getYCoord()-m)/startK - errLimit;
			double upper = startK * p2.getXCoord() + m + errLimit;
			double lower = startK * p2.getXCoord() + m - errLimit;
			if(lower>upper){
				double temp = upper;
				upper = lower;
				lower = temp;
			}
			if(valley>mountain){
				double temp = mountain;
				mountain = valley;
				valley = temp;
			}
			double dist = startPoint.distanceTo(p2);
			double newK = startPoint.calcK(p2);
			//double newK = p1.calcK(p2);
			//double err = (std::atan(std::abs((newK - startK)/(1 + (newK*startK)))))*180/3.141592;
      //std::cout << "Error: " << err*dist*10 << " point: " << start-index << " Angle: " << (std::atan(std::abs((newK - startK)/(1 + (newK*startK)))))*180/3.141592 << "dist: " << dist << std::endl;
			std::cout << "lower: " << lower << " ycoord: " << p2.getYCoord() << " upper: " << upper << " valley " << valley << " mountain " << mountain << std::endl;
			std::cout << "start: " << start << " next point: " << start+index << " startK: " << startK << " newK: " << newK /*<< " newStartK: " << val*/ << std::endl;
			if(lower<=p2.getYCoord() && p2.getYCoord()<=upper || valley<=p2.getXCoord() && p2.getXCoord() <= mountain){
				double w = 1.0/index;
				double val = (1-w)*startK + w*newK;
				startK = val;
				// errLimit-=err;
				/*handle line adding*/
			}else{
				isLine = false;
				break;
			}
			p1 = p2;
		}
		/*add lines to datastructure*/
		double length = startPoint.distanceTo(p1);
		if(length>0.25 && index>3){
			double m = startPoint.getYCoord() - startPoint.getXCoord() * startK;
			Line l(startK,m,length);
			lineVector.push_back(l);
			std::cout << "----------------added line----------" << std::endl;
		}
			std::cout << "length: " << length << " nbr points: " << index << std::endl;
		start += index-1;
		startPoint = p1;
	}
	return lineVector;
}

Attributes Dataset::lineAttributes(double err1, double err2, double err3){
  std::vector<Line> vec = determineLines(err1);
  //std::cout << "Attributes: " << std::endl;
  //std::cout << "Number of lines: " << vec.size() << std::endl;
  double length = 0;
  int nbr_parallell = 0;
  int nbr_perpend = 0;



  std::unordered_set<Line, Hash> already_checked_parallel;
  std::unordered_set<Line, Hash> already_checked_perpend;


  for (auto elem : vec){
    std::cout << "K-value: " << elem.getK() << " M-value: " << elem.getM() << " Angle: " << atan(elem.getK())*360/(2*3.141592) << " Length: "<< elem.getLength() << std::endl;
    length += elem.getLength();
		bool firstPara = true;
		bool firstPerpend = true;
    for(auto elem1 : vec){
      //check if it is not current element
      if(elem != elem1){
        //calculate angle between lines
        double angle = (std::atan(std::abs((elem.getK() - elem1.getK())/(1 + (elem.getK()*elem1.getK())))))*180/3.141592;
        //if angle = 0 + error margin, and the line has not already been checked.
        if(angle<err2 && already_checked_parallel.find(elem) == already_checked_parallel.end() && already_checked_parallel.find(elem1) == already_checked_parallel.end()){
          ++nbr_parallell;
          already_checked_parallel.insert(elem1);
			if(firstPara){
				++nbr_parallell;
				firstPara = false;
			}
          //if the angle is perpendicualr + error margin and the line has not already been checked.
        }else if(angle>(90-err3) && already_checked_perpend.find(elem) == already_checked_perpend.end()){
          ++nbr_perpend;
			if(firstPerpend && already_checked_perpend.find(elem1) == already_checked_perpend.end()){
				++nbr_perpend;
				firstPerpend = false;
			}
          already_checked_perpend.insert(elem1);
        }
		//std::cout << "Angle " << angle << " para: " << nbr_parallell << " perpend: " << nbr_perpend << std::endl;
      }
    }
  }
  std::cout << "Number of lines: " << vec.size() << std::endl;
  
  std::cout << "Mean length of lines: " << (length/vec.size()) << std::endl;

  std::cout << "Parallell lines: " << nbr_parallell << std::endl;

  std::cout << "Perpendicular lines: " << nbr_perpend << std::endl;

	Attributes attributes(vec.size(),length/vec.size(),nbr_parallell,nbr_perpend);
	return attributes;
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
