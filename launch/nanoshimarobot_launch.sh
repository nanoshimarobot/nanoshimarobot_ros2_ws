#!/bin/bash
echo $ROS_DOMAIN_ID
source /opt/ros/foxy/setup.bash
source $(dirname $0)/../install/local_setup.bash
export RCUTILS_COLORIZED_OUTPUT=1

ros2 daemon stop
ros2 daemon start

ros2 launch nanoshimarobot_bringup nanoshimarobot.launch.py