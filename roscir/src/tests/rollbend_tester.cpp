/*
 * pantilt_tester.cpp
 *
 *  Created on: 2014. 1. 16.
 *      Author: msyoo
 */

#ifdef WIN32
#include <ros/ros.h>
#include <conio.h>
#include <roscir/device/client/CRollBendClient.h>
#endif


int main(int argc, char **argv) {
#ifdef WIN32
	ros::init(argc, argv, "RollbendTester");
	ROS_DEBUG("Rollbend tester started");

	double leftRightMax = 100;
	double leftRightMin = -100;
	double upDownMax	= 70;
	double upDownMin	= -30;

	int speed = 30;
	double upDown = 0;
	double leftRight = 0;
	int xtionUpDown = 20;



	CRollBend* rollbend = CRollBendClientProxy::newInstance();
	rollbend->on();

	CConfig* config = CConfig::getInstance();

	while(ros::ok()) {
		cout << "Waiting Type key 'i, k, j, l, g, c, n, m ' " << endl;
		char c = getch();
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

		rollbend->moveToAbsolutePosition(leftRight, upDown, speed);
		cout << "leftRight : " << leftRight << ", upDown : " << upDown << ", xtionUpDown : " << xtionUpDown << endl;
	}

	ros::spin();

#endif

	return 0;

}



