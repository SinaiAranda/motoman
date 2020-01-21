#include <ros/ros.h>

#include "motoman_robot_monitoring/motoman_robot_monitoring.h"

int main(int argc, char ** argv) {
  ros::init(argc, argv, "remote_mode_selected");
  ros::NodeHandle nh;

  ros::Publisher remote_mode_selected_pub = nh.advertise<std_msgs::String>("remote_mode_selected", 1000);

  ros::AsyncSpinner spinner(2);
  ros::Rate loop_rate(30);

  spinner.start();

  while (ros::ok()) {
    std_msgs::String msg;

    std::stringstream ss;
    ss << remote_mode_selected();
    msg.data = ss.str();

    ROS_INFO("%s", msg.data.c_str());

    remote_mode_selected_pub.publish(msg);
    loop_rate.sleep();
  }
  return 0;
}
