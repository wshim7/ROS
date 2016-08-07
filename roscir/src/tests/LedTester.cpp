/*
 * LedTester.cpp
 *
 *  Created on: 2014. 1. 26.
 *      Author: ADmin
 */


#include <stdio.h>
#include <ros/ros.h>
#include <roscir/device/client/CLightEmittingDiodeClient.h>
#include <roscir/env/Config.h>
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
	ros::init(argc, argv, "TestLED");

	CLightEmittingDiode* led = CLightEmittingDiodeClientProxy::newInstance();

	int count = 0;
	while(ros::ok()) {
		cin.clear();
		cout << "Waiting Type key (b)oth , (l)eft , (r)ight , rin(g) " << endl;
		//char c = getchar();
		char c;
		cin >> c;
		cout << "You typed [[ "<< c << " ]]" <<endl;

		char command = 0x00;
		if(c=='b') {
			command = 0xF2;
		} else if(c=='l') {
			command = 0xF3;
		} else if(c=='r') {
			command = 0xF4;
		} else if(c=='g') {
			command = 0xF5;
		}

		cout << "Waiting Type key (o)n, of(f) " << endl;
		cout << "bright ? " << endl;
		//char bright = getchar();
		cin.clear();
		char bright;
		cin >> bright;
                cout << "-----------------------" << endl;
		if(bright == 'o') {
			bright = 0x01;
		} else {
			bright = 0x00;
		}

		cout << "red ? " << endl;
		//char red = getchar();
		cin.clear();
		char red;
		cin >> red;
                cout << "-----------------------" << endl;
		if(red == 'o') {
			red = 0x01;
		} else {
			red = 0x00;
		}

		cout << "green ? " << endl;
		//char green = getchar();
		cin.clear();
		char green;
		cin >> green;
                cout << "-----------------------" << endl;
		if(green == 'o') {
			green = 0x01;
		} else {
			green = 0x00;
		}

		cout << "blue ? " << endl;
		//char blue = getchar();
		cin.clear();
		char blue;
		cin >> blue;
                cout << "-----------------------" << endl;
		if(blue == 'o') {
			blue = 0x01;
		} else {
			blue = 0x00;
		}
		cout << "===== send command =====" << endl;
		//cout << "bright : " << bright << endl;
		//cout << "red : " << red << endl;
		//cout << "green : " << green << endl;
		//cout << "blue : " << blue << endl;
		printf("bright : 0x%02x \n", bright);
		printf("red    : 0x%02x \n", red);
		printf("green  : 0x%02x \n", green);
		printf("blue   : 0x%02x \n", blue);
		cout << "========================" << endl;

		led->on(command,bright, red, green, blue);
	}
	delete led;
	return -1;
}
