cmake_minimum_required(VERSION 2.8.3)
project(motoman_robot_monitoring)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS roslaunch
  roscpp
  rospy
  std_msgs
  motoman_msgs
)
roslaunch_add_file_check(launch)

find_package(Boost REQUIRED COMPONENTS system)

################################################
## Declare ROS dynamic reconfigure parameters ##
################################################

## To declare and build dynamic reconfigure parameters within this
## package, follow these steps:
## * In the file package.xml:
##   * add a build_depend and a exec_depend tag for "dynamic_reconfigure"
## * In this file (CMakeLists.txt):
##   * add "dynamic_reconfigure" to
##     find_package(catkin REQUIRED COMPONENTS ...)
##   * uncomment the "generate_dynamic_reconfigure_options" section below
##     and list every .cfg file to be processed

## Generate dynamic reconfigure parameters in the 'cfg' folder
# generate_dynamic_reconfigure_options(
#   cfg/DynReconf1.cfg
#   cfg/DynReconf2.cfg
# )

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if your package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need

catkin_package()

catkin_package(
  INCLUDE_DIRS include
  CATKIN_DEPENDS
  LIBRARIES 
  DEPENDS Boost
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
include_directories(
  include
  ${catkin_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
)


add_executable(running src/running.cpp)
target_link_libraries(running ${catkin_LIBRARIES} ${Boost_LIBRARIES})
#add_dependencies(running ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

add_executable(servo_is_on src/servo_is_on.cpp)
target_link_libraries(servo_is_on ${catkin_LIBRARIES} ${Boost_LIBRARIES})
add_dependencies(servo_is_on ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

add_executable(top_of_master_job src/top_of_master_job.cpp)
target_link_libraries(top_of_master_job ${catkin_LIBRARIES} ${Boost_LIBRARIES})
add_dependencies(top_of_master_job ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

add_executable(alarm_error_occurred src/alarm_error_occurred.cpp)
target_link_libraries(alarm_error_occurred ${catkin_LIBRARIES} ${Boost_LIBRARIES})
add_dependencies(alarm_error_occurred ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

add_executable(battery_alarm src/battery_alarm.cpp)
target_link_libraries(battery_alarm ${catkin_LIBRARIES} ${Boost_LIBRARIES})
add_dependencies(battery_alarm ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

add_executable(remote_mode_selected src/remote_mode_selected.cpp)
target_link_libraries(remote_mode_selected ${catkin_LIBRARIES} ${Boost_LIBRARIES})
add_dependencies(remote_mode_selected ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

add_executable(play_mode_selected src/play_mode_selected.cpp)
target_link_libraries(play_mode_selected ${catkin_LIBRARIES} ${Boost_LIBRARIES})
add_dependencies(play_mode_selected ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

add_executable(teach_mode_selected src/teach_mode_selected.cpp)
target_link_libraries(teach_mode_selected ${catkin_LIBRARIES} ${Boost_LIBRARIES})
add_dependencies(teach_mode_selected ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

#############
## Testing ##
#############

# headers
install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
)

# other files
install(DIRECTORY
    launch
    include
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})

install(PROGRAMS scripts/motoman_robot_monitoring.py
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

install(DIRECTORY include/${PROJECT_NAME}/
  DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION})

install(TARGETS teach_mode_selected play_mode_selected remote_mode_selected battery_alarm alarm_error_occurred top_of_master_job servo_is_on running
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION})

install(DIRECTORY launch
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION})
#############
## Testing ##
#############

if(CATKIN_ENABLE_TESTING)
  find_package(roslint REQUIRED)
  roslint_cpp()
endif()
