// #include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include "point.h"
#include "parser.h"



// #define PLOTSMAX 361
// #define PLOTSMIN 350

// std::pair<double,double> transform(double accumulatedAngle, double distance, double fieldOfView){
//   double angle;
//   int sign;
//   if ((fieldOfView/2) > accumulatedAngle){
//       angle = fieldOfView/2 - accumulatedAngle;
//       sign = -1;
//   }else{
//       angle = accumulatedAngle - fieldOfView/2;
//       sign = 1;
//   }
//   double x = sign*distance*sin(angle);
//   double y = distance*cos(angle);
//   return std::make_pair(x,y);
// }


Dataset parseDataset(std::string line, int lineNo){
  std::stringstream data(line);
  double floatval;
  long intval;
  data >> floatval; //unknown
  data >> floatval; //unknown
  int nbrPoints;
  data >> nbrPoints; //number of points
  data >> intval; //timestamp_sec
  data >> intval; //timestamp_micsec
  data >> floatval; //unknown
  data >> floatval; //unknown
  data >> floatval; //unknown
  data >> floatval; //unknown
  data >> floatval; //unknown
  data >> floatval; //unknown
  double angleInc;
  data >> angleInc; //angle_increment
  data >> floatval; //unknown
  data >> floatval; //unknown
  data >> floatval; //unknown
  Dataset set(std::to_string(lineNo),nbrPoints,angleInc);
  double fieldOfView = (nbrPoints - 1)*angleInc;
  //std::cout << fieldOfView*180/(atan(1)*4) << std::endl;
  double dist;
  int index = 0;
  while(data >> dist){ //distance for each point
    //std::pair<double,double> coords = transform(index*angleInc,dist,fieldOfView);
    //std::cout << "Angle: " << index*angleInc << std::endl << "Distance: " << dist << std::endl << "xCoord: " << coords.first << std::endl << "yCoord: " << coords.second << std::endl;
    Point p(index,index*angleInc,dist,fieldOfView);//,coords.first,coords.second);
    set.addPoint(p);
    ++index;
  }
  return set;
}

std::vector<Dataset> parseFile(std::ifstream& stream){//, int plotMin, int plotMax){
  std::vector<Dataset> vec;
  std::string line;
  bool correctAmount = true;
  int lineNo = 1;
  while (correctAmount && getline(stream,line)){
    Dataset set = parseDataset(line,lineNo);
    //std::cout << "Field of view: " << nbrPoints*angle*180/(atan(1)*4) << std::endl;
    //std::cout << "nbrPoints: " << nbrPoints << std::endl << "parsedPoints: " << index << std::endl << "--------------------" << std::endl;
    //correctAmount = correctAmount ? (index == nbrPoints) : correctAmount;
    //if (!correctAmount)
    //  break;

    //
    // if (lineNo >= plotMin && lineNo <= plotMax){
    //   set.outputPlotFile("plots");
    // }
    vec.push_back(set);
      //std::cout << lineNo << std::endl;
    ++lineNo;
  }
  return vec;
}

// int main(int argc, char* argv[]){
//   // if (argc != 4){
//   //   std::cout << "Wrong arguemnts! Usage: ./parser startAngle endAngle distance" << std::endl;
//   //   exit(1);
//   // }
//
//   // int plotMin = std::stoi(std::string(argv[1]));
//   // int plotMax = std::stoi(std::string(argv[2]));
//   std::cout << "Input: startAngle endAngle distance!" << std::endl;
//   double startAngle;
//   double endAngle;
//   double distance;
//   std::cin >> startAngle;
//   std::cin >> endAngle;
//   std::cin >> distance;
//   std::ifstream file(argv[1]);
//
//   std::vector<Dataset> vec = parseFile(file);//, plotMin, plotMax);
//
//   // for (int i = plotMin; i <= plotMax; ++i){
//   //   vec[i].datasetInterval(0,atan(1)*2).outputPlotFile("plots");
//   // }
//
//   for (Dataset set : vec){
//     Dataset data = set.datasetInterval((startAngle/180)*atan(1)*4,(endAngle/180)*atan(1)*4,distance);
//     data.outputPlotFile("plots");
//     data.outputDatasetFile("datasets");
//   }
//
//   //file.close();
//   // if (correctAmount){
//   //   std::cout << "Indicated number of points is equal to number of data points" << std::endl;
//   // }else{
//   //   std::cout << "Indicated number of points is NOT equal to number of data points" << std::endl;
//   // }
//   /*okänt okänt <antal_punkter> <timestamp_sec> <timestamp_micsec> okänt okänt okänt okänt okänt okänt <vinkel_increment> okänt okänt okänt <<antal_punkter> * distans_i_meter>*/
// }
