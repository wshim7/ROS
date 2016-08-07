/*
 * LED_tester.cpp
 *
 *  Created on: 2014. 2. 14.
 *      Author: zikprid
 */


#include <ros/ros.h>
#include <roscir/device/client/CTouchButtonClient.h>
#include <roscir/env/Config.h>

int main(int argc, char **argv) {
	ros::init(argc, argv, "roscir_Touch_tester");
	ros::NodeHandle n;
	CTouchButton* touch = CTouchButtonClientProxy::newInstance();

	CTouchButtonData data;

	int robotType = CConfig::getInstance()->getParamValueInt("ROBOT_TYPE");


	cout << "ROBOT_TYPE: " << robotType << endl;

	int roopCnt = 0;
	if(robotType == 7 || robotType ==8){
		roopCnt = 2;
	}else {
		roopCnt = 5;
	}

	ros::Rate loop_rate(10);

	while(ros::ok())
	{
		data = touch->readData(0);

		cout << "Touch DATAs: ";
		for(int i=0; i < roopCnt; i++ )
		{
			cout <<"[" << i <<   "]: " << data.getData()[i] << " ";
		}

		cout<< endl;
		loop_rate.sleep();

		ros::spinOnce();

	}

	return 0;

}


