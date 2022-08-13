#!/bin/sh
xterm -e "source devel/setup.bash; roslaunch turtlebot_gazebo turtlebot_world.launch"  &
sleep 3
xterm -e "roslaunch turtlebot_gazebo amcl_demo.launch" &
sleep 3
xterm -e "roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 5
xterm -e "roslaunch turtlebot_teleop keyboard_teleop.launch" 
