/*
 * wheel.cpp
 *
 *  Created on: 2014. 1. 7.
 *      Author: robocare
 */
#include <ros/ros.h>
#include <ros/package.h>
#include <roscir/device/client/CWheelClient.h>
#include <roscir/env/Config.h>
#include <string>

using namespace std;

int main(int argc, char **argv) {
	ros::init(argc, argv, "roscir_wheel_test");

	CConfig* config = CConfig::getInstance();

	string ip = config->getParamValue("wheel.device.server.ip");
	ROS_INFO("wheel.server.ip : %s", ip.c_str());

	string path = ros::package::getPath("roscir");
	ROS_INFO("path: %s", path.c_str());
	ROS_INFO("examples");
	return -1;
}



