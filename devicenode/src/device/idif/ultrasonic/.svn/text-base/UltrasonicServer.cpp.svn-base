#include "UltrasonicServer.h"

CUltrasonicServerProxy::CUltrasonicServerProxy()
{
	
	int serverDeviceType	= CConfig::getInstance()->getParamValueInt( "SERVER_DEVICE_TYPE" );
    int typeOfRobot			= CConfig::getInstance()->getParamValueInt( "ROBOT_TYPE" );
	int ultrasonicType		= CConfig::getInstance()->getParamValueInt( "ULTRASONIC_TYPE" );

	//cout << "[CUltrasonicServerProxy] robot type : "	<< typeOfRobot << endl;
	//cout << "[CUltrasonicServerProxy] server type : "	<< serverDeviceType << endl;
	//cout << "[CUltrasonicServerProxy] sensor type : "	<< ultrasonicType << endl;
	ROS_DEBUG("[CUltrasonicServerProxy] robot type : %d", typeOfRobot);
	ROS_DEBUG("[CUltrasonicServerProxy] server type : %d",serverDeviceType);
	ROS_DEBUG("[CUltrasonicServerProxy] sensor type : %d",ultrasonicType);

	switch ( typeOfRobot ) {
	case ROBOT_TYPE_EROBOT :
		switch (serverDeviceType) {
		case SERVER_DEVICE_REAL:
		case SERVER_DEVICE_BOTH:
			ultra = CUltrasonicERobot::getInstance();
			break;
		case SERVER_DEVICE_SIMULATOR:
			ultra = CUltrasonicERobotSimul::getInstance();
			break;
		default:
			ultra = new CUltrasonicMock();
			break;
		}
		break;
		default:
			ultra = new CUltrasonicMock();
			break;
	}
}


CUltrasonicServerProxy::~CUltrasonicServerProxy()
{
}


CUltrasonic* CUltrasonicServerProxy::getInstance( )
{
	static CUltrasonicServerProxy thisInstance;
	return &thisInstance;
}



CUltrasonicData CUltrasonicServerProxy::readData(int index)
{
	return ultra->readData(index);
}

void CUltrasonicServerProxy::close()
{
	ultra->close();
}
