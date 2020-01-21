#include <ros/ros.h>

#include "motoman_robot_monitoring/motoman_robot_monitoring.h"

int main(int argc, char ** argv) {
  ros::init(argc, argv, "battery_alarm");
  ros::NodeHandle nh;

  ros::Publisher battery_alarm_pub = nh.advertise<std_msgs::String>("battery_alarm", 1000);

  ros::AsyncSpinner spinner(2);
  ros::Rate loop_rate(30);

  spinner.start();

  while (ros::ok()) {
    std_msgs::String msg;

    std::stringstream ss;
    ss << battery_alarm();
    msg.data = ss.str();

    ROS_INFO("%s", msg.data.c_str());

    battery_alarm_pub.publish(msg);
    loop_rate.sleep();
  }
  return 0;
}
