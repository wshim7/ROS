#ifndef __ULTRASONIC_SERVER_H__
#define __ULTRASONIC_SERVER_H__

#include <ros/ros.h>
#include <iostream>
#include <roscir/env/Config.h>
#include <roscir/device/common/Ultrasonic.h>
#include <reactive/erobot/ERobotCore.h>
#include <device/DeviceServerDefinition.h>

using namespace std;
using namespace reactive::erobot::core;

class CUltrasonicServerProxy : public CUltrasonic
{
private :
	CUltrasonic* ultra;
	CUltrasonicServerProxy();

public :
	~CUltrasonicServerProxy();
	static CUltrasonic* getInstance();

	CUltrasonicData readData(int index);
	void close();
};

class CUltrasonicMock : public CUltrasonic
{

public :
	CUltrasonicMock();
	~CUltrasonicMock();

	CUltrasonicData readData(int index);
	void close();
};

class CUltrasonicERobot : public CUltrasonic
{
private:
	CUltrasonicERobot();
	//ERobotSocketReceiver* sonic;
	ERobotCore* core;

private:
	int ultrasonicBumperRange;

public :
	~CUltrasonicERobot();
	static CUltrasonic* getInstance();

	CUltrasonicData readData(int index);
	void close();
};

class CUltrasonicERobotSimul : public CUltrasonic
{
private :
	CUltrasonicERobotSimul();

public :
	~CUltrasonicERobotSimul();
	static CUltrasonic* getInstance();

	CUltrasonicData readData(int index);
	void close();
};

#endif /* __ULTRASONIC_SERVER_H__ */