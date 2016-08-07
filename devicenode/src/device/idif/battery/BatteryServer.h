#ifndef __BATTERY_SERVER_H__
#define __BATTERY_SERVER_H__

#include <ros/ros.h>
#include <iostream>
#include <boost/thread.hpp>
#include <roscir/env/Config.h>
#include <roscir/device/common/battery.h>
#include <device/DeviceServerDefinition.h>
#include <reactive/erobot/ERobotCore.h>

class CBatteryServerProxy : public CBattery
{

private:
	CBattery* battery;
	CBatteryServerProxy(void);

public:
	~CBatteryServerProxy(void);

	static CBattery* getInstance();

	CBatteryData readData( int index );
    bool isDocked(const int& id);
	bool doCharge(const int& id);
};

class CBatteryMock : public CBattery
{
public :
	CBatteryMock(void);
	~CBatteryMock(void);

	CBatteryData readData( int index );
	bool isDocked(const int& id);
	bool doCharge(const int& id);
};

class CBatteryERobot : public CBattery
{
private :
	ERobotCore* core;

public:
	CBatteryERobot(void);
	~CBatteryERobot(void);

	static CBattery* getInstance();

	CBatteryData readData( int index );
    bool isDocked(const int& id);
    bool doCharge(const int& id);
};

#endif /* __BATTERY_SERVER_H__ */
