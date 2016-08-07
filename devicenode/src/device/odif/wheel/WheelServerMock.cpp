#include "WheelServer.h"

CWheelServerMock::CWheelServerMock(void)
{
	isEmergency = false;
}

CWheelServerMock::~CWheelServerMock(void)
{
}

int CWheelServerMock::on()
{
	ROS_DEBUG("[CWheelServerMock] on");
	return RETURN_SUCCESS;
}

int CWheelServerMock::off()
{
	ROS_DEBUG("[CWheelServerMock] off");
	return RETURN_SUCCESS;
}

int CWheelServerMock::stop()
{
	ROS_DEBUG("[CWheelServerMock] stop");
	return RETURN_SUCCESS;
}

int CWheelServerMock::moveByTRVelocity( double translationalVelocity, double rotationalVelocity )
{
	if(isEmergency) return 0;
	ROS_DEBUG("[CWheelServerMock] moveByTRVelocity");
	return RETURN_SUCCESS;
}

int CWheelServerMock::moveByWheelVelocity( double leftWheelVelocity, double rightWheelVelocity )
{
	if(isEmergency) return 0;
	ROS_DEBUG("[CWheelServerMock] moveByWheelVelocity");
	return RETURN_SUCCESS;
}

int CWheelServerMock::moveToDeltaX( int deltaX, double velocity )
{
	if(isEmergency) return 0;
	ROS_DEBUG("[CWheelServerMock] moveToDeltaX");
	return RETURN_SUCCESS;
}

int CWheelServerMock::moveToDeltaTheta( int deltaTheta, int radius, double velocity )
{
	if(isEmergency) return 0;
	ROS_DEBUG("[CWheelServerMock] moveToDeltaTheta");
	return RETURN_SUCCESS;
}

int CWheelServerMock::moveToDeltaXYTheta( int deltaX, int deltaY, int deltaTheta, double velocity )
{
	if(isEmergency) return 0;
	ROS_DEBUG("[CWheelServerMock] moveToDeltaXYTheta");
	return RETURN_SUCCESS;
}

int CWheelServerMock::moveByVelocityXYT( double velX, double velY, double velTheta )
{
	if(isEmergency) return 0;
	ROS_DEBUG("[CWheelServerMock] moveByVelocityXYT");
	return RETURN_SUCCESS;
}

int CWheelServerMock::waitmoveToDeltaFinished() {
	ROS_DEBUG("[CWheelServerMock] waitmoveToDeltaFinished");
	return RETURN_SUCCESS;
}

int CWheelServerMock::moveByWheelVelocity(double wheel1Rpm, double wheel2Rpm, double wheel3Rpm)
{
	if(isEmergency) return 0;
	ROS_DEBUG("[CWheelServerMock] moveByWheelVelocity");
	return RETURN_SUCCESS;
}

int CWheelServerMock::reset()
{
	if(isEmergency) return 0;
	ROS_DEBUG("[CWheelServerMock] reset");
	return RETURN_SUCCESS;
}

int CWheelServerMock::moveByTwistMsg(const geometry_msgs::Twist& twistMsg)
{
	if(isEmergency) return 0;
	ROS_DEBUG("[CWheelServerMock] moveByTwistMsg");
	return RETURN_SUCCESS;
}

int CWheelServerMock::emergencyStop()
{
	ROS_DEBUG("[CWheelServerMock] emergencyStop");
	isEmergency = true;
	return RETURN_SUCCESS;
}

int CWheelServerMock::emergencyRelease()
{
	ROS_DEBUG("[CWheelServerMock] emergencyRelease");
	isEmergency = false;
	return RETURN_SUCCESS;
}

int CWheelServerMock::emergencyMoveByVelocityXYT( double velX, double velY, double velTheta) {
	ROS_DEBUG("[CWheelServerMock] emergencyMoveByVelocityXYT");
	return RETURN_SUCCESS;
}

int CWheelServerMock::selfDiagnosis(short errorCode[9]) {
	for(int i=0; i<9; i++) {
		errorCode[i] = -1;
	}
	return RETURN_SUCCESS;
}
