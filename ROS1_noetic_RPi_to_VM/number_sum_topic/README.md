# Simple Topic Example: Sum two number
## Ubuntu 20.04 & Raspberry Pi 4:
* **Step 1** : Create a new package
```bash
cd ros_catkin_ws/src
catkin_create_pkg sum_publisher_subscriber std_msgs rospy roscpp
```
* **Step 2** : Create Publisher and Subscriber C++ file
```bash
cd sum_publisher_subscriber/src
touch number_publisher.cpp
touch number_subscriber.cpp
```
Publisher: `number_publisher.cpp` (Raspberry Pi 4)
```cpp
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
```
Subscriber: `number_subscriber.cpp` (Ubuntu 20.04)
```cpp
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
```
* **Step 3** : Must make sure the following content in `CMakeList.txt` & `package.xml`

CMakeList.txt
```
add_executable(number_publisher src/number_publisher.cpp)
target_link_libraries(number_publisher ${catkin_LIBRARIES})
add_executable(number_subscriber src/number_subscriber.cpp)
target_link_libraries(number_subscriber ${catkin_LIBRARIES})
```
package.xml
```xml
<build_depend>roscpp</build_depend>
<build_depend>std_msgs</build_depend>
<build_export_depend>roscpp</build_export_depend>
<build_export_depend>std_msgs</build_export_depend>
<exec_depend>roscpp</exec_depend>
<exec_depend>std_msgs</exec_depend>
```
* **Step 4** : Compile the workspace
```bash
cd ~/ros_catkin_ws
catkin_make
source ~/ros_catkin_ws/devel/setup.bash
```
* **Step 5** : Run nodes

Raspberry Pi 4
```bash
cd ~/ros_catkin_ws
roscore
```
Open another terminal
```bash
cd ~/ros_catkin_ws
rosrun sum_publisher_subscriber number_publisher
```
Ubuntu 20.04
```bash
cd ~/ros_catkin_ws
rosrun sum_publisher_subscriber number_subscriber
```
