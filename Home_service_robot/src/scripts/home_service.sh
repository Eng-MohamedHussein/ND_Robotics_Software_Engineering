#!/bin/sh
xterm -e "source devel/setup.bash; roslaunch turtlebot_gazebo home_service.launch world_file:=$(rospack find my_robot)/worlds/Mohameds.world"  &
sleep 5
xterm -e "roslaunch turtlebot_gazebo amcl_demo.launch map_file:=$(rospack find amcl_pkg)/maps/myMap.yaml" &
sleep 5
xterm -e "roslaunch turtlebot_rviz_launchers view_navigation.launch config_file:=$(pwd)/src/rvizConfig/home_service.rviz" &
sleep 5
xterm -e "roslaunch home_service_pkg home_service_pkg.launch" &
xterm -e "roslaunch pick_objects pick_objects.launch" 
