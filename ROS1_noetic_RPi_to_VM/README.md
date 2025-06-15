# ROS1 Noetic Communication Setup: Raspberry Pi 4 & Ubuntu 20.04 in VirtualBox
## Raspberry Pi 4:
* **Step 1** : Install OS [Debian/Raspbian Buster](https://downloads.raspberrypi.com/raspios_oldstable_armhf/images/raspios_oldstable_armhf-2023-05-03/) on Raspberry Pi 4
* **Step 2** : Add the official ROS Debian repo to the OS
```bash
sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu buster main" > /etc/apt/sources.list.d/ros-noetic.list'
```
* **Step 3** : Add official ROS key which is not specific to Noetic but for all ROS distros
```bash
sudo apt-key adv --keyserver 'hkp://keyserver.ubuntu.com:80' --recv-key C1CF6E31E6BADE8868B172B4F42ED6FBAB17C654
```
* **Step 4** : Pull all meta info of ROS Noetic packages
```bash
sudo apt update
```
* **Step 5** : Install build dependencies on Raspberry Pi 4
```bash
sudo apt-get install -y python-rosdep python-rosinstall-generator python-wstool python-rosinstall build-essential cmake
```
* **Step 6** : Set up ROS Noetic dependency sources/repos
```bash
sudo rosdep init
rosdep update
```
* **Step 7** : Fetch & Install ROS Noetic dependencies
```bash
mkdir ~/ros_catkin_ws
cd ~/ros_catkin_ws
rosinstall_generator ros_comm --rosdistro noetic --deps --wet-only --tar > noetic-ros_comm-wet.rosinstall
sudo apt-get install -y python3-wstool (or sudo apt-get install python-wstool)
wstool init src noetic-ros_comm-wet.rosinstall
rosdep install -y --from-paths src --ignore-src --rosdistro noetic -r --os=debian:buster
```
> * ***Extra*** : It is recommenced to increase the swap space, which is used when the physical memory space on your Raspberry Pi is used up
> ```bash
> sudo dphys-swapfile swapoff
> sudoedit /etc/dphys-swapfile
> ```
> Edit the file to increase the swap space form 100 MB to 1024 MB (1 GB): **CONF_SWAPSIZE=1024**
> ```bash
> sudo dphys-swapfile setup
> sudo dphys-swapfile swapon
> free -m
> ```
> Check if the swap status: Swap Total about 1024

* **Step 8** : Compiling Noetic packages on Raspberry Pi 4
```bash
sudo src/catkin/bin/catkin_make_isolated --install -DCMAKE_BUILD_TYPE=Release --install-space /opt/ros/noetic -j1 -DPYTHON_EXECUTABLE=/usr/bin/python3
```
* **Step 9** : Verify Noetic installation on Raspberry Pi 4
```bash
source /opt/ros/noetic/setup.bash
roscore
```
---
## Ubuntu 20.04 in VirtualBox:
* **Step 1** : Install OS [Ubuntu 20.04 LTS](https://releases.ubuntu.com/20.04/) in VirtualBox
> * ***Extra*** : It is recommenced to install the new terminal app
> ```
> sudo apt install terminator
> ```
> Press Ctrl+Alt+T to open terminator
### Install ROS Noetic
* **Step 2** : Set up the ROS repository
```bash
sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu focal main" > /etc/apt/sources.list.d/ros-latest.list'
```
* **Step 3** : Set up the ROS key
```bash
sudo apt install curl
curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc | sudo apt-key add -
```
* **Step 4** : Update the package lists
```bash
sudo apt update
```
* **Step 5** : Install ROS Noetic
```bash
sudo apt install ros-noetic-desktop
```
* **Step 6** : Initialize rosdep & Install rosinstall
```bash
sudo apt install python3-rosdep 
sudo apt install python3-rosinstall 
sudo apt install python3-rosinstall-generator 
sudo apt install python3-wstool 
sudo apt install build-essential
sudo rosdep init
rosdep update
```
* **Step 7** : Set up the ROS environment variables
```bash
echo "source /opt/ros/noetic/setup.bash" >> ~/.bashrc
source ~/.bashrc
```
* **Step 8** : Verify the installation
```bash
rosversion -d
roswtf
roscore
```
Open a new terminal and run
```bash
rosrun turtlesim turtlesim_node
```
Open another new terminal and run
```bash
rosrun turtlesim turtle_teleop_key
```
### Setup Communication with Raspberry Pi 4
* **Step 9** : 選擇此虛擬機->設定->網路->把預設的NAT改為橋接介面卡->選擇電腦連接的對應網卡
* **Step 10** : 查看虛擬機與樹莓派的的ip與hostname
```bash
ifconfg
hostname
```
* **Step 11.1** : 虛擬機中運行`sudoedit /etc/hosts`打開檔案，添加下面箭頭那兩行 (__注意：ip與hostname之間一定要用Tab鍵__)
```
127.0.0.1       localhost
127.0.1.1       eric-VirtualBox
192.168.43.216  eric-VirtualBox  <---
192.168.43.52   raspberrypi  <---

# The following lines are desirable for IPv6 capable hosts
::1     ip6-localhost ip6-loopback
fe00::0 ip6-localnet
ff00::0 ip6-mcastprefix
ff02::1 ip6-allnodes
ff02::2 ip6-allrouters
```
* **Step 11.2** : 樹莓派中運行`sudo nano /etc/hosts`打開檔案，添加下面兩行 (__注意：ip與hostname之間一定要用Tab鍵__)
```
127.0.0.1       localhost
192.168.43.216  eric-VirtualBox  <---
192.168.43.52   raspberrypi  <---
::1             localhost ip6-localhost ip6-loopback
ff02::1         ip6-allnodes
ff02::2         ip6-allrouters

127.0.1.1               raspberrypi
```
* **Step 12** : 雙方重啟網路
```bash
sudo /etc/init.d/networking restart
```
或
```bash
sudo /etc/init.d/network-manager restart
```
* **Step 13** : 雙方安裝Chrony
```bash
sudo apt-get install chrony
```
* **Step 14** : 雙方安裝SSH
```bash
sudo apt-get install openssh-server
```
* **Step 15.1** : 虛擬機查看樹莓派網路連接
```bash
ping raspberrypi
```
* **Step 15.2** : 樹莓派查看虛擬機網路連接
```bash
ping eric-VirtualBox
```
* **Step 16.1** : 虛擬機添加環境變量，運行`sudoedit ~/.bashrc`，在檔案最底添加以下幾行 (__主機為樹莓派__)
```bash
source /opt/ros/noetic/setup.bash
source ~/ros_catkin_ws/devel/setup.bash
export ROS_HOSTNAME=eric-VirtualBox
export ROS_MASTER_URI=http://raspberrypi:11311
```
* **Step 16.2** : 樹莓派添加環境變量，運行`sudo nano ~/.bashrc`，在檔案最底添加以下幾行 (__主機為樹莓派__)
```bash
source /opt/ros/noetic/setup.bash
source ~/ros_catkin_ws/devel/setup.bash
export ROS_HOSTNAME=raspberrypi
export ROS_MASTER_URI=http://raspberrypi:11311
```
* **Step 17** : 樹莓派運行publisher節點，虛擬機運行`rostopic list`即可查看到發布的節點名稱
