#ifndef __GYRO_SERVER_H__
#define __GYRO_SERVER_H__

#include <ros/ros.h>
#include <iostream>
#include <boost/thread.hpp>
#include <roscir/env/Config.h>
#include <roscir/device/common/Gyro.h>
#include <device/DeviceServerDefinition.h>

#include <reactive/erobot/session/EGyroCore.h>

using namespace std;

class CGyroServerProxy : public CGyro
{
private:
	CGyro* gyro;	
	CGyroServerProxy(void);

public:
	~CGyroServerProxy(void);

public:
	static CGyro* getInstance();
	CGyroData readData();
};

class CGyroMock : public CGyro
{
public :
	CGyroMock();
	~CGyroMock();
	CGyroData readData();

};

class CGyroERobotSimul : public CGyro
{

private :
	CGyroERobotSimul();

public :
	~CGyroERobotSimul();
	static CGyro* getInstance();

	CGyroData readData();
	void run();
};

class CGyroERobot : public CGyro
{
private :
	CGyroERobot();
	EGyroCore* _core;
	string _comPort;

public :
	~CGyroERobot();
	static CGyro* getInstance();

public :
	CGyroData readData();
};

#endif /* __GYRO_SERVER_H__ */