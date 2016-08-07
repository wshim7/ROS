#include <ros/ros.h>
#include <ros/package.h>
#include <stdio.h>

#include <roscir/roscir.h>
#include <roscir/device/odif/CWheel.h>

int main(int argc, char** argv) {
	ros::init(argc, argv, "roscir");
	roscir::init(argc, argv);

	ROS_INFO("package path :  패키지 패스를 보여 줍니다. : %s", ros::package::getPath("roscir").c_str());
	ROS_INFO("이것은 한글 입니다.");
	ROS_INFO("roscir Binary main launched");

	using namespace roscir::device::odif;
	IWheel* wheel = new CWheel;
	wheel->moveByTRVelocity(10.0, 20.0);

	delete wheel;

	return -1;
}


