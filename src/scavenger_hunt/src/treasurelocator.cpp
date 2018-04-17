#include <ros/ros.h>
#include <logical_camera_plugin/logicalImage.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <string>
#include <vector>
#include <geometry_msgs/Quaternion.h>
#include <angles/angles.h>
#include <tf/transform_datatypes.h>
#include <nav_msgs/OccupancyGrid.h>

std::vector<std::string> treasureNames;

//amcl value to know pose and Orientation
float robotX, robotY, robotZ;
geometry_msgs::Quaternion robotOrientation;

void printCoordinatesName(std::string name, float x, float y, float z, geometry_msgs::Quaternion ori){

	//getting angle from z rotation
	double treAngle = tf::getYaw(ori);

	//makes angle be from 0 to 2*M_PI
	treAngle = angles::normalize_angle_positive(treAngle);

	double degree = treAngle*180/M_PI;

	if((degree >= 0) && (degree < 90)){
		x = x - robotX;
		y = y - robotY;
	}

	else if((degree >= 90) && (degree < 180)){
		x = x + robotX;
		y = y - robotY;
	}

	else if((degree >= 180) && (degree < 270)){
		x = x + robotX;
		y = y + robotY;
	}

	else{
		x = x - robotX;
		y = y + robotY;
	}

	ROS_INFO_STREAM("Name: " << name);
	ROS_INFO_STREAM("X location: " << x);
	ROS_INFO_STREAM("Y location: " << y);
	ROS_INFO_STREAM("Z location: " << z);
	ROS_INFO_STREAM("Orientation: " << degree);

}

void Location(const geometry_msgs::PoseWithCovarianceStamped &msg){

	robotX = msg.pose.pose.position.x;
	robotY = msg.pose.pose.position.y;
	robotZ = msg.pose.pose.position.z;
	robotOrientation = msg.pose.pose.orientation;

	//ROS_INFO_STREAM(msg.pose.pose.position);
	//ROS_INFO_STREAM(msg.pose.pose.orientation);
}

void LogicalCameraMessage(const logical_camera_plugin::logicalImage &msg){

	std::string foundTreasure = msg.modelName;

	float x = msg.pose_pos_x;
	float y = msg.pose_pos_y;
	float z = msg.pose_pos_z;

	geometry_msgs::Quaternion quat;

	quat.x = msg.pose_rot_x;
	quat.y = msg.pose_rot_y;
	quat.z = msg.pose_rot_z;
	quat.w = msg.pose_rot_w;

	if(treasureNames.empty()){

		treasureNames.insert(treasureNames.begin(), foundTreasure);
		printCoordinatesName(foundTreasure, x, y, z, quat);
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
			printCoordinatesName(foundTreasure, x, y, z, quat);
		}
	}
}

int main(int argc, char** argv){

ros::init(argc, argv, "treasurelocator");

ros::NodeHandle nh;

ros::Subscriber logcamera = nh.subscribe("/objectsDetected",1000, &LogicalCameraMessage);

ros::Subscriber robotlocation = nh.subscribe("/amcl_pose", 1000, &Location);

ros::spin();

}