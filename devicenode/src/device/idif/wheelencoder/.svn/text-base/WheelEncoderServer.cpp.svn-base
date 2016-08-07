#include "WheelEncoderServer.h"

CWheelEncoderServerProxy::CWheelEncoderServerProxy(){
	
	int typeOfServerDevice		= CConfig::getInstance()->getParamValueInt( "SERVER_DEVICE_TYPE" );
	int typeOfRobot				= CConfig::getInstance()->getParamValueInt( "ROBOT_TYPE" );

	//cout << "[CWheelEncoderServerProxy] server type "<< typeOfServerDevice << endl;
	//cout << "[CWheelEncoderServerProxy] robot type "<< typeOfRobot << endl;
	ROS_DEBUG("[CWheelEncoderServerProxy] robot type : %d", typeOfRobot);
	ROS_DEBUG("[CWheelEncoderServerProxy] server type : %d",typeOfServerDevice);

	switch (typeOfRobot) {
		case ROBOT_TYPE_EROBOT:
				switch (typeOfServerDevice) {
					case SERVER_DEVICE_REAL: 
					case SERVER_DEVICE_BOTH :
						wheelencoder = new CWheelEncoderERobot();
						break;
					case SERVER_DEVICE_SIMULATOR: 
						wheelencoder = new CWheelEncoderERobotSimul();
						break;

					case SERVER_DEVICE_MOCK: 
					default:
						wheelencoder = new CWheelEncoderMock();
						break;
				}
			break;
		default:
			wheelencoder = new CWheelEncoderMock();
			break;
	}
}
CWheelEncoderServerProxy::~CWheelEncoderServerProxy(){

}


CWheelEncoder* CWheelEncoderServerProxy::getInstance() {
	static CWheelEncoderServerProxy instance;
	return &instance;
}


CWheelEncoderData CWheelEncoderServerProxy::readData(int index) {

	return wheelencoder->readData(index);
}