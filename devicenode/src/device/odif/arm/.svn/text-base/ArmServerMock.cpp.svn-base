#include "ArmServer.h"

CArmServerMock::CArmServerMock(void)
{	
	isEmergency = false;
}

CArmServerMock::~CArmServerMock(void)
{
}

int CArmServerMock::on( int armID )
{
	ROS_DEBUG("[CArmServerMock] on");
	return 0;
}

int CArmServerMock::off( int armID )
{
	ROS_DEBUG("[CArmServerMock] off");
	return 0;
}

int CArmServerMock::setPeriodic( int armID, int milisecondTime )
{
	if(isEmergency) return 0;
	ROS_DEBUG("[CArmServerMock] setPeriodic");
	return 0;
}

int CArmServerMock::moveToHome( int armID )
{
	if(isEmergency) return 0;
	ROS_DEBUG("[CArmServerMock] moveToHome");
	return 0;
}

int CArmServerMock::moveToPositionAll( int armID, double* Angle, double Speed )
{
	if(isEmergency) return 0;
	ROS_DEBUG("[CArmServerMock] moveToPositionAll");
	return 0;
}

int CArmServerMock::moveToPositionAllWithPeriodic( int armID, double Angle, int stateType )
{
	if(isEmergency) return 0;
	ROS_DEBUG("[CArmServerMock] moveToPositionAllWithPeriodic");
	return 0;
}

int CArmServerMock::stop()
{
	if(isEmergency) return 0;
	ROS_DEBUG("[CArmServerMock] stop");
	return 0;
}

CArmData CArmServerMock::waitRunOnPeriodic( float index )
{
	static CArmData data;
	if(isEmergency) return data;
	ROS_DEBUG("[CArmServerMock] waitRunOnPeriodic");
	return data;
}

void CArmServerMock::moveBothArmToPositionAll( double Angle[6], int speed )
{
	if(isEmergency) return;
	ROS_DEBUG("[CArmServerMock] moveBothArmToPositionAll");
}

int CArmServerMock::moveToPositionWithAxisSpeed( int armID, double* Angle, double* Speed )
{
	if(isEmergency) return 0;
	ROS_DEBUG("[CArmServerMock] moveToPositionWithAxisSpeed");
	return 0;
}

void CArmServerMock::moveBothArmToPositionWithAxisSpeed( double Angle[6], int speed[6] )
{
	if(isEmergency) return;
	ROS_DEBUG("[CArmServerMock] moveBothArmToPositionWithAxisSpeed");
}

void CArmServerMock::getArmPosition( int armId, double angle[6] )
{

	for(int i=0; i<6; i++) {
		angle[i] = -999;
	}

	ROS_DEBUG("[CArmServerMock] getArmPosition");
}

void CArmServerMock::setArmHomePosition() {
	ROS_DEBUG("[CArmServerMock] setArmHomePosition");
}

void CArmServerMock::emergencyStop() {
	ROS_DEBUG("[CArmServerMock] emergencyStop");
	isEmergency = true;
}
void CArmServerMock::emergencyRelease() {
	ROS_DEBUG("[CArmServerMock] emergencyRelease");
	isEmergency = false;
}

void CArmServerMock::detectingError(short errorCode[6]) {
	for(int i=0; i<6; i++) {
		errorCode[i] = -1;
	}
}
