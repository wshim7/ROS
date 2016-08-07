/*
 * LED_tester.cpp
 *
 *  Created on: 2014. 2. 14.
 *      Author: zikprid
 */


#include <ros/ros.h>
#include <roscir/device/client/CLightEmittingDiodeClient.h>

int main(int argc, char **argv) {
	ros::init(argc, argv, "roscir_LED_tester");
	ros::NodeHandle n;
	CLightEmittingDiode* led = CLightEmittingDiodeClientProxy::newInstance();

	int id, red, green, blue;

	while(ros::ok()){

		cout << "MERO TESTER" << endl;
		cout << "LED ID (R: 1 L:2), RED (ON: 1, OFF: 0), GREEN (ON: 1, OFF: 0), BLUE (ON: 1, OFF: 0)" << endl;
		cout << "ID: " ;
		cin >>id;
		cin.clear();

		cout << "Red: " ;
		cin >>red;
		cin.clear();

		cout << "Green: " ;
		cin >>green;
		cin.clear();

		cout << "Blue: " ;
		cin >>blue;
		cin.clear();


		if(id ==1 ){
			id = 0xF3;
		}else if(id ==2){
			id = 0xF4;
		}

		if(red ==0 ){
			red = 0x00;
		}else if(red ==1){
			red = 0x01;
		}

		if(green ==0 ){
			green = 0x00;
		}else if(green ==1){
			green = 0x01;
		}

		if(blue ==0 ){
			blue = 0x00;
		}else if(blue ==1){
			blue = 0x01;
		}

		led->on(id, 0, red, green, blue);

		ros::spinOnce();
	}


	return 0;

}


