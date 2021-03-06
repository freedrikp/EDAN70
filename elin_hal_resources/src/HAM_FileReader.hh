#ifndef _HAM_FileReader_HH_
#define _HAM_FileReader_HH_

#include <ros/ros.h>
#include "elin_hal_resources/HAM_ScanOdomRaw.h"

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <float.h>



class HAM_FileReader {


private:

  // --- the file streams for reading ---
  std::fstream scanFS_;
  std::fstream odomFS_;

  // --- helping buffers --- 
  double scanTimestamp_;
  double odomTimestamp_;
  
  // --- the message to be filled and published ---
  elin_hal_resources::HAM_ScanOdomRaw *dataMsg_;

public:

  HAM_FileReader( void);
  ~HAM_FileReader( void);
  
  // --- set all initial paths and flags for data 
  //     collection                  --- 
  bool initReadingFromFile( char *fromDir);
  
  // --- close the files ---
  void disconnectFromFile( void);
  
  // --- useful for file reading things to go through data stepwise
  // --- returns FALSE in case there are no more data to read
  elin_hal_resources::HAM_ScanOdomRaw* readNext( void);
  
};

#endif 
