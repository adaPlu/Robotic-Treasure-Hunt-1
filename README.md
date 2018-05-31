# Robotic-Treasure-Hunt
A Robotic Treasure Hunt Designed for UC Merced CSE 180.
Progams written and designed by Adam Pluguez and Irian Aguiluz
Due to the project being setup on each machine local text files in the build folder of the workspace need to be overwritten or have locations changed for the workspace to compile.

Problem description
•Given the map of an indoor bounded environment, write a robot controller that finds an unknown number of 
tags hidden in the environment 
•tags are detected by a given sensor (logical camera — more later) 
•You must report (print to the screen):
•how many tags you found 
•for each tag: identity (string), and absolute pose in the map.

Available nodes
•amcl for localization 
•move_base to move the robot around 
•map_server to get the map of the environment
•logical camera to detect objects in the environment

Map of the Environment
•Can be read from disk or retrieved from map_server
•robot produced. Mostly accurate but with some imprecision 
•your code must be generic with respect to the map,
i.e., your code will be tested on a map different from the one you are given for testing 
•Pseudo info available either from disk (yaml file) or map_server

Logical Camera Description
•Posts info on /objectsDetected
•publishes messages of type message of type logical_camera_plugin/logicalImage
•Example:
modelName: couch_0 
pose_pos_x: 1.47894906998 
pose_pos_y: -1.03072357178 
pose_pos_z: -0.368999242783 
pose_rot_x: -1.08818733224e-06 
pose_rot_y: -2.45950900535e-07 
pose_rot_z: 0.705672979355 
pose_rot_w: 0.708537697792

Run Instructions:
	There is a launch file for our project called “scavenger.launch”. This launch file runs all necessary nodes and outputs treasure locations to the screen.
Strategy:
	Our strategy for finding the treasures was to create two separate nodes, one for moving around the environment without colliding into obstacles and another to continually scan for treasures. The movement node is called “gototreasure”, while the locator node is called ”treasurelocator”.
The “gototreasure” node uses move-base to move to assigned goals. The dwa planner goal tolerances were adjusted in planner.yaml so that the robot did not overcompensate trying to reach an exact point, as this was an obvious problem early on. There were also some minor adjustments to occdist_scale to reduce object collisions. As well as minor changes to costmap_common.yaml, such as increasing the  inflation radius to reduce the likelihood of the robot coming to close to various obstacles and getting stuck. The approach used to cover the entire map area involved assuming a unknown amount of obstacles randomly distributed. A efficient group of fixed points which would traverse the entire map with no obstacles was planned. At each goal point a 360 degree rotation was performed to increase the chances of finding a treasure near a given goal. Also to decrease the number of total points required to cover the entire map space. These programmed points and 360 degree rotation combined with the dwa local planner allow the robot to successfully traverse most if not all areas of a given map of the same size regardless of obstacle locations. 
The node “treasurelocator” is responsible for using the logical camera to scan for treasures, print out the treasure’s name, and its coordinates in relation to the map. The logical camera gives the location of the treasure in relation to the robots current position.  In order to get the location of the treasure in relation to the map, first we use amcl get the location of the robot. From here we can use change of coordinates to get the estimated location of the treasure. Due to their being multiple treasures, in order to keep track of which treasures have already been found, a global vector was made containing the string id of each treasure. Since they all have a unique identifying name. Once it has been concluded that the treasure has not been found by checking the id in the vector  the new treasure’s id is placed in the vector and then its id and coordinates are printed. If the treasure has already been found before nothing is done and the robot keeps searching through the map for treasures.

