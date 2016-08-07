#include "WheelServer.h"

CWheelServerProxy::CWheelServerProxy()
{
    int typeOfRobot	= CConfig::getInstance()->getParamValueInt( "ROBOT_TYPE" );
    int serverDeviceType	= CConfig::getInstance()->getParamValueInt( "SERVER_DEVICE_TYPE" );
	//cout << " [CWheelServerProxy] server type " << typeOfServerDevice << endl;
	//cout << " [CWheelServerProxy] robot type " << typeOfRobot << endl;
	ROS_DEBUG("[CWheelServerProxy] robot type : %d", typeOfRobot);

	switch (typeOfRobot) {
		case ROBOT_TYPE_EROBOT:
			switch (serverDeviceType) {
				case SERVER_DEVICE_REAL:
				case SERVER_DEVICE_BOTH:
					wheel = new CWheelERobot();
					break;
				case SERVER_DEVICE_SIMULATOR:
					wheel = new CWheelERobot();
					break;
				default:
					wheel = new CWheelServerMock();
					break;
				}
				break;
	
		default:
			cout << "!!!! No matching robot type  !!!! " << typeOfRobot << endl;
			wheel = new CWheelServerMock();
			break;
	}
}


CWheelServerProxy::~CWheelServerProxy()
{
}



CWheel* CWheelServerProxy::getInstance()
{
	static CWheelServerProxy instance;
	return &instance;
}


int CWheelServerProxy::on()
{
	return wheel->on();
}


int CWheelServerProxy::off()
{
	return wheel->off();
}


int CWheelServerProxy::stop()
{
	return wheel->stop();
}


int CWheelServerProxy::moveByTRVelocity( double translationalVelocity, double rotationalVelocity )
{
	return wheel->moveByTRVelocity( translationalVelocity, rotationalVelocity );
}


int CWheelServerProxy::moveByWheelVelocity( double leftWheelVelocity, double rightWheelVelocity )
{
	return wheel->moveByWheelVelocity( leftWheelVelocity, rightWheelVelocity );
}


int CWheelServerProxy::moveToDeltaX( int deltaX, double velocity )
{
	return wheel->moveToDeltaX( deltaX, velocity );
}


int CWheelServerProxy::moveToDeltaTheta( int deltaTheta, int radius, double velocity )
{
	return wheel->moveToDeltaTheta( deltaTheta, radius, velocity );
}


int CWheelServerProxy::moveToDeltaXYTheta( int deltaX, int deltaY, int deltaTheta, double velocity )
{
	return wheel->moveToDeltaXYTheta( deltaX, deltaY, deltaTheta, velocity );
}

int CWheelServerProxy::moveByVelocityXYT( double velX, double velY, double velTheta)
{
	return wheel->moveByVelocityXYT(velX, velY, velTheta);
}

int CWheelServerProxy::waitmoveToDeltaFinished() {
	return wheel->waitmoveToDeltaFinished();
}

int CWheelServerProxy::emergencyStop()
{
	return wheel->emergencyStop();
}

int CWheelServerProxy::emergencyRelease()
{
	return wheel->emergencyRelease();
}

int CWheelServerProxy::moveByWheelVelocity(double wheel1Rpm, double wheel2Rpm, double wheel3Rpm)
{
	return wheel->moveByWheelVelocity(wheel1Rpm, wheel2Rpm, wheel3Rpm);
}

int CWheelServerProxy::reset()
{
	return wheel->reset();
}

int CWheelServerProxy::moveByTwistMsg(const geometry_msgs::Twist& twistMsg) {
	return wheel->moveByTwistMsg(twistMsg);
}
int CWheelServerProxy::emergencyMoveByVelocityXYT( double velX, double velY, double velTheta) {
	return wheel->emergencyMoveByVelocityXYT(velX, velY, velTheta);
}

int CWheelServerProxy::selfDiagnosis(short errorCode[9]) {
	return wheel->selfDiagnosis(errorCode);
}
