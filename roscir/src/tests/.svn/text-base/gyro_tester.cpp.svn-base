/*
 * battery_tester.cpp
 *
 *  Created on: 2014. 2. 14.
 *      Author: zikprid
 */


#include <ros/ros.h>
#include <roscir/device/client/CGyroClient.h>

int main(int argc, char **argv) {
	ros::init(argc, argv, "roscir_gyro_tester");
	ros::NodeHandle n;
	CGyro* gyro = CGyroClientProxy::newInstance();
	CGyroData data(0,0);
	double angle = 0;
	for(int i = 0; i < 10000000; i++) {
		data = gyro->readData();
		angle = data.getAngle();

		cout << "angle " << angle << endl;

		ros::spinOnce();
	}



}


