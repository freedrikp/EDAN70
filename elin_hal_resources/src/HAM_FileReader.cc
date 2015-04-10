/*---------------------------------------------------------------------*/
//
// = LIBRARY
//
// = FILENAME
//   HAM_FileReader.cc
//
// = FUNCTION
//   The scan publisher reads sensory data from a specific file formate
//   compatible to the CURE library and provides them according to the formats 
//   (so far) required by several Human Augmented Mapping components.
//
// = AUTHOR(S)
//   Elin Anna Topp
//
// = DESCRIPTION
//   see comments
//
// = COPYRIGHT
//   Copyright (c) 2014 Elin Anna Topp
//
/*----------------------------------------------------------------------*/
#include "./HAM_FileReader.hh"
#include <kdl/frames.hpp>


HAM_FileReader::HAM_FileReader( void) {
  dataMsg_ = new elin_hal_resources::HAM_ScanOdomRaw();    
}

HAM_FileReader::~HAM_FileReader( void) {
  if( dataMsg_ != NULL) delete dataMsg_;
}

bool HAM_FileReader::initReadingFromFile( char *fromDir) {
  scanTimestamp_ = 0.0;
  odomTimestamp_ = 0.0;

  char *buf = new char[256];
  sprintf( buf, "%s/scans.dat", fromDir);
  scanFS_.open( buf, std::ios::in);
  sprintf( buf, "%s/odom.dat", fromDir);
  odomFS_.open( buf, std::ios::in);

  delete[] buf;
  return( scanFS_.is_open() && odomFS_.is_open());
}


void HAM_FileReader::disconnectFromFile( void) {
  if( scanFS_.is_open()) scanFS_.close();
  if( odomFS_.is_open()) odomFS_.close();

  return;
}  


elin_hal_resources::HAM_ScanOdomRaw* HAM_FileReader::readNext( void) {
  int dummy;
  bool gotScanData = true;
  bool gotOdomData = true;
  double scanTimeBuf, odomTimeBuf;
  float fDummy;
  
  //scanTimeBuf = odomTimeBuf = tDummy = 0.0;
  
  // --- need to read from both files only if odom has come around ... 
  if( scanTimestamp_ <= odomTimestamp_) {
  
    if( !scanFS_.eof()) {  
      scanTimeBuf = scanTimestamp_;
    
      do {
        // --- getting rid of extra entries
        scanFS_ >> dummy;
        scanFS_ >> dummy;
        
        // --- reading some real data      
        scanFS_ >> dataMsg_->nScanPts;
        scanFS_ >> scanTimeBuf;
        scanFS_ >> fDummy;
        scanTimeBuf += fDummy / 1000000;

        // --- getting rid of extra entries
        scanFS_ >> dummy;
        scanFS_ >> dummy;
        scanFS_ >> dummy;
        scanFS_ >> dummy;
        scanFS_ >> dummy;
        scanFS_ >> dummy;
        
        // --- reading angular step between scan points
        scanFS_ >> dataMsg_->angStep;      
        
        // --- getting rid of extra entries
        scanFS_ >> dummy;
        scanFS_ >> dummy;
        scanFS_ >> fDummy;
        
        // --- reading the actual scan data (distances)
        if( dataMsg_->scanPts.capacity() < dataMsg_->nScanPts) dataMsg_->scanPts.resize( dataMsg_->nScanPts);
        for( int i=0; i<dataMsg_->nScanPts; i++) scanFS_ >> dataMsg_->scanPts[i];

        if( dataMsg_->nScanPts == 541) dataMsg_->minAngle = -3*M_PI/4;
        else dataMsg_->minAngle = -M_PI/2;        
        dataMsg_->maxAngle = -1*dataMsg_->minAngle;

      } while( scanTimeBuf == scanTimestamp_ && !scanFS_.eof());
      scanTimestamp_ = scanTimeBuf;
      dataMsg_->lastScanTime = scanTimestamp_;  
    } else {
      gotScanData = false;
    }
  }
  
  if( !odomFS_.eof()) {
    odomTimeBuf = odomTimestamp_;
    
    do { 
      // --- getting rid of extra entries
      odomFS_ >> dummy;
      odomFS_ >> dummy;
      odomFS_ >> dummy;

      // --- reading some real data      
      odomFS_ >> odomTimeBuf;
      odomFS_ >> fDummy;
      odomTimeBuf += fDummy / 1000000;

      // --- getting rid of extra entries
      odomFS_ >> dummy;
      odomFS_ >> dummy;
      odomFS_ >> dummy;
      
      // --- reading x and y position 
      odomFS_ >> dataMsg_->pose.position.x;
      odomFS_ >> dataMsg_->pose.position.y;

      // --- getting rid of extra entries
      odomFS_ >> dummy;
      
      // --- reading theta 
      
      odomFS_ >> fDummy;
      // put in a KDL-transform here!
      double x, y, z, w;
      KDL::Rotation r = KDL::Rotation::RPY( 0.0, 0.0, fDummy);
  
      r.GetQuaternion( x, y, z, w);
  
      dataMsg_->pose.orientation.x = x;
      dataMsg_->pose.orientation.y = y;
      dataMsg_->pose.orientation.z = z;
      dataMsg_->pose.orientation.w = w;
      
                 
      // --- getting rid of extra entries
      odomFS_ >> dummy;
      odomFS_ >> dummy;

    } while( odomTimeBuf == odomTimestamp_ && !odomFS_.eof());
    
    odomTimestamp_ = odomTimeBuf;
    dataMsg_->lastScanTime = odomTimestamp_;      
  } else {
    gotOdomData = false;
  }  
  
  // if there was any data updated ...
  if( gotScanData || gotOdomData) return dataMsg_;
  else return NULL;
}

/**
 * This tutorial demonstrates simple sending of messages over the ROS system.

int main(int argc, char **argv)
{
  ros::init(argc, argv, "HAM_FileReader");
  
  HAM_FileReader dPub( 1000, 10);
  char buf[256];
  bool readOk = false;
  
  while (ros::ok()) {
    
    std::cout << " please enter the directory name to read data from!" << std::endl;
    std::cin >> buf;
  
    readOk = dPub.initReadingFromFile( buf);
    
    while( readOk && ros::ok()) {
      readOk = dPub.readAndPublishNext();
    }
    
    dPub.disconnectFromFile();
  }


  return 0;
}
*/
