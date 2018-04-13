#include <ros/ros.h>
#include <geometry_msgs/Pose2D.h>
#include <iostream>

int main(int argc, char** argv)
{
	ros::init(argc, argv, "getpose");
	ros::NodeHandle nh;
	ros::Publisher send = nh.advertise<geometry_msgs::Pose2D>("targetpose", 1000);
	geometry_msgs::Pose2D pose;
	const double PI = 3.14159;
	double degree;
	while (ros::ok)
	{
		std::cout << "X: ";
		std::cin >> pose.x;
		std::cout << "Y: ";
		std::cin >> pose.y;
		std::cout << "theta (in degrees): ";
		std::cin >> degree;
		pose.theta = degree*PI/180;
		send.publish(pose);
	}
}
