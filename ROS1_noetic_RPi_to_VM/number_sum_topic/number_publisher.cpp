#include "ros/ros.h"
#include "std_msgs/Int32MultiArray.h"

int main(int argc, char **argv)
{
  ros::init(argc, argv, "number_publisher");
  ros::NodeHandle n;
  ros::Publisher number_pub = n.advertise<std_msgs::Int32MultiArray>("numbers", 1000);
  ros::Rate loop_rate(10);

  int x=0;
  int y=5;

  while (ros::ok())
  {
    std_msgs::Int32MultiArray msg;
    msg.data.push_back(x); // 第一個數字
    msg.data.push_back(y); // 第二個數字
    ROS_INFO("Two Number: %d and %d", x, y);

    number_pub.publish(msg);
    ros::spinOnce();
    loop_rate.sleep();

    x++;
    y++;
  }

  return 0;
}
