#include <ros/ros.h>

#include "motoman_robot_monitoring/motoman_robot_monitoring.h"

int main(int argc, char ** argv) {
  ros::init(argc, argv, "alarm_error_occurred");
  ros::NodeHandle nh;

  ros::Publisher alarm_error_occurred_pub = nh.advertise<std_msgs::String>("alarm_error_occurred", 1000);

  ros::AsyncSpinner spinner(2);
  ros::Rate loop_rate(30);

  spinner.start();

  while (ros::ok()) {
    std_msgs::String msg;

    std::stringstream ss;
    ss << alarm_error_occurred();
    msg.data = ss.str();

    ROS_INFO("%s", msg.data.c_str());

    alarm_error_occurred_pub.publish(msg);
    loop_rate.sleep();
  }
  return 0;
}
