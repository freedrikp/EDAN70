#include "./HAM_FileReader.hh"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "elin_hal_publisher");

  elin_hal_resources::HAM_ScanOdomRaw *dataMsg;
  ros::NodeHandle nodeHandle;
  ros::Publisher ham_dataPub = nodeHandle.advertise<elin_hal_resources::HAM_ScanOdomRaw>( "ham_data", 1000);
  ros::Rate loopRate( 10);
  
  HAM_FileReader *fReader = new HAM_FileReader();
  char buf[256];
  bool readOk = false;
  
  while (ros::ok()) {
    
    std::cout << " please enter the directory name to read data from!" << std::endl;
    std::cin >> buf;
  
    readOk = fReader->initReadingFromFile( buf);
    
    while( readOk && ros::ok()) {
      dataMsg = fReader->readNext();
      
      if( dataMsg != NULL) {
        // ... do the publishing!
        ROS_INFO("Publishing scan at: %f and odom at: %f \n", dataMsg->lastScanTime, dataMsg->lastOdomTime);
        ham_dataPub.publish( *dataMsg);
    
        ros::spinOnce();
        loopRate.sleep();
      } else {
        readOk = false;
      }
 
    }
    
    fReader->disconnectFromFile();
  }

  delete fReader;

  return 0;
}
