# Simple Service Example: Sum two number
## Ubuntu 20.04 & Raspberry Pi 4:
* **Step 1** : Create a new package of simple service
```bash
cd ros_catkin_ws/src
catkin_create_pkg service_example std_msgs rospy roscpp
cd service_example
mkdir srv
cd srv
touch AddTwoInts.srv
```
Edit the `AddTwoInts.srv` with the following content
```
int64 a
int64 b
---
int64 sum
```
* **Step 2** : Modify or add the following content in `CMakeList.txt` & `package.xml`

CMakeList.txt
```
find_package(catkin REQUIRED COMPONENTS
  rospy
  std_msgs
  message_generation
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES add_ints_service
  CATKIN_DEPENDS rospy std_msgs message_runtime
#  DEPENDS system_lib
)

add_service_files(
  FILES
  AddTwoInts.srv
)

generate_messages(
  DEPENDENCIES
  std_msgs
)
```
package.xml
```xml
<build_depend>message_generation</build_depend>
<exec_depend>message_runtime</exec_depend>
```
* **Step 3** : Write the service nodes
```bash
cd ~/ros_catkin_ws/src/service_example
mkdir scripts
cd scripts
touch add_two_ints_server.py
touch add_two_ints_client.py
```
Server node: `add_two_ints_server.py` (Raspberry Pi 4)
```python
#!/usr/bin/env python3
import rospy
from service_example.srv import AddTwoInts, AddTwoIntsResponse

def handle_add_two_ints(req):
    print("Returning [%s + %s = %s]"%(req.a, req.b, (req.a + req.b)))
    return AddTwoIntsResponse(req.a + req.b)

def add_two_ints_server():
    rospy.init_node('add_two_ints_server')
    s = rospy.Service('add_two_ints', AddTwoInts, handle_add_two_ints)
    print("Ready to add two ints.")
    rospy.spin()

if __name__ == "__main__":
    add_two_ints_server()
```
Client node: `add_two_ints_client.py` (Ubuntu 20.04)
```python
#!/usr/bin/env python3
import sys
import rospy
from service_example.srv import AddTwoInts

def add_two_ints_client(x, y):
    rospy.wait_for_service('add_two_ints')
    try:
        add_two_ints = rospy.ServiceProxy('add_two_ints', AddTwoInts)
        resp1 = add_two_ints(x, y)
        return resp1.sum
    except rospy.ServiceException as e:
        print("Service call failed: %s"%e)

if __name__ == "__main__":
    if len(sys.argv) == 3:
        x = int(sys.argv[1])
        y = int(sys.argv[2])
    else:
        sys.exit(1)
    print("Requesting %s+%s"%(x, y))
    print("%s + %s = %s"%(x, y, add_two_ints_client(x, y)))
```
* **Step 4** : Modify execution permissions of script files and Compile
```bash
chmod +x ~/ros_catkin_ws/src/service_example/scripts/*.py
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
rosrun service_example add_two_ints_server.py
```
Ubuntu 20.04
```bash
cd ~/ros_catkin_ws
rosrun service_example add_two_ints_client.py 52 34
```
