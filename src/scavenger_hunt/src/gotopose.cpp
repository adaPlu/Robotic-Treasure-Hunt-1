#include <ros/ros.h>
#include <geometry_msgs/Pose2D.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <geometry_msgs/Quaternion.h>
#include <tf/transform_datatypes.h>
#include <queue>
using namespace std;

class Point{
public:
	float x;
	float y;
	float theta;
};

queue<Point> location;

void PoseMessage(const geometry_msgs::Pose2D &msg){

	Point p;

	p.x = msg.x;
	p.y = msg.y;
	p.theta = msg.theta;

	location.push(p);
}

int main(int argv, char ** argc){

ros::init(argv, argc, "gotopose");

ros::NodeHandle nh;

ros::Subscriber subpose = nh.subscribe("targetpose", 1000, &PoseMessage);

actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> ac("move_base",true);

while(!ac.waitForServer()){}

move_base_msgs::MoveBaseGoal goal;

while(ros::ok()){

	if(!location.empty()){

		Point target = location.front();

		location.pop();

		goal.target_pose.header.frame_id = "map";
		goal.target_pose.header.stamp = ros::Time::now();
		goal.target_pose.pose.position.x = target.x;
		goal.target_pose.pose.position.y = target.y;

		tf::Quaternion quaternion;
		quaternion = tf::createQuaternionFromYaw(target.theta);
		geometry_msgs::Quaternion qMsg;
		tf::quaternionTFToMsg(quaternion, qMsg);

		goal.target_pose.pose.orientation = qMsg;

		ac.sendGoal(goal);

		ac.waitForResult();

		if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){

			ROS_INFO_STREAM("Reached goal");
		}

		else{

			ROS_INFO_STREAM("Failed to reach goal");
			ac.cancelGoal();
		}
	}

	ros::spinOnce();
}

}
