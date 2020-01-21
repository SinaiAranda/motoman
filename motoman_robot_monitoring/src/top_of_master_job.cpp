#include <ros/ros.h>

#include "motoman_robot_monitoring/motoman_robot_monitoring.h"

int main(int argc, char ** argv) {
  ros::init(argc, argv, "top_of_master_job");
  ros::NodeHandle nh;

  ros::Publisher top_of_master_job_pub = nh.advertise<std_msgs::String>("top_of_master_job", 1000);

  ros::AsyncSpinner spinner(2);
  ros::Rate loop_rate(30);

  spinner.start();

  while (ros::ok()) {
    std_msgs::String msg;

    std::stringstream ss;
    ss << top_of_master_job();
    msg.data = ss.str();

    ROS_INFO("%s", msg.data.c_str());

    top_of_master_job_pub.publish(msg);
    loop_rate.sleep();
  }
  return 0;
}
