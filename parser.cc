/*Hej,

nu har jag letat upp två (rätt gamla) datasamlingar. Jag valde dem, eftersom det är just den typen av fil som kan läses av ROS-noden HAM_fileDataPublisher och som inte innehåller korrupt data - jag har några nyare scan- datafiler från 2 x 270° scans, där punkterna är inlagda i fel ordning. Ifall ni vill ha 360°-filer någon gång, går det att ordna efter påsk / lite längre in i projektet.

(HAM står för Human Augmented Mapping...)

ROS-noden:
- HAM_FileReader.cc/hh: läser in en scan.dat och en odom.dat fil, och genererar en ROS-Msg med "raw" Scan och Odometry-data, så nära synkroniserade de kan vara (scan-data kom då med 4-5 Hz, odometri-data med 10 Hz, och våra verktyg sparade då ofta en scan-mängd dubbelt, men nu känns det onödigt att skicka om det inte blev någon uppdatering, det kollas alltså om det är ny data och om odometri också finns med).
Förväntar sig ett katalognamn / en sökväg, i katalogen bör det alltså finnas minst två filer, en som heter scan.dat, en som heter odom.dat.

- HAM_fileDataPublisher.cc publicerar en HAM_ScanOdomRaw.msg med ungefär synkroniserad data till topic ham_data.


Datafilerna:
- scan.dat: innehåller scannerns mätningar (int / float-värden), i följande format:

okänt okänt <antal_punkter> <timestamp_sec> <timestamp_micsec> okänt okänt okänt okänt okänt okänt <vinkel_increment> okänt okänt okänt <<antal_punkter> * distans_i_meter>

(ny set börjar bara om på ny rad)

- odom.data: innehåller robotens egen pose-uppskattning relativt pose 0,0,0 den startat ifrån, i följande format:

okänt okänt okänt <timestamp_sec> <timestamp_micrsec> okänt okänt okänt <x> <y> <z> <theta> <vinkel2> <vinkel3>

(värden för z, vinkel2 och vinkel3 är alltid 0, eftersom vi bara har tre effektiva frihetsgrader...)


Hela bunten är kanske mera intressant för "simulationer", medans ni egentligen bara behöver scan-data och vill kanske skriva en offline-parser eller testa med enbart en data-mängd till en början.


Litteratur:

- http://eds.b.ebscohost.com/eds/detail/detail?vid=4&sid=8890a336-76f9-46d1-a241-b2dcc366ba64%40sessionmgr115&hid=117&bdata=JnNpdGU9ZWRzLWxpdmUmc2NvcGU9c2l0ZQ%3d%3d#db=cat01310a&AN=lovisa.001442155

(Duda, Hart, Stork, "Pattern Classification") påstår bibliotekets söksystem ska finnas tillgänglig i E-huset.
Som sagt, mer av en klassiker än något banbrytande nytt...

Här: http://miarn.sourceforge.net/pdf/a1738b.pdf finns det papperet med laser-data tolkning.
Och här: http://www.nada.kth.se/~topp/pdf/techRep05_1.pdf hittar ni en teknisk rapport som jag själv skrev ... (visste inte ens att min gamla hemsida fungerade fortfarande...)

Om jag kommer på fler grundläggande publikationer, meddelar jag detta.

Och just det, ROS hittas på ros.org.

Mvh, Elin
*/

#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <utility>
#include "point.h"
#include "dataset.h"

#define PLOTSMAX 361
#define PLOTSMIN 350

std::pair<double,double> transform(double accumulatedAngle, double distance, double fieldOfView){
  double angle;
  int sign;
  if ((fieldOfView/2) > accumulatedAngle){
      angle = fieldOfView/2 - accumulatedAngle;
      sign = -1;
  }else{
      angle = accumulatedAngle - fieldOfView/2;
      sign = 1;
  }
  double x = sign*distance*sin(angle);
  double y = distance*cos(angle);
  return std::make_pair(x,y);
}

int main(int argc, char* argv[]){
  if (argc != 3){
    std::cout << "Wrong arguemnts! Usage: ./parser plotmin plotmax" << std::endl;
    exit(1);
  }
  int plotMin = std::stoi(std::string(argv[1]));
  int plotMax = std::stoi(std::string(argv[2]));
  std::string line;
  bool correctAmount = true;
  int lineNo = 1;
  while (correctAmount && getline(std::cin,line)){
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
      std::pair<double,double> coords = transform(index*angleInc,dist,fieldOfView);
      //std::cout << "Angle: " << index*angleInc << std::endl << "Distance: " << dist << std::endl << "xCoord: " << coords.first << std::endl << "yCoord: " << coords.second << std::endl;
      Point p(index,index*angleInc,dist,coords.first,coords.second);
      set.addPoint(p);
      ++index;
    }
    //std::cout << "Field of view: " << nbrPoints*angle*180/(atan(1)*4) << std::endl;
    //std::cout << "nbrPoints: " << nbrPoints << std::endl << "parsedPoints: " << index << std::endl << "--------------------" << std::endl;
    correctAmount = correctAmount ? (index == nbrPoints) : correctAmount;
    if (!correctAmount)
      break;


    if (lineNo >= plotMin && lineNo <= plotMax){
      set.outputPlotFile("plots");
    }

      //std::cout << lineNo << std::endl;
    ++lineNo;
  }
  if (correctAmount){
    std::cout << "Indicated number of points is equal to number of data points" << std::endl;
  }else{
    std::cout << "Indicated number of points is NOT equal to number of data points" << std::endl;
  }
  /*okänt okänt <antal_punkter> <timestamp_sec> <timestamp_micsec> okänt okänt okänt okänt okänt okänt <vinkel_increment> okänt okänt okänt <<antal_punkter> * distans_i_meter>*/
}
