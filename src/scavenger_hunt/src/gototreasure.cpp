
/*
Adam Pluguez
UC Merced CSE 180 Robotics
Final Project
Uses Move base to move to receieved point. Configured to go to 10 fixed map points then rotate 360 degrees in an attempt to locate any nearby treasures.
*/
#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <geometry_msgs/Twist.h>
#include <time.h>


void serviceActivated();
void serviceDone(const actionlib::SimpleClientGoalState& state,const move_base_msgs::MoveBaseResultConstPtr& result);
void serviceFeedback(const move_base_msgs::MoveBaseFeedbackConstPtr& fb);
void turn(double rel_angle, double ang_speed, bool isClockwise);
void setGoal(double x, double y);

ros::Publisher vel;
move_base_msgs::MoveBaseGoal goal;
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;


int main(int argc, char** argv){
  ros::init(argc, argv, "gototreasure");
  ros::NodeHandle nh;

  vel =nh.advertise<geometry_msgs::Twist>("/husky_velocity_controller/cmd_vel", 10);
  ros::Rate loop_rate(10);

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  //wait for the action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }
  
  turn(11, 1, 1);
  
  setGoal(0,8); 

  ROS_INFO("Sending goal");
  ac.sendGoal(goal,&serviceDone,&serviceActivated,&serviceFeedback);
	ac.waitForResult();
	if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
   			ROS_INFO("The base moved to goal!");
			  turn(11, 1, 1);
	}
  else{
    		ROS_INFO("The base failed to move to goal for some reason.");
			  turn(11, 1, 1);
  }
 
  setGoal(8,8);

  ROS_INFO("Sending goal");
  ac.sendGoal(goal,&serviceDone,&serviceActivated,&serviceFeedback);
	ac.waitForResult();
	if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
   			ROS_INFO("The base moved to goal!");
			  turn(11, 1, 1);
	}
  else{
    		ROS_INFO("The base failed to move to goal for some reason.");
			  turn(11, 1, 1);
  }
  
  setGoal(8,2);
  
  ROS_INFO("Sending goal");
  ac.sendGoal(goal,&serviceDone,&serviceActivated,&serviceFeedback);
	ac.waitForResult();
	if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
   			ROS_INFO("The base moved to goal!");
			  turn(11, 1, 1);
	}
  else{
    		ROS_INFO("The base failed to move to goal for some reason.");
			  turn(11, 1, 1);
  }

  setGoal(8,-2);

  ROS_INFO("Sending goal");
  ac.sendGoal(goal,&serviceDone,&serviceActivated,&serviceFeedback);
	ac.waitForResult();
	if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
   			ROS_INFO("The base moved to goal!");
			  turn(11, 1, 1);
	}
  else{
    		ROS_INFO("The base failed to move to goal for some reason.");
			  turn(11, 1, 1);
  }

  setGoal(8,-8);

  ROS_INFO("Sending goal");
  ac.sendGoal(goal,&serviceDone,&serviceActivated,&serviceFeedback);
	ac.waitForResult();
	if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
   			ROS_INFO("The base moved to goal!");
			  turn(11, 1, 1);
	}
  else{
    		ROS_INFO("The base failed to move to goal for some reason.");
			  turn(11, 1, 1);
  }

  

  setGoal(0,-8);

  ROS_INFO("Sending goal");
  ac.sendGoal(goal,&serviceDone,&serviceActivated,&serviceFeedback);
	ac.waitForResult();
	if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
   			ROS_INFO("The base moved to goal!");
			  turn(11, 1, 1);
	}
  else{
    		ROS_INFO("The base failed to move to goal for some reason.");
			  turn(11, 1, 1);
  }

  setGoal(-8,-8);

  ROS_INFO("Sending goal");
  ac.sendGoal(goal,&serviceDone,&serviceActivated,&serviceFeedback);
	ac.waitForResult();
	if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
   			ROS_INFO("The base moved to goal!");
			  turn(11, 1, 1);
	}
  else{
    		ROS_INFO("The base failed to move to goal for some reason.");
			  turn(11, 1, 1);
  }

  setGoal(-8,-2);

  ROS_INFO("Sending goal");
  ac.sendGoal(goal,&serviceDone,&serviceActivated,&serviceFeedback);
	ac.waitForResult();
	if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
   			ROS_INFO("The base moved to goal!");
			  turn(11, 1, 1);
	}
  else{
    		ROS_INFO("The base failed to move to goal for some reason.");
			  turn(11, 1, 1);
  }

  setGoal(-8,2);

  ROS_INFO("Sending goal");
  ac.sendGoal(goal,&serviceDone,&serviceActivated,&serviceFeedback);
	ac.waitForResult();
	if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
   			ROS_INFO("The base moved to goal!");
			  turn(11, 1, 1);
	}
  else{
    		ROS_INFO("The base failed to move to goal for some reason.");
			  turn(11, 1, 1);
  }

  setGoal(-8,6);

  ROS_INFO("Sending goal");
  ac.sendGoal(goal,&serviceDone,&serviceActivated,&serviceFeedback);
	ac.waitForResult();
	if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
   			ROS_INFO("The base moved to goal!");
			  turn(11, 1, 1);
	}
  else{
    		ROS_INFO("The base failed to move to goal for some reason.");
			  turn(11, 1, 1);
  }

  setGoal(-8,8);

  ROS_INFO("Sending goal");
  ac.sendGoal(goal,&serviceDone,&serviceActivated,&serviceFeedback);
	ac.waitForResult();
	if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
   			ROS_INFO("The base moved to goal!");
			  turn(11, 1, 1);
	}
  else{
    		ROS_INFO("The base failed to move to goal for some reason.");
			  turn(11, 1, 1);
  }

  return 0;
}


//Functions
void setGoal(double x, double y){
  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();
  goal.target_pose.pose.position.x = x;
  goal.target_pose.pose.position.y = y;
  goal.target_pose.pose.orientation.w = 1;
}

void turn(double rel_angle, double ang_speed, bool isClockwise){
    ROS_INFO("Scanning goal area....");
	geometry_msgs::Twist twist;

	if(isClockwise)
		twist.angular.z = -abs(ang_speed);
	else	
		twist.angular.z = abs(ang_speed);
	ros::Rate ratet(10);	
	double t0 = ros::Time::now().toSec();	
	double current_angle = 0.0;

	do{
	     vel.publish(twist);
	     double t1 = ros::Time::now().toSec();
             current_angle = ang_speed * (t1-t0);	
	     ros::spinOnce();
             ratet.sleep();
	}while(current_angle < rel_angle && ros::ok());
	twist.angular.z = 0;
        vel.publish(twist);

}

void serviceActivated() {
    ROS_INFO_STREAM("Service received goal");
}

void serviceDone(const actionlib::SimpleClientGoalState& state,const move_base_msgs::MoveBaseResultConstPtr& result) {
    ROS_INFO_STREAM("Service completed");
    ROS_INFO_STREAM("Final state " << state.toString().c_str());
    //ros::shutdown();
}

void serviceFeedback(const move_base_msgs::MoveBaseFeedbackConstPtr& fb) {
    ROS_INFO_STREAM("Service still running");
    ROS_INFO_STREAM("Current pose (x,y) " <<
		    fb->base_position.pose.position.x << "," <<
		    fb->base_position.pose.position.y);
}


