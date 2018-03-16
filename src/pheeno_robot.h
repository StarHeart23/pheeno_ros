#ifndef GUARD_PHEENO_ROBOT_H
#define GUARD_PHEENO_ROBOT_H

#include "ros/ros.h"
#include "std_msgs/Float32.h"
#include "std_msgs/Int16.h"
#include "geometry_msgs/Twist.h"
#include "nav_msgs/Odometry.h"
#include "pheeno_markov_chain/ColorsFound.h"
#include <vector>
#include <complex>
#include <cstdlib>

class PheenoRobot {

public:
  // Constructor
  PheenoRobot(std::string pheeno_name);

  // Pheeno name
  std::string pheeno_namespace_id;

  // Sensor Messages
  std_msgs::Float32 ir_sensor_center;
  std_msgs::Float32 ir_sensor_back;
  std_msgs::Float32 ir_sensor_right;
  std_msgs::Float32 ir_sensor_left;
  std_msgs::Float32 ir_sensor_c_right;
  std_msgs::Float32 ir_sensor_c_left;
  std_msgs::Int16 ir_sensor_bottom;
  std::vector<double> ir_sensor_values;

  // Odometry Messages
  nav_msgs::Odometry odom_msg;
  std::vector<double> odom_pose_position;
  std::vector<double> odom_pose_orient;
  std::vector<double> odom_twist_linear;
  std::vector<double> odom_twist_angular;

  // Camera Messages
  std::vector<bool> color_state_facing;

  // Public Sensor Methods
  bool irSensorTriggered(float sensor_limits);

  // Public Movement Methods
  double randomTurn(float angular = 0.06);
  void avoidObstaclesLinear(std::vector<double> values, double &linear, double &angular,
                            float angular_velocity = 1.2, float linear_velocity = 0.08,
                            double range_to_avoid = 20.0);
  void avoidObstaclesAngular(std::vector<double>, double &angular, double &random_turn_value,
                             float angular_velocity = 1.2, double range_to_avoid = 20.0);

  // Public Publishers
  void publish(geometry_msgs::Twist velocity);

  // Public camera methods
  bool checkFrontColor(int color);

private:
  // ROS Node handle
  ros::NodeHandle nh_;

  // Private Subscribers
  ros::Subscriber sub_ir_center_;
  ros::Subscriber sub_ir_right_;
  ros::Subscriber sub_ir_left_;
  ros::Subscriber sub_ir_cr_;
  ros::Subscriber sub_ir_cl_;
  ros::Subscriber sub_ir_back_;
  ros::Subscriber sub_ir_bottom_;
  ros::Subscriber sub_pheeno_cam_;
  ros::Subscriber sub_odom_;

  // Private Publishers
  ros::Publisher pub_cmd_vel_;

  // IR Callback Methods
  void irSensorCenterCallback(const std_msgs::Float32::ConstPtr& msg);
  void irSensorBackCallback(const std_msgs::Float32::ConstPtr& msg);
  void irSensorRightCallback(const std_msgs::Float32::ConstPtr& msg);
  void irSensorLeftCallback(const std_msgs::Float32::ConstPtr& msg);
  void irSensorCRightCallback(const std_msgs::Float32::ConstPtr& msg);
  void irSensorCLeftCallback(const std_msgs::Float32::ConstPtr& msg);
  void irSensorBottomCallback(const std_msgs::Int16::ConstPtr& msg);
  
  // Odom Callback Methods
  void odomCallback(const nav_msgs::Odometry::ConstPtr& msg);

  // Camera Callback Modules
  void piCamCallback();
  void piCamColorCallback(const pheeno_markov_chain::ColorsFound& msg);
};

#endif //GUARD_PHEENO_ROBOT_H
