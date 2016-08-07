#include "PantiltServer.h"

CPanTiltServerMock::CPanTiltServerMock(void)
{
	isEmergency = false;
}

CPanTiltServerMock::~CPanTiltServerMock(void)
{	
}

int CPanTiltServerMock::on()
{
	ROS_DEBUG("[CPanTiltServerMock] on");
	return RETURN_SUCCESS;
}

int CPanTiltServerMock::off()
{
	ROS_DEBUG("[CPanTiltServerMock] off");
	return RETURN_SUCCESS;
}

int CPanTiltServerMock::stop()
{
	ROS_DEBUG("[CPanTiltServerMock] stop");
	return RETURN_SUCCESS;
}

int CPanTiltServerMock::moveToHome( int speed )
{
	ROS_DEBUG("[CPanTiltServerMock] moveToHome");
	return RETURN_SUCCESS;
}

int CPanTiltServerMock::moveToAbsolutePosition( double degreeLeftRight, double degreeUpDown, int speed )
{
	ROS_DEBUG("[CPanTiltServerMock] moveToAbsolutePosition(degLR : %f, degUD: %f, speed: %d) called", degreeLeftRight, degreeUpDown, speed);
	return RETURN_SUCCESS;
}

int CPanTiltServerMock::moveToAbsolutePositionWithSpeed(double degreeLeftRight, double degreeUpDown, int speedLeftRight, int speedUpDown)
{
	ROS_DEBUG("[CPanTiltServerMock] moveToAbsolutePositionWithSpeed(degLR : %f, degUD: %f, speedLeftRight: %d, speedUpDown: %d) called", degreeLeftRight, degreeUpDown, speedLeftRight, speedUpDown);
	return RETURN_SUCCESS;
}

int CPanTiltServerMock::moveToRelativePosition( double degreeLeftRight, double degreeUpDown, int speed )
{
	ROS_DEBUG("[CPanTiltServerMock] moveToRelativePosition");
	return RETURN_SUCCESS;
}

int CPanTiltServerMock::move2MotorSync( int motorID1, int motorSpeed1, int motorPosition1, int motorID2, int motorSpeed2, int motorPosition2 )
{
	ROS_DEBUG("[CPanTiltServerMock] move2MotorSync");
	return RETURN_SUCCESS;
}

int CPanTiltServerMock::moveMotor( int motorID, int motorSpeed, int motorPosition )
{
	ROS_DEBUG("[CPanTiltServerMock] moveMotor");
	return RETURN_SUCCESS;
}

void CPanTiltServerMock::getPosition( CPanTiltPosition& position )
{
	ROS_DEBUG("[CPanTiltServerMock] getPosition");
	position.setDegreeLeftRight(-999);
	position.setDegreeUpDown(-999);
	position.setXtionTilt(-999);
}


int CPanTiltServerMock::setCompliance(int option)
{
	ROS_DEBUG("[CPanTiltServerMock] setCompliance");
	return RETURN_SUCCESS;
}
void CPanTiltServerMock::emergencyStop() {
	ROS_DEBUG("[CPanTiltServerMock] emergencyStop");
	isEmergency = true;
}



void CPanTiltServerMock::emergencyRelease() {
	ROS_DEBUG("[CPanTiltServerMock] emergencyRelease");
	isEmergency = false;
}

void CPanTiltServerMock::detectingError(short errorCode[3]) {
	for(int i=0; i<3; i++) {
		errorCode[i] = -1;
	}
}
