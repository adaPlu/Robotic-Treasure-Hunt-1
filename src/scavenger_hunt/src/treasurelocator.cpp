#include <ros/ros.h>
#include <logical_camera_plugin/logicalImage.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <string>
#include <vector>
#include <geometry_msgs/Quaternion.h>
#include <angles/angles.h>
#include <tf/transform_datatypes.h>
#include <tf/tf.h>

//vector holding names of treasure
std::vector<std::string> treasureNames;

//amcl values to know pose and orientation
float robotX, robotY, robotZ;
geometry_msgs::Quaternion robotOrientation;

void printCoordinatesName(std::string name, float x, float y, float z, geometry_msgs::Quaternion ori){

	tf::Quaternion Brot;
	tf::quaternionMsgToTF(robotOrientation, Brot);
	tf::Matrix3x3 BrotA(Brot);

	tf::Vector3 Col0 = BrotA.getColumn(0);
	tf::Vector3 Col1 = BrotA.getColumn(1);
	tf::Vector3 Col2 = BrotA.getColumn(2);

	float xx, xy, xz;
	float yx, yy, yz;
	float zx, zy, zz;

	xx = Col0.getX(); xy = Col1.getX(); xz = Col2.getX();
	yx = Col0.getY(); yy = Col1.getY(); yz = Col2.getY();
	zx = Col0.getZ(); zy = Col1.getZ(); zz = Col2.getZ();

	float ApX = (x*xx + y*xy + z*xz) + robotX;
	float ApY = (x*yx + y*yy + z*yz) + robotY;
	float ApZ = (x*zx + y*zy + z*zz) + robotZ;

	ROS_INFO_STREAM("Name: " << name);
	ROS_INFO_STREAM("X location: " << ApX);
	ROS_INFO_STREAM("Y location: " << ApY);
	ROS_INFO_STREAM("Z location: " << ApZ);
}

//amcl_pose getting the location of the gazebo in the map
void Location(const geometry_msgs::PoseWithCovarianceStamped &msg){

	robotX = msg.pose.pose.position.x;
	robotY = msg.pose.pose.position.y;
	robotZ = msg.pose.pose.position.z;
	robotOrientation = msg.pose.pose.orientation;
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

	//if the vector was initially empty then we place
	//it in the vector and print the coordinates

	if(treasureNames.empty()){

		treasureNames.insert(treasureNames.begin(), foundTreasure);
		printCoordinatesName(foundTreasure, x, y, z, quat);
	}

	else{
		int vecsize = treasureNames.size();
		bool found = false;

	//going through the vector to see if the treasure has already been found
		for(int i=0; i < vecsize; i++){

			std::string knownTreasure = treasureNames.at(i);

			if(foundTreasure.compare(knownTreasure) == 0){

				found = true;
				break;
			}
		}

	//checking to see if the name was found in the vector if it wasent
	//then we put it in the vector and print the name and coordinates

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