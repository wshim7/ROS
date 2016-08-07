#include "BatteryServer.h"

CBatteryServerProxy::CBatteryServerProxy(void)
{
	int serverDeviceType	= CConfig::getInstance()->getParamValueInt( "SERVER_DEVICE_TYPE" );
    int typeOfRobot			= CConfig::getInstance()->getParamValueInt( "ROBOT_TYPE" );

	//cout << "[CGyroServerProxy] robot type : "	<< typeOfRobot << endl;
	//cout << "[CGyroServerProxy] server type : "	<< serverDeviceType << endl;
	ROS_DEBUG("[CBatteryServerProxy] robot type : %d", typeOfRobot);
	ROS_DEBUG("[CBatteryServerProxy] server type : %d",serverDeviceType);

	switch ( typeOfRobot ) {
		case ROBOT_TYPE_EROBOT :
			switch (serverDeviceType) {
				case SERVER_DEVICE_REAL:
				case SERVER_DEVICE_BOTH:
					battery = CBatteryERobot::getInstance();
					break;
				case SERVER_DEVICE_SIMULATOR:
					// TODO
					break;
				default:
					battery = new CBatteryMock();
					break;
			}
			break;
		default:
			ROS_DEBUG("batterymock creaeted");
			battery = new CBatteryMock();
			break;
	}

}

CBatteryServerProxy::~CBatteryServerProxy(void)
{
}

CBattery* CBatteryServerProxy::getInstance()
{
	static CBatteryServerProxy instance;
	return &instance;
}

CBatteryData CBatteryServerProxy::readData( int index ) {
	return battery->readData( index );
}

bool  CBatteryServerProxy::isDocked(const int& id) {
	return battery->isDocked(id);
}

bool  CBatteryServerProxy::doCharge(const int& id) {
	return battery->doCharge(id);
}
