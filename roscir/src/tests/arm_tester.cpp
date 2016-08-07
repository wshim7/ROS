#include <ros/ros.h>
#include <time.h>
#include <iostream>
#include <roscir/device/client/CArmClient.h>


using namespace std;

int main(int argc, char **argv) {

	ros::init(argc, argv, "TestArm");

	ros::NodeHandle n;
	//test33();
	string command = "";


	CArm* arm = CArmClientProxy::newInstance();

	while(ros::ok()) {
		cin.clear();

		int id = 0;
		double angle[3];
		int speed;
		cout << "input arm id (left=0,right=1,setHome=99): ";
		cin >> id;
		if(id == 99) {
			arm->setArmHomePosition();
		} else {
			cin.clear();
			cout << "input angle0 : ";
			cin >> angle[0];
			cin.clear();
			cout << "input angle1 : ";
			cin >> angle[1];
			cin.clear();
			cout << "input angle2 : ";
			cin >> angle[2];
			cin.clear();
			cout << "input speed : ";
			cin >> speed;
			cin.clear();

			arm->moveToPositionAll(id, angle, speed);
		}

	}

	ros::spin();
	return -1;
}
