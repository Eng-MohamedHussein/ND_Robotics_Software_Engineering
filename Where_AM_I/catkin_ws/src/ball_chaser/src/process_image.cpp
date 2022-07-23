#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>

ros::ServiceClient client;

void drive_bot (float lin_x, float ang_z){
  ROS_INFO_STREAM("drive the bot to the ball");

  ball_chaser::DriveToTarget srv;
  srv.request.linear_x = lin_x;
  srv.request.angular_z = ang_z;

  if(!client.call(srv)){
    ROS_ERROR("failed to call service ");
  }
}

void process_image_callback(const sensor_msgs::Image img)
{
int white_pixel = 255;

bool turn_left = false;
bool turn_right = false;
bool move_forward = false;
  
int leftSide = img.step/3;
int middleSide = 2 * img.step/3;
int rightSide = img.step;
    
// Looping through the image
for(int i = 0; i < img.height * img.step; i+=3)
{
	//checking the ball	
	if (img.data[i] == white_pixel && img.data[i+1] == white_pixel && img.data[i+2] == white_pixel)
	{
    
	        int position = i % img.step;
	        //Ball in left side 
	        if (position >= 0 && position <= leftSide)
		{
		          turn_left = true;
		          turn_right = false;
		          move_forward = false;
		          break;
        	}
		//Ball in the middle side
	        else if (position > leftSide && position <= middleSide)
		{
		          move_forward = true;
		          turn_right = false;
		          turn_left = false;
		          break;
	        }
		//ball in the right side
	        else if (position > middleSide && position <= rightSide)
		{
		          turn_right = true;
		          turn_left = false;
		          move_forward = false;
		          break;
	        }
	}
}
    //using the service to drive the robot
	if(turn_right)
	{
	      drive_bot(0.2,-0.2);
	    }
	else if(turn_left)
	{
	      drive_bot(0.2, 0.2);
	}
	else if(move_forward){
	      drive_bot(0.2, 0.2);
	}
	else if(!move_forward && !turn_left && !turn_right)
	{
	      drive_bot(0.0, 0.0);
	}
}

int main(int argc, char** argv){
  ros::init(argc, argv, "process_image");
  ros::NodeHandle n;

  client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");
  ros::Subscriber sub = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

  ros::spin();
  return 0;
}

