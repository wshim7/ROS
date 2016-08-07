/*
 * pantilt_tester.cpp
 *
 *  Created on: 2014. 1. 16.
 *      Author: msyoo
 */
#include <stdio.h>
#include <ros/ros.h>
#include <roscir/device/client/CPanTiltClient.h>

#ifdef WIN32
	#include <conio.h>
#else
#include <roscir/util/getch.h>
#endif

int main(int argc, char **argv) {
		ros::init(argc, argv, "TestPantilt");

		double leftRightMax = 100;
		double leftRightMin = -100;
		double upDownMax	= 70;
		double upDownMin	= -30;

		int speed = 30;
		double upDown = 0;
		double leftRight = 0;
		int xtionUpDown = 20;

		CPanTilt* pantilt = CPanTiltClientProxy::newInstance();
		pantilt->on();

		CConfig* config = CConfig::getInstance();

		while(ros::ok()) {
			cout << "Waiting Type key 'i, k, j, l, g, c, n, m ' " << endl;
			char c = getchar();
			cout << "You typed [[ "<< c << " ]]" <<endl;

			if(c=='i') {
				upDown += 10;
			} else if(c=='k') {
				upDown -= 10;
			} else if(c=='j') {
				leftRight-=10;
			} else if(c=='l') {
				leftRight+=10;
			} else if(c=='c') {
				break;
			} else if(c=='n') {
				xtionUpDown += 2;
			} else if(c=='m') {
				xtionUpDown -= 2;
			}
			if(leftRight >= leftRightMax) {
				leftRight = leftRightMax;
			} else if(leftRight <= leftRightMin) {
				leftRight = leftRightMin;
			}
			if(upDown >= upDownMax) {
				upDown = upDownMax;
			} else if(upDown <= upDownMin) {
				upDown = upDownMin;
			}

			if(upDown >= 50) {
				upDown = 50;
			}
			if(upDown <= -10) {
				upDown = -10;
			}
			if(leftRight >= 70) {
				leftRight = 70;
			}
			if(leftRight <= -70) {
				leftRight = -70;
			}
			if(xtionUpDown >= 36) {
				xtionUpDown = 36;
			}
			if(xtionUpDown <= -10) {
				xtionUpDown = -10;
			}

//			pantilt->moveToAbsolutePosition(leftRight, upDown, speed);
			pantilt->moveToABSAll(leftRight, upDown, xtionUpDown, speed, speed, speed);

		}

		return -1;

}




