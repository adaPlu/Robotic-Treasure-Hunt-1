
#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include <sensor_msgs/LaserScan.h>
#include <nav_msgs/OccupancyGrid.h>


#include <stdlib.h>     /* srand, rand */

double iSecret = 0;
double jSecret = 0;
geometry_msgs::Twist msg;
int toggle = 1;
ros::Publisher pub;
double disttoclosestobject = 30;//Max range of laser 30m
bool move = false;
/*
void recieveRanges(const sensor_msgs::LaserScan::ConstPtr& scan) {
	double disttoclosestobject = 30;
	for(int i = 0 ; i <scan->ranges.size() ; i++){	
        	ROS_INFO_STREAM(scan->ranges[i]);

		if(scan->ranges[i] < disttoclosestobject)
			disttoclosestobject = scan->ranges[i];
		
	}
	ROS_INFO("Dist:[%f]", disttoclosestobject);
	if(disttoclosestobject <= 0.2){
		move = false;	
		return;		
	}
	else
		move = true;
		return;
}
*/

/*
void recievePose(const geometry_msgs::Pose2D&msg) {
	
        goalPose.x = msg.x;
	goalPose.y = msg.y;
	relative_angle = atan2(goalPose.y - currentPose.position.y, goalPose.x - currentPose.position.x) * 57.29;
        STOP = false;
	return;

}


void poseCallback(const geometry_msgs::PoseStamped&msg){

  currentPose.position.x = msg.pose.position.x;
  currentPose.position.y = msg.pose.position.y;
  currentPose.position.z = msg.pose.position.z;
  currentPose.orientation.x = msg.pose.orientation.x;
  currentPose.orientation.y = msg.pose.orientation.y;
  currentPose.orientation.z = msg.pose.orientation.z;
  currentPose.orientation.w = msg.pose.orientation.w;
  return;
}

*/


void recieveMap(const nav_msgs::OccupancyGrid& map) {
	for(int i =0; i <map.data.size();i++){
		ROS_INFO("MapData:[%d]", map.data[i]);
	}
		return;
}


int main(int argc, char **argv)
{
  ros::init(argc, argv, "moveMap");
  ros::NodeHandle n;


  pub = n.advertise<geometry_msgs::Twist>("/husky_velocity_controller/cmd_vel", 1000);
  
  //ros::Subscriber scanlaser  = n.subscribe<sensor_msgs::LaserScan> ("/scan", 10,&recieveRanges);
  ros::Subscriber map = n.subscribe("/map", 5, recieveMap);
  ros::Rate loop_rate(10);
  ros::Time startTime = ros::Time::now();
  ros::Duration duration = ros::Duration( rand() % 2 + 1 );
		
	while (n.ok()){
	
	if (move){
		 if ( ( ros::Time::now().sec - startTime.sec ) >= duration.sec ){
	  		startTime = ros::Time::now();

	      if (toggle){
		duration = ros::Duration( rand() % 2 + 1 );
		toggle = 0;
		iSecret = 0;
		jSecret = ((double)(rand() % 5 - 2))/5;
	      }
	      else{
		duration = ros::Duration( rand() % 2 + 1 );
		toggle = 1;
		iSecret = ((double)(rand() % 5 - 2))/5;
		jSecret = 0;
	      }
	    }

	       
	  	msg.linear.x = iSecret;
	  	msg.angular.z = jSecret;

	  	pub.publish(msg);
	}
	
	loop_rate.sleep();
	ros::spinOnce(); 
	}
  

}
