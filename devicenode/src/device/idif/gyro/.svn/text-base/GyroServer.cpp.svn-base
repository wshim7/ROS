#include "GyroServer.h"

CGyroServerProxy::CGyroServerProxy()
{	
	int serverDeviceType	= CConfig::getInstance()->getParamValueInt( "SERVER_DEVICE_TYPE" );
    int typeOfRobot			= CConfig::getInstance()->getParamValueInt( "ROBOT_TYPE" );

	//cout << "[CGyroServerProxy] robot type : "	<< typeOfRobot << endl;
	//cout << "[CGyroServerProxy] server type : "	<< serverDeviceType << endl;
	ROS_DEBUG("[CGyroServerProxy] robot type : %d", typeOfRobot);
	ROS_DEBUG("[CGyroServerProxy] server type : %d",serverDeviceType);

    switch ( typeOfRobot ) {
		case ROBOT_TYPE_EROBOT :
			switch (serverDeviceType) {
				case SERVER_DEVICE_REAL:
				case SERVER_DEVICE_BOTH:
					gyro = CGyroERobot::getInstance();
					break;
				case SERVER_DEVICE_SIMULATOR:
					gyro = CGyroERobotSimul::getInstance();
					break;
				default:
					gyro = new CGyroMock();
					break;
			}
			break;
		default:
			ROS_DEBUG("gyromock creaeted");
			gyro = new CGyroMock();
			break;
    }
}


CGyroServerProxy::~CGyroServerProxy()
{
}


CGyro* CGyroServerProxy::getInstance( )
{
	static CGyroServerProxy thisInstance;
	return &thisInstance;
}



CGyroData CGyroServerProxy::readData()
{
	return gyro->readData();
}
