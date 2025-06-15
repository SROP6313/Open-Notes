#include "ros/ros.h"
#include "std_msgs/Int32MultiArray.h"

void numbersCallback(const std_msgs::Int32MultiArray::ConstPtr& msg)
{
  int sum = 0;
  for(int num : msg->data)
    sum += num;
  ROS_INFO("Sum: %d", sum);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "number_subscriber");
  ros::NodeHandle n;
  ros::Subscriber sub = n.subscribe("numbers", 1000, numbersCallback);
  ros::spin();

  return 0;
}
