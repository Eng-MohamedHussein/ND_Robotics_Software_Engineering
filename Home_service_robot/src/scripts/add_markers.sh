#!/bin/sh
xterm -e "source devel/setup.bash; roslaunch turtlebot_gazebo turtlebot_world.launch world_file:=$(rospack find my_robot)/worlds/Mohameds.world"  &
sleep 5
xterm -e "roslaunch turtlebot_gazebo amcl_demo.launch map_file:=$(rospack find amcl_pkg)/maps/myMap.yaml" &
sleep 5
xterm -e "roslaunch turtlebot_rviz_launchers view_navigation.launch config_file:=$(pwd)/rvizConfig/home_service.rviz" &
sleep 5
xterm -e "roslaunch add_markers add_markers.launch" 
