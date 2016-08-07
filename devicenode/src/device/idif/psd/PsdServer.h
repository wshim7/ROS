#ifndef __PSD_SERVER_H__
#define __PSD_SERVER_H__

#include <iostream>
#include <string>

#include <ros/ros.h>
#include <roscir/env/Config.h>
#include <reactive/erobot/ERobotCore.h>
#include <roscir/device/common/Psd.h>
#include <device/DeviceServerDefinition.h>
#include <iostream>

using namespace std;
using namespace reactive::erobot::core;

class CPSDServerProxy : public CPSD {
private:
	CPSD* psd;
	CPSDServerProxy();
public:
	virtual ~CPSDServerProxy();
	static CPSD* getInstance();
	int readData(int returnMethod, CPSDData& data);

};

class CPSDMock : public CPSD {

public:
	CPSDMock();
	virtual ~CPSDMock();

	int readData(int returnMethod, CPSDData& data);
};

class CPSDERobot : public CPSD {
private:
	ERobotCore* core;

public:
	CPSDERobot();
	virtual ~CPSDERobot();
	
	int readData(int returnMethod, CPSDData& data);
};

class CPSDERobotSimul : public CPSD {

public:
	CPSDERobotSimul();
	virtual ~CPSDERobotSimul();
	
	int readData(int returnMethod, CPSDData& data);
};

#endif /* __PSD_SERVER_H__ */