#include "ArmServer.h"

CArmServerProxy* CArmServerProxy::getInstance()
{
	static CArmServerProxy instance;
	return &instance;
}

CArmServerProxy::CArmServerProxy()
{

	int typeOfRobot					= CConfig::getInstance()->getParamValueInt( "ROBOT_TYPE" );
	//cout << "[CArmServerProxy] robot type : "	<< typeOfRobot << endl;
	//cout << "[CArmServerProxy] server type : "	<< typeOfServerDevice << endl;
	ROS_DEBUG("[CArmServerProxy] robot type : %d", typeOfRobot);
	int serverDeviceType	= CConfig::getInstance()->getParamValueInt( "SERVER_DEVICE_TYPE" );
	switch(typeOfRobot) {  
		case ROBOT_TYPE_EROBOT : 
			arm = new CArmERobot();
		default:
			cout << NO_MATCHING_ROBOT_TYPE << typeOfRobot << endl;
			break;
	}
	switch(serverDeviceType) {
		case SERVER_DEVICE_MOCK :
			arm = new CArmServerMock();
		default:
			break;
	}


}

CArmServerProxy::~CArmServerProxy()
{
}

int CArmServerProxy::on( int armID )
{
    return arm->on( armID );
}


int CArmServerProxy::off( int armID )
{
    return arm->off( armID );
}


int CArmServerProxy::setPeriodic( int armID, int milisecondTime )
{
    return arm->setPeriodic( armID, milisecondTime );
}


int CArmServerProxy::moveToHome( int armID )
{
    return arm->moveToHome( armID );
}


int CArmServerProxy::moveToPositionAll( int armID, double* Angle, double Speed )
{
    return arm->moveToPositionAll( armID, Angle, Speed );
}


int CArmServerProxy::moveToPositionAllWithPeriodic( int armID, double Angle, int stateType )
{
    return arm->moveToPositionAllWithPeriodic( armID, Angle, stateType );
}


int CArmServerProxy::stop()
{
    return arm->stop();
}

CArmData CArmServerProxy::waitRunOnPeriodic( float index )
{
    return arm->waitRunOnPeriodic( index );
}

int CArmServerProxy::moveToPositionWithAxisSpeed(int armID, double *Angle, double *Speed) 
{
	return arm->moveToPositionWithAxisSpeed(armID, Angle, Speed);
}

void CArmServerProxy::moveBothArmToPositionAll(double Angle[6], int speed) {
	arm->moveBothArmToPositionAll(Angle, speed);
}

void CArmServerProxy::moveBothArmToPositionWithAxisSpeed(double Angle[6], int speed[6]) {
	arm->moveBothArmToPositionWithAxisSpeed(Angle, speed);
}

void CArmServerProxy::getArmPosition(int armId, double angle[6]) {
	arm->getArmPosition(armId, angle);
}

void CArmServerProxy::setArmHomePosition() {
	arm->setArmHomePosition();
}

void CArmServerProxy::emergencyStop() {
	arm->emergencyStop();
}
void CArmServerProxy::emergencyRelease() {
	arm->emergencyRelease();
}
void CArmServerProxy::detectingError(short errorCode[6]) {
	arm->detectingError(errorCode);
}
