/*
Costmap saved to map.txt, displays resolution
*/
#include <ros/ros.h>
#include <nav_msgs/OccupancyGrid.h>
#include <fstream>

void localMapMessageReceived(const nav_msgs::OccupancyGrid&msg) {
  ROS_INFO_STREAM("Received Local Map");
  ROS_INFO_STREAM("Dimensions: " <<msg.info.width << " x " << msg.info.height);
  ROS_INFO_STREAM("Resolution " << msg.info.resolution);
}

void gloabalMapMessageReceived(const nav_msgs::OccupancyGrid&msg) {
  ROS_INFO_STREAM("Received Global Map");
  ROS_INFO_STREAM("Dimensions: " <<msg.info.width << " x " << msg.info.height);
  ROS_INFO_STREAM("Resolution " << msg.info.resolution);
  ROS_INFO_STREAM("Saving costmap to a file");
  std::ofstream globalmap("map.txt");
  int z= 0;
  for (int i = 0 ; i < msg.info.height ; i++) {
      for ( int j = 0 ; j < msg.info.width ; j++ )
	  globalmap << (int)msg.data[z++] << " " ;
      globalmap << std::endl;
  }
  globalmap.close();
}

int main(int argc,char ** argv) {

  ros::init(argc,argv,"getlocalglobalmap");
  ros::NodeHandle nh;

  ros::Subscriber subglobal =
    nh.subscribe("/move_base/global_costmap/costmap",
		 100,&gloabalMapMessageReceived);
  ros::Subscriber sublocal =
    nh.subscribe("/move_base/local_costmap/costmap",
		 100,&localMapMessageReceived); 

  ros::spin();
}
