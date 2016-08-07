/*
 * LogTester.cpp
 *
 *  Created on: 2014. 1. 14.
 *      Author: robocare
 */

#include <ros/ros.h>
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
	ros::init(argc, argv, "Logtester");
	ros::NodeHandle nh;

	cout<<"한글 console out"<<endl;
	ROS_INFO("한글 로깅");

	return -1;
}



