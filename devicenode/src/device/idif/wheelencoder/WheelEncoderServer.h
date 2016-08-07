#ifndef __WHEELENCODER_SERVER_H__
#define __WHEELENCODER_SERVER_H__

#include <ros/ros.h>
#include <iostream>
#include <roscir/env/Config.h>
#include <roscir/device/common/WheelEncoder.h>
#include <roscir/device/data/WheelEncoderData.h>
#include <device/DeviceServerDefinition.h>
#include <reactive/erobot/ERobotCore.h>

using namespace std;
using namespace reactive::erobot::core;

class CWheelEncoderServerProxy : public CWheelEncoder
{
private :
	CWheelEncoder* wheelencoder;
	CWheelEncoderServerProxy();

public :	
	~CWheelEncoderServerProxy();
	static CWheelEncoder* getInstance();
	CWheelEncoderData readData( int index );

};

class CWheelEncoderMock : public CWheelEncoder
{
public:
    public :
		CWheelEncoderMock();
        virtual ~CWheelEncoderMock();
        CWheelEncoderData readData( int index );
};

class CWheelEncoderERobot : public CWheelEncoder
{
private:
	ERobotCore* core;

public :
	CWheelEncoderERobot();
    virtual ~CWheelEncoderERobot();
	CWheelEncoderData readData( int index);
};

class CWheelEncoderERobotSimul : public CWheelEncoder
{
private: 
	bool isConnect;


public :
	CWheelEncoderERobotSimul();
    virtual ~CWheelEncoderERobotSimul();
	CWheelEncoderData readData( int index);
};

#endif /* __WHEELENCODER_SERVER_H__ */