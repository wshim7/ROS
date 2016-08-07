#ifndef __LED_SERVER_H__
#define __LED_SERVER_H__

#include <ros/ros.h>
#include <roscir/env/Config.h>
#include <roscir/device/common/LightEmittingDiode.h>
#include <device/DeviceServerDefinition.h>
#include <reactive/erobot/ERobotCore.h>
#include <reactive/mero/driver/MeroLEDDriver.h>

using namespace std;
using namespace reactive::erobot::core;
using namespace reactive::mero::driver;

class CLightEmittingDiodeServerProxy : public CLightEmittingDiode
{
    private :
        CLightEmittingDiode* lightEmittingDiode;
        CLightEmittingDiodeServerProxy();

    public :
        virtual ~CLightEmittingDiodeServerProxy();
        static CLightEmittingDiodeServerProxy* getInstance();

        int on( int id, int color );
        int on(int id, unsigned char bright, unsigned char red, unsigned char green, unsigned char blue);
};

class CLightEmittingDiodeERobot : public CLightEmittingDiode
{
private:
	
	ERobotCore* core;

public:
	CLightEmittingDiodeERobot();
	virtual ~CLightEmittingDiodeERobot();
public:
	int on( int id, int color );
	int on(int id, unsigned char bright, unsigned char red, unsigned char green, unsigned char blue);
};

class CLightEmittingDiodeMock : public CLightEmittingDiode
{
private:

	ERobotCore* core;

public:
	CLightEmittingDiodeMock();
	virtual ~CLightEmittingDiodeMock();
public:
	int on( int id, int color );
	int on(int id, unsigned char bright, unsigned char red, unsigned char green, unsigned char blue);
};

class CLightEmittingDiodeMero : public CLightEmittingDiode
{
private:
	MeroLEDDriver* MLC;
public:
	CLightEmittingDiodeMero();
	virtual ~CLightEmittingDiodeMero();
public:
	int on( int id, int color );
	int on(int id, unsigned char bright, unsigned char red, unsigned char green, unsigned char blue);
};

#endif /* __LED_SERVER_H__ */
