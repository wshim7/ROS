#ifndef __TOUCH_SERVER_H__
#define __TOUCH_SERVER_H__

#include <iostream>
#include <string>

#include <ros/ros.h>
#include <roscir/env/Config.h>
#include <reactive/erobot/ERobotCore.h>
#include <reactive/mero/driver/MeroTouchDriver.h>
#include <roscir/device/common/TouchButton.h>
#include <device/DeviceServerDefinition.h>
#include <iostream>

using namespace std;
using namespace reactive::erobot::core;
using namespace reactive::mero::driver;


class CTouchButtonServerProxy : public CTouchButton {
    private :
        CTouchButton* touchButton;
        CTouchButtonServerProxy();

    public :
        virtual ~CTouchButtonServerProxy();
        static CTouchButtonServerProxy* getInstance();

        CTouchButtonData readData( int index );
        CHeadTouchButtonData readHeadData( int index );
        int detectingError(int touchID);
};

class CTouchButtonERobot : public CTouchButton
{
private :
	ERobotCore* core;

public :
	CTouchButtonERobot();
	virtual ~CTouchButtonERobot();

	CTouchButtonData readData( int index );
	CHeadTouchButtonData readHeadData( int index );
	int detectingError(int touchID);
};

class CTouchButtonMero : public CTouchButton
{
private :
	MeroTouchDriver* MTD;

public :
	CTouchButtonMero();
	virtual ~CTouchButtonMero();

	CTouchButtonData readData( int index );
	CHeadTouchButtonData readHeadData( int index );
	int detectingError(int touchID);
};

class CTouchButtonMock : public CTouchButton
{
private :
	ERobotCore* core;

public :
	CTouchButtonMock();
	virtual ~CTouchButtonMock();

	CTouchButtonData readData( int index );
	CHeadTouchButtonData readHeadData( int index );
	int detectingError(int touchID);
};

#endif /* __TOUCH_SERVER_H__ */
