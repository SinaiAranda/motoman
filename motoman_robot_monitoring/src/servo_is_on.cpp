#include <ros/ros.h>

#include "motoman_robot_monitoring/motoman_robot_monitoring.h"

int main(int argc, char ** argv) {
  ros::init(argc, argv, "servo_is_on");
  ros::NodeHandle nh;

  ros::Publisher servo_is_on_pub = nh.advertise<std_msgs::String>("servo_is_on", 1000);

  ros::AsyncSpinner spinner(2);
  ros::Rate loop_rate(30);

  spinner.start();

  while (ros::ok()) {
    std_msgs::String msg;

    std::stringstream ss;
    ss << servo_is_on();
    msg.data = ss.str();

    ROS_INFO("%s", msg.data.c_str());

    servo_is_on_pub.publish(msg);
    loop_rate.sleep();
  }
  return 0;
}
