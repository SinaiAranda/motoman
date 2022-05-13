cmake_minimum_required(VERSION 2.8.3)

project(motoman_sda20d_with_gripper_hole_kinect_support)

find_package(catkin REQUIRED  COMPONENTS
    roscpp
    sensor_msgs
)

catkin_package(
  CATKIN_DEPENDS    
)

find_package(roslaunch)

