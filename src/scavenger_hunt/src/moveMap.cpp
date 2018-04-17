#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include "geometry_msgs/Pose2D.h"
#include <tf2/LinearMath/Quaternion.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>

void recievePose(const geometry_msgs::Pose2D&msg);

move_base_msgs::MoveBaseGoal goal;
bool STOP = true;
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  ros::init(argc, argv, "goToTimeout");
  ros::NodeHandle nh;
  ros::Subscriber subGoalPose;
  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  //wait for the action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }
  subGoalPose = nh.subscribe("nextGoal",1000,&recievePose);
  ros::Rate loop_rate(10);
  while (nh.ok() ){
	
	if (STOP == false){
		ROS_INFO("Sending goal");
  		ac.sendGoalAndWait(goal, ros::Duration(5.0));
		if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
   		    ROS_INFO("The base moved to goal!");
  		else
    		    ROS_INFO("The base failed to move to goal within five seconds.");
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

void recievePose(const geometry_msgs::Pose2D&msg) {
  goal.target_pose.header.frame_id = "base_link";
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