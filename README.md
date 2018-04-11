# Robotic-Treasure-Hunt
A Robotic Treasure Hunt Designed for UC Merced CSE 180.
Problem description•Given the map of an indoor bounded environment, write a robot controller that finds an unknown number of 
tags hidden in the environment 
•tags are detected by a given sensor (logical camera — more later) 
•You must report (print to the screen):
•how many tags you found •for each tag: identity (string), and absolute pose in the map.

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

Logical Camera
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
