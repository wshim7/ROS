/*
 * battery_tester.cpp
 *
 *  Created on: 2014. 2. 14.
 *      Author: zikprid
 */


#include <ros/ros.h>
#include <roscir/device/client/CBatteryClient.h>

int main(int argc, char **argv) {
	ros::init(argc, argv, "roscir_battery_tester");
	ros::NodeHandle n;
	CBattery* battery = CBatteryClientProxy::newInstance();
	CBatteryData data;
	int voltage = 0;
	for(int i = 0; i < 100; i++) {
		data = battery->readData(0);
		voltage = data.getData()[0];
		printf("voltage : %d", voltage);
		ROS_DEBUG("voltage : %d", voltage);
	}

	ros::spin();

}


