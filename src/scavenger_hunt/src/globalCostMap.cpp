#include "ros/ros.h"
#include <nav_msgs/OccupancyGrid.h>
#include <fstream>

void recieveGlobalCostMap(const nav_msgs::OccupancyGrid& map);

int main(int argc, char **argv){
  ros::init(argc, argv, "globalCostMap");
  ros::NodeHandle n;
  ros::Subscriber mapg = n.subscribe("/move_base/global_costmap/costmap", 100, recieveGlobalCostMap);
 
  ros::spin(); 
}



void recieveGlobalCostMap(const nav_msgs::OccupancyGrid& map) {
	ROS_INFO_STREAM("Recieved Global Map");
	ROS_INFO_STREAM("Dimensions: " <<map.info.width << "_x_" << map.info.height);
	ROS_INFO_STREAM("Resolution " << map.info.resolution);
	std::ofstream globalmap("map.txt");
	
	int k = 0;
	for(int i =0; i <map.info.height;i++){
		for(int j =0; j <map.info.width;j++){
			globalmap << (int)map.data[k++] << "_" ;
		globalmap << std::endl;
		}
	}

	globalmap << std::endl;
	globalmap.close();
	
}
