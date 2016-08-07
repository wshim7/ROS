#include "WheelEncoderServer.h"
//#include <reactive/erobot/ERobotSocketReceiver.h>
#include <iostream>


using namespace reactive::erobot::core;

CWheelEncoderERobot::CWheelEncoderERobot()
{
	//wheel = ERobotSocketReceiver::getInstance();
	core = ERobotCore::getInstance();
	//cout << "WheelEncoderERobot..." << endl;
}

CWheelEncoderERobot::~CWheelEncoderERobot() 
{
	//delete wheel;
}

CWheelEncoderData CWheelEncoderERobot::readData(int index) 
{
	long a[3] = { 0 , 0, 0};
	long datas[6] = {0,0,0,0,0,0};
	int x=0, y=0, t=0;

	//wheel->getWheelPosition(&x, &y, &t);
	core->getWheelEncoderValue(a, &x, &y, &t);
	//erobot과 기존 잉키 등의 x/y축이 다름.
	CWheelEncoderData encoderData(a, y, -1 * x, t, 3);
	//cout << "WheelEncoderERobot.readData : " << a[0] << ", " << a[1] << ", " << a[2] <<", position: " << datas[3] << ", " << datas[4] << ", " << datas[5] << endl;

	return encoderData;
}
