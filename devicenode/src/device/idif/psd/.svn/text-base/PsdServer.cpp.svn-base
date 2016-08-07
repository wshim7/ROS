#include "PsdServer.h"

CPSDServerProxy::CPSDServerProxy() {

	int serverDeviceType	= CConfig::getInstance()->getParamValueInt( "SERVER_DEVICE_TYPE" );
	int typeOfRobot			= CConfig::getInstance()->getParamValueInt( "ROBOT_TYPE" );

	//cout << "[CPSDServerProxy] robot type : "	<< typeOfRobot << endl;
	//cout << "[CPSDServerProxy] server type : "	<< serverDeviceType << endl;
	ROS_DEBUG("[CPSDServerProxy] robot type : %d", typeOfRobot);
	ROS_DEBUG("[CPSDServerProxy] server type : %d",serverDeviceType);

	switch(typeOfRobot) {
		case ROBOT_TYPE_EROBOT :		
			switch (serverDeviceType) {
				case SERVER_DEVICE_REAL:
				case SERVER_DEVICE_BOTH:
					psd = new CPSDERobot();
					break;
				case SERVER_DEVICE_SIMULATOR:
					psd = new CPSDERobotSimul();
					break;
				default:
					psd = new CPSDMock();
					break;
			}			
			break;
		default:
			psd = new CPSDMock();
			break;
	}
}

CPSDServerProxy::~CPSDServerProxy() {

}

CPSD* CPSDServerProxy::getInstance() {
	static CPSDServerProxy instance;
	return &instance;
}

int CPSDServerProxy::readData(int returnMethod, CPSDData& data) {
	return psd->readData(returnMethod, data);
}