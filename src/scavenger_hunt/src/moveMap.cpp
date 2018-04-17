
/*Uses Move bases to move to receieved point. Will be configured to go to fixed map points based on map size?*/
#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include "geometry_msgs/Pose2D.h"
#include <tf2/LinearMath/Quaternion.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>

void currentPoseCallBack(const geometry_msgs::PoseWithCovarianceStamped&msg);
void recieveTargetPose(const geometry_msgs::Pose2D&msg);
void serviceActivated();
void serviceDone(const actionlib::SimpleClientGoalState& state,const move_base_msgs::MoveBaseResultConstPtr& result);
void serviceFeedback(const move_base_msgs::MoveBaseFeedbackConstPtr& fb);
double getDistance(double x1, double y1, double x2, double y2);

geometry_msgs::Pose currentPose;
move_base_msgs::MoveBaseGoal goal;
bool STOP = true;
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  ros::init(argc, argv, "goTo");
  ros::NodeHandle nh;
  ros::Subscriber subCurrentpose = nh.subscribe("/amcl_pose", 10, &currentPoseCallBack);
  ros::Subscriber subGoalPose = nh.subscribe("targetpose",10, &recieveTargetPose);

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  //wait for the action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }
  

  ros::Rate loop_rate(10);
  while (nh.ok() ){
	
	if (STOP == false){
		ROS_INFO("Sending goal");
		ac.sendGoal(goal);
		ac.waitForResult();
		if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
   			ROS_INFO("The base moved to goal!");
  		else
    			ROS_INFO("The base failed to move to goal for some reason.");
			STOP = true;
	}
	else{
		ROS_INFO("Waiting on pose...");
	}
	loop_rate.sleep();
	ros::spinOnce(); 
	}
  return 0;
}

double getDistance(double x1, double y1, double x2, double y2){
	return sqrt(pow((x1-x2), 2) + pow((y1-y2), 2));
}


void serviceActivated() {
    ROS_INFO_STREAM("Service received goal");
}

void serviceDone(const actionlib::SimpleClientGoalState& state,const move_base_msgs::MoveBaseResultConstPtr& result) {
    ROS_INFO_STREAM("Service completed");
    ROS_INFO_STREAM("Final state " << state.toString().c_str());
    ros::shutdown();
}

void serviceFeedback(const move_base_msgs::MoveBaseFeedbackConstPtr& fb) {
    ROS_INFO_STREAM("Service still running");
    ROS_INFO_STREAM("Current pose (x,y) " <<
		    fb->base_position.pose.position.x << "," <<
		    fb->base_position.pose.position.y);
}

void recieveTargetPose(const geometry_msgs::Pose2D&msg) {
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();
  goal.target_pose.pose.position.x = msg.x;
  goal.target_pose.pose.position.y = msg.y;
  tf2::Quaternion q;
  q.setRPY(0,0,msg.theta);
  goal.target_pose.pose.orientation.x = q.x();
  goal.target_pose.pose.orientation.y = q.y();
  goal.target_pose.pose.orientation.z = q.z();
  goal.target_pose.pose.orientation.w = q.w();
  STOP = false;

	return;

}

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
