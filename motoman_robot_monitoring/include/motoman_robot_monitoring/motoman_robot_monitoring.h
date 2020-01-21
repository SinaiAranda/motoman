#ifndef MOTOMAN_ROBOT_MONITORING
#define MOTOMAN_ROBOT_MONITORING

#include "std_msgs/String.h"
#include <sstream>

#include "motoman_msgs/ReadSingleIO.h"

int ReadValvue(int address) {
  ros::NodeHandle nh;
  ros::ServiceClient read_io = nh.serviceClient<motoman_msgs::ReadSingleIO> ("read_single_io");

  motoman_msgs::ReadSingleIO::Request read_req;
  motoman_msgs::ReadSingleIO::Response read_res;

  read_req.address = address;
  bool success = read_io.call(read_req, read_res);

  if (success) {
    ROS_INFO_STREAM("Read: " << read_res.value);
  } else {
    ROS_ERROR_STREAM("Failed to Read");
  }
  return read_res.value;
}

int running() {
  return ReadValvue(30010);
}

int servo_is_on() {
  return ReadValvue(30011);
}

int top_of_master_job() {
  return ReadValvue(30012);
}

int alarm_error_occurred() {
  return ReadValvue(30013);
}

int battery_alarm() {
  return ReadValvue(30014);
}

int remote_mode_selected() {
  return ReadValvue(30015);
}

int play_mode_selected() {
  return ReadValvue(30016);
}

int teach_mode_selected() {
  return ReadValvue(30017);
}


#endif
