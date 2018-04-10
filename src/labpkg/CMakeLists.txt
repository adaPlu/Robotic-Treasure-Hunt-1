cmake_minimum_required(VERSION 2.8.3)
project(labpkg)

find_package(catkin REQUIRED COMPONENTS 
roscpp
std_msgs
geometry_msgs
sensor_msgs
nav_msgs
message_generation
#logical_camera_plugin
tf2
tf2_eigen
tf2_geometry_msgs
tf2_kdl
tf2_msgs
tf2_ros
tf
 )

catkin_package()

include_directories( include ${catkin_INCLUDE_DIRS} )

add_executable(gotopose src/gotopose.cpp)
add_executable(treasurelocator src/treasurelocator.cpp)
add_executable(moveMap src/moveMap.cpp)


target_link_libraries(moveMap ${catkin_LIBRARIES} )
target_link_libraries(treasurelocator ${catkin_LIBRARIES} )
target_link_libraries(gotopose ${catkin_LIBRARIES} )

