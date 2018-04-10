#include <ros/ros.h>
#include <logical_camera_plugin/logicalImage.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <string>
#include <vector>
#include <geometry_msgs/Quaternion.h>

#include <tf2_ros/transform_listener.h>
#include <geometry_msgs/TransformStamped.h>
#include <tf2/utils.h>

std::vector<std::string> treasureNames;

float robotX, robotY;
geometry_msgs::Quaternion robotOrientation;
geometry_msgs::TransformStamped pose;

void printCoordinatesName(std::string name, float x, float y, geometry_msgs::Quaternion ori){

	ROS_INFO_STREAM("Name: " << name);
	ROS_INFO_STREAM("X location: " << x);
	ROS_INFO_STREAM("Y location: " << y);
	ROS_INFO_STREAM("Orientation: " << ori);
}

void Location(const geometry_msgs::PoseWithCovarianceStamped &msg){

	robotX = msg.pose.pose.position.x;
	robotY = msg.pose.pose.position.y;
	robotOrientation = msg.pose.pose.orientation;

	ROS_INFO_STREAM("Robot pose " << msg.pose.pose.position);
	ROS_INFO_STREAM("Robot rotation " << msg.pose.pose.orientation);
//	ROS_INFO_STREAM("Robot location " << pose);
}

void LogicalCameraMessage(const logical_camera_plugin::logicalImage &msg){

	std::string foundTreasure = msg.modelName;

	float x = msg.pose_pos_x;
	float y = msg.pose_pos_y;

	geometry_msgs::Quaternion quat;

	quat.x = msg.pose_rot_x;
	quat.y = msg.pose_rot_y;
	quat.z = msg.pose_rot_z;
	quat.w = msg.pose_rot_w;

	if(treasureNames.empty()){

		treasureNames.insert(treasureNames.begin(), foundTreasure);
		printCoordinatesName(foundTreasure, x, y, quat);
	}

	else{
		int vecsize = treasureNames.size();
		bool found = false;

		for(int i=0; i < vecsize; i++){

			std::string knownTreasure = treasureNames.at(i);

			if(foundTreasure.compare(knownTreasure) == 0){

				found = true;
				break;
			}
		}

		if(found == false){

			treasureNames.insert(treasureNames.begin(), foundTreasure);
			printCoordinatesName(foundTreasure, x, y, quat);
		}
	}
}

int main(int argc, char** argv){

ros::init(argc, argv, "treasurelocator");

ros::NodeHandle nh;

ros::Subscriber logcamera = nh.subscribe("/objectsDetected",1000, &LogicalCameraMessage);

ros::Subscriber robotlocation = nh.subscribe("/amcl_pose", 1000, &Location);

ros::spin();
/*
tf2_ros::Buffer tfbuffer;
tf2_ros::TransformListener listener(tfbuffer);
while(ros::ok()){
try{
	pose = tfbuffer.lookupTransform("mapfinal", "base_link", ros::Time(0));
}
catch(tf2::TransformException &ex){
	ROS_WARN("%s", ex.what());
}
ros::spinOnce();
}
*/

}
#include <ros/ros.h>
#include <logical_camera_plugin/logicalImage.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <string>
#include <vector>
#include <geometry_msgs/Quaternion.h>

#include <tf2_ros/transform_listener.h>
#include <geometry_msgs/TransformStamped.h>
#include <tf2/utils.h>

std::vector<std::string> treasureNames;

float robotX, robotY;
geometry_msgs::Quaternion robotOrientation;
geometry_msgs::TransformStamped pose;

void printCoordinatesName(std::string name, float x, float y, geometry_msgs::Quaternion ori){

	ROS_INFO_STREAM("Name: " << name);
	ROS_INFO_STREAM("X location: " << x);
	ROS_INFO_STREAM("Y location: " << y);
	ROS_INFO_STREAM("Orientation: " << ori);
}

void Location(const geometry_msgs::PoseWithCovarianceStamped &msg){

	robotX = msg.pose.pose.position.x;
	robotY = msg.pose.pose.position.y;
	robotOrientation = msg.pose.pose.orientation;

	ROS_INFO_STREAM("Robot pose " << msg.pose.pose.position);
	ROS_INFO_STREAM("Robot rotation " << msg.pose.pose.orientation);
//	ROS_INFO_STREAM("Robot location " << pose);
}

void LogicalCameraMessage(const logical_camera_plugin::logicalImage &msg){

	std::string foundTreasure = msg.modelName;

	float x = msg.pose_pos_x;
	float y = msg.pose_pos_y;

	geometry_msgs::Quaternion quat;

	quat.x = msg.pose_rot_x;
	quat.y = msg.pose_rot_y;
	quat.z = msg.pose_rot_z;
	quat.w = msg.pose_rot_w;

	if(treasureNames.empty()){

		treasureNames.insert(treasureNames.begin(), foundTreasure);
		printCoordinatesName(foundTreasure, x, y, quat);
	}

	else{
		int vecsize = treasureNames.size();
		bool found = false;

		for(int i=0; i < vecsize; i++){

			std::string knownTreasure = treasureNames.at(i);

			if(foundTreasure.compare(knownTreasure) == 0){

				found = true;
				break;
			}
		}

		if(found == false){

			treasureNames.insert(treasureNames.begin(), foundTreasure);
			printCoordinatesName(foundTreasure, x, y, quat);
		}
	}
}

int main(int argc, char** argv){

ros::init(argc, argv, "treasurelocator");

ros::NodeHandle nh;

ros::Subscriber logcamera = nh.subscribe("/objectsDetected",1000, &LogicalCameraMessage);

ros::Subscriber robotlocation = nh.subscribe("/amcl_pose", 1000, &Location);

ros::spin();
/*
tf2_ros::Buffer tfbuffer;
tf2_ros::TransformListener listener(tfbuffer);
while(ros::ok()){
try{
	pose = tfbuffer.lookupTransform("mapfinal", "base_link", ros::Time(0));
}
catch(tf2::TransformException &ex){
	ROS_WARN("%s", ex.what());
}
ros::spinOnce();
}
*/

}

