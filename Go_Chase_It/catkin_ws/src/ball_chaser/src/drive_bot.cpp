#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include <string.h>
#include "ball_chaser/DriveToTarget.h"

// ROS::Publisher motor commands;
ros::Publisher motor_command_publisher;


bool handle_drive_request(ball_chaser::DriveToTarget::Request& req , ball_chaser::DriveToTarget::Response& res)
{

geometry_msgs::Twist motorCommand;
        // Set wheel velocities
        motorCommand.linear.x = req.linear_x;
        motorCommand.angular.z = req.angular_z;
        // Publish angles to drive the robot
        motor_command_publisher.publish(motorCommand);

res.msg_feedback= "The linear velocity x were set to: " + std::to_string(motorCommand.linear.x) +"\n The angular velocity z were set to:"+std::to_string(motorCommand.angular.z);
ROS_INFO_STREAM(res.msg_feedback);


return true;
}
int main(int argc, char** argv)
{
    // Initialize a ROS node
    ros::init(argc, argv, "drive_bot");

    // Create a ROS NodeHandle object
    ros::NodeHandle n;

    // Inform ROS master that we will be publishing a message of type geometry_msgs::Twist on the robot actuation topic with a publishing queue size of 10
    motor_command_publisher = n.advertise<geometry_msgs::Twist>("/cmd_vel", 10);

    
	ros::ServiceServer service = n.advertiseService("ball_chaser/command_robot",	handle_drive_request);

    
    ros::spin();

    return 0;
}
