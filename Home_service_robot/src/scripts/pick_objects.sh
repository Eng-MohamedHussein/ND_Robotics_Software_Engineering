#!/bin/sh
xterm -e "source devel/setup.bash; roslaunch turtlebot_gazebo home_service.launch world_file:=$(rospack find my_robot)/worlds/Mohameds.world "  &
sleep 5
xterm -e "roslaunch turtlebot_gazebo amcl_demo.launch map_file:=$(rospack find amcl_pkg)/maps/myMap.yaml" &
sleep 10
xterm -e "roslaunch turtlebot_rviz_launchers view_navigation.launch " &
sleep 10
xterm -e "roslaunch pick_objects pick_objects.launch" 
