#include <ros/ros.h>
#include <geometry_msgs/Pose2D.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/TransformStamped.h>
#include <tf2_ros/transform_listener.h>
#include <tf2/utils.h>
#include <angles/angles.h>

double targetX;
double targetY;
double targetTheta;

bool getnewpose;

const double distanceTolerance = 0.2;
const double angleTolerance =  ((10) * M_PI / 180.0); //  10 degrees in radians

const double linearvelocity = 0.5;  //translational verlocity for the robot
const double angularvelocity = 0.2; // rotational velocity for the robot;

// callback function getting a new target pose and storing it globally
void subpose(const geometry_msgs::Pose2D msg) {
    targetX = msg.x;
    targetY = msg.y;
    targetTheta = angles::normalize_angle(msg.theta);
    getnewpose = false;
    ROS_INFO_STREAM("Received new target pose " << targetX << " " <<  targetY << " " << targetTheta);
}

// stops the robot by sending a 0 twist
void stopRobot(ros::Publisher &pub) {
   geometry_msgs::Twist velcmd;
   velcmd.linear.x = velcmd.linear.y = velcmd.linear.z = 0;
   velcmd.angular.x = velcmd.angular.y = velcmd.angular.z = 0;
   pub.publish(velcmd);
}

// moves forward the robot by the specified amount
void moveForward(ros::Publisher &pub,double distance) {
  ROS_INFO_STREAM("Moving forward  " << distance << " meters");
  geometry_msgs::Twist velcmd;
  velcmd.linear.x = linearvelocity;
  double sleeptime = distance/linearvelocity;
  velcmd.linear.y = velcmd.linear.z = 0;
  velcmd.angular.x = velcmd.angular.y = velcmd.angular.z = 0;
  ROS_INFO_STREAM("Sending " << std::endl  << velcmd << " for " << sleeptime << " seconds");
  ros::Duration duration(sleeptime);
  ros::Time begin = ros::Time::now();
  while ( ros::Time::now() - begin < duration ) {
    pub.publish(velcmd);
    ros::Duration(0.1).sleep();       
   }
   stopRobot(pub);
}

// turns in place so that the robot eventually faces the given angle
// current is the current heading of the robot, target is the desired heading of the robot
void reorientRobot(ros::Publisher &pub,double current,double target) {
    target = angles::normalize_angle(target);
    geometry_msgs::Twist velcmd;
    velcmd.linear.x = velcmd.linear.y = velcmd.linear.z = 0;
    velcmd.angular.x =  velcmd.angular.y = 0;
    ROS_INFO_STREAM("Reorienting robot from " << current << " to " << target);
    double angulardistance = angles::shortest_angular_distance(current,target);
    ROS_INFO_STREAM("Angular distance " << angulardistance << " radians");
    if ( angulardistance > 0 )
	velcmd.angular.z = angularvelocity;
    else 
        velcmd.angular.z = -angularvelocity;
    double sleeptime = (fabs(angulardistance))/angularvelocity;
    ROS_INFO_STREAM("Sending " << std::endl << velcmd << " for " << sleeptime << " seconds");
    ros::Duration duration(sleeptime);
    ros::Time begin = ros::Time::now();
    while ( ros::Time::now() - begin < duration ) {
	pub.publish(velcmd);
	ros::Duration(0.1).sleep();
    }
    stopRobot(pub);
}

int main(int argc,char **argv) {

    ros::init(argc,argv,"gotopose");
    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe("targetpose",100,subpose);
    tf2_ros::Buffer tfbuffer;
    tf2_ros::TransformListener listener(tfbuffer);
    geometry_msgs::TransformStamped lastpose;
    ros::Publisher twistpub = nh.advertise<geometry_msgs::Twist>("/husky_velocity_controller/cmd_vel",1000);
    bool arrived;
    double currentX;
    double currentY;
    double currentTheta;
    double distanceError;
    double angleError;

    getnewpose = true; // we need to get a new pose
    
    while (ros::ok() ) {
	ROS_INFO_STREAM("Waiting for new taget pose...");
	while (getnewpose == true )  
	    ros::spinOnce();
	ROS_INFO_STREAM("Moving towards target pose.");
	arrived = false;
	while ( not arrived ) {
	    // get current pose
	    try {
		lastpose = tfbuffer.lookupTransform("odom","base_link",ros::Time(0));
	    }
	    catch (tf2::TransformException &ex) {
		ROS_WARN("%s",ex.what());
	    }
	    currentX = lastpose.transform.translation.x;
	    currentY = lastpose.transform.translation.y;
	    currentTheta = angles::normalize_angle(tf2::getYaw(lastpose.transform.rotation));
            ROS_INFO_STREAM("Current pose " << currentX << " " << currentY << " " << currentTheta );
	    distanceError = hypot(currentX-targetX,currentY-targetY);  
	    angleError = fabs(angles::shortest_angular_distance(currentTheta,targetTheta));
	    if ( ( distanceError < distanceTolerance ) && (angleError < angleTolerance) )
		arrived = true;
	    else {
		if ( distanceError > distanceTolerance ) {
		    ROS_INFO_STREAM("Correcting distance error. Reorienting....");
		    reorientRobot(twistpub,currentTheta,atan2(targetY-currentY,targetX-currentX));
		    ROS_INFO_STREAM("Correcting distance error. Moving Forward....");
		    moveForward(twistpub,distanceError);
		}
		else {
		    ROS_INFO_STREAM("Correcting final orientation error. Reorienting....");
		    reorientRobot(twistpub,currentTheta,targetTheta);
		}
	    }
	    
	}
	ROS_INFO_STREAM("Arrived (within tolernace):");
	ROS_INFO_STREAM("Target pose is " <<   targetX << " " <<  targetY << " " << targetTheta);
	ROS_INFO_STREAM("Current pose " << currentX << " " << currentY << " " << currentTheta );
	getnewpose = true; // enable receiving a new pose
    }

}
