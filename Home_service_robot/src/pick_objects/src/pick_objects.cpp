#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

// Define a client for to send goal requests to the move_base server through a SimpleActionClient
typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

int main(int argc, char** argv){
  // Initialize the simple_navigation_goals node
  ros::init(argc, argv, "pick_objects");

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);
  double pick_up_x=2;
  double pick_up_y=2;

  double drop_off_x=1;
  double drop_off_y=-2;

  // Wait 5 sec for move_base action server to come up
  while(!ac.waitForServer(ros::Duration(5.0))){
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal pick_up;
  move_base_msgs::MoveBaseGoal drop_off;
  

  // set up the frame parameters
  pick_up.target_pose.header.frame_id = "map";
  pick_up.target_pose.header.stamp = ros::Time::now();

  drop_off.target_pose.header.frame_id = "map";
  drop_off.target_pose.header.stamp = ros::Time::now();

  // Define a position and orientation for the robot to reach
  pick_up.target_pose.pose.position.x = pick_up_x;
  pick_up.target_pose.pose.position.y = pick_up_y;
  pick_up.target_pose.pose.orientation.w = 1.0;

  drop_off.target_pose.pose.position.x = drop_off_x;
  drop_off.target_pose.pose.position.y = drop_off_y;
  drop_off.target_pose.pose.orientation.w = -1.0;
   // Send the goal position and orientation for the robot to reach
  ROS_INFO("Sending goal");
  ac.sendGoal(pick_up);

  // Wait an infinite time for the results
  ac.waitForResult();

  // Check if the robot reached its goal
  if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
    ROS_INFO("Hooray, the robot reached the pick up zone");
    ros::Duration(15.0).sleep();
    ROS_INFO("Sending goal");
    ac.sendGoal(drop_off);
    // Wait an infinite time for the results
    ac.waitForResult();}
    if(ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED){
      ROS_INFO("Hooray, the robot reached the drop off zone");}
        
  else{
    ROS_INFO("The robot failed to reach the pick up zone");}

  return 0;
}

