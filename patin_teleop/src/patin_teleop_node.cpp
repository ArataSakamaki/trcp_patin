#include <iostream>

#include <ros/ros.h>
#include <boost/shared_ptr.hpp>

#include <std_msgs/String.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>

int trigger_ind = 10;
int acce_ind = 8;
int accel = 1.5;


int main(int argc, char** argv){
  ros::init(argc, argv, "patin_teleop");
  ros::NodeHandle nh;
  ros::Publisher vel_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
  ros::Rate loop_rate(10);

  while(ros::ok()){

    std::cout << "start" << std::endl;

    boost::shared_ptr<sensor_msgs::Joy const> joyMsg =
      ros::topic::waitForMessage<sensor_msgs::Joy>("/joy", nh);

    //std::cout << "message arrived" << std::endl;
    sensor_msgs::Joy joymsg;
    if(joyMsg != NULL){
      joymsg = *joyMsg;
    }else{
      continue;
    }

    if(joymsg.buttons[trigger_ind] == 0){
      std::cout << "not pushed" << std::endl;
      continue;
    }

    int acc = 1;
    if(joymsg.buttons[acce_ind == 0]){
      std::cout << "accel" << std::endl;
      acc = accel;
    }

    geometry_msgs::Twist msg;
    msg.linear.x=joymsg.axes[1]/2*acc;
    msg.linear.y=joymsg.axes[0]/2*acc;

    msg.angular.z=joymsg.axes[2]*acc;

    std::cout << msg << std::endl;

    vel_pub.publish(msg);

    loop_rate.sleep();
  }
}
