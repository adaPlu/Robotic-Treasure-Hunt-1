/*
Displays All relevent Pose/Position/Orientation Data
*/

#include <ros/ros.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <iostream>




geometry_msgs::Pose currentPose;


void currentPoseCallBack(const geometry_msgs::PoseWithCovarianceStamped&msg){
  currentPose.position.x = msg.pose.pose.position.x;
  currentPose.position.y = msg.pose.pose.position.y;
  currentPose.position.z = msg.pose.pose.position.z;
  currentPose.orientation.x = msg.pose.pose.orientation.x;
  currentPose.orientation.y = msg.pose.pose.orientation.y;
  currentPose.orientation.z = msg.pose.pose.orientation.z;
  currentPose.orientation.w = msg.pose.pose.orientation.w;
  return;
}


int main(int argc,char ** argv) {

  ros::init(argc,argv,"postion");
  ros::NodeHandle nh;
  ros::Subscriber subCurrentpose = nh.subscribe("/amcl_pose", 5, currentPoseCallBack);
  ros::Rate loop_rate(10);
  while (nh.ok() ){
	ros::spinOnce();
	double x=currentPose.orientation.x;
  	double y=currentPose.orientation.y;
  	double z=currentPose.orientation.z;
  	double w=currentPose.orientation.w;
  	double curr_head=atan2(2*(x*y+w*z), w*w + x*x - y*y - z*z);
	ROS_INFO("Angle about z axis: [%f]", curr_head * 57.29);
	ROS_INFO("Position-> x: [%f], y: [%f], theta: [%f]",currentPose.position.x,currentPose.position.y,currentPose.position.z);
	ROS_INFO("Orientation(Quat)-> x: [%f], y: [%f], z: [%f], w: [%f]",currentPose.orientation.x,currentPose.orientation.y,currentPose.orientation.z, currentPose.orientation.w);
loop_rate.sleep();

	
	}
}

