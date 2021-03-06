#include "PantiltServer.h"

CPanTiltServerProxy::CPanTiltServerProxy()
{ 

    int typeOfRobot   = CConfig::getInstance()->getParamValueInt( "ROBOT_TYPE" );
    int typeOfServer	= CConfig::getInstance()->getParamValueInt( "SERVER_DEVICE_TYPE" );
	//cout << "[CPanTiltServerProxy] server type: " << typeOfServer << endl;
	//cout << "[CPanTiltServerProxy] robot type " << typeOfRobot << endl;
	ROS_DEBUG("[CPanTiltServerProxy] robot type : %d", typeOfRobot);
	ROS_DEBUG("[CPanTiltServerProxy] Server Type : %d", typeOfServer);

	panTiltSimul = NULL;

	switch (typeOfRobot) {
		case ROBOT_TYPE_EROBOT:
			if(typeOfServer == SERVER_DEVICE_REAL) {
				panTilt = new CPanTiltERobot();
			} else if( typeOfServer == SERVER_DEVICE_SIMULATOR) {

			} else if( typeOfServer == SERVER_DEVICE_BOTH) {
				panTilt = new CPanTiltERobot();
			} else if( typeOfServer == SERVER_DEVICE_MOCK) {
				panTilt = new CPanTiltServerMock;
			}
			break;

		case ROBOT_TYPE_MERO :
			if(typeOfServer == SERVER_DEVICE_REAL) {
				panTilt = new CPanTiltMero();
			} else if( typeOfServer == SERVER_DEVICE_SIMULATOR) {

			} else if( typeOfServer == SERVER_DEVICE_BOTH) {
				panTilt = new CPanTiltMero();
			} else if( typeOfServer == SERVER_DEVICE_MOCK) {
				panTilt = new CPanTiltServerMock;
			}
			break;

		case ROBOT_TYPE_MERO_S :
			if(typeOfServer == SERVER_DEVICE_REAL) {
				panTilt = new CPanTiltMero();
			} else if( typeOfServer == SERVER_DEVICE_SIMULATOR) {

			} else if( typeOfServer == SERVER_DEVICE_BOTH) {
				panTilt = new CPanTiltMero();
			} else if( typeOfServer == SERVER_DEVICE_MOCK) {
				panTilt = new CPanTiltServerMock;
			}
			break;
		case ROBOT_TYPE_FRI :
			panTilt = new CPanTiltFRIRTAI();
			break;
		default:
			cout << "default PantiltServerMock " << endl;
			panTilt = new CPanTiltServerMock;
			break;
	}


}


CPanTiltServerProxy::~CPanTiltServerProxy()
{
}


CPanTilt* CPanTiltServerProxy::getInstance()
{
	static CPanTiltServerProxy instance;
	return &instance;
}


int CPanTiltServerProxy::on()
{
    return panTilt->on();
}


int CPanTiltServerProxy::off()
{
    return panTilt->off();
}


int CPanTiltServerProxy::stop()
{
    return panTilt->stop();
}


int CPanTiltServerProxy::moveToHome( int speed )
{
    return panTilt->moveToHome( speed );
}


int CPanTiltServerProxy::moveToAbsolutePosition( double degreeLeftRight, double degreeUpDown, int speed )
{
    return panTilt->moveToAbsolutePosition( degreeLeftRight, degreeUpDown, speed );
}


int CPanTiltServerProxy::moveToAbsolutePositionWithSpeed(double degreeLeftRight, double degreeUpDown, int speedLeftRight, int speedUpDown)
{
	return panTilt->moveToAbsolutePositionWithSpeed( degreeLeftRight, degreeUpDown, speedLeftRight,  speedUpDown);
}


int CPanTiltServerProxy::moveToRelativePosition( double degreeLeftRight, double degreeUpDown, int speed )
{
    return panTilt->moveToRelativePosition( degreeLeftRight, degreeUpDown, speed );
}


int CPanTiltServerProxy::move2MotorSync( int motorID1, int motorSpeed1, int motorPosition1, int motorID2, int motorSpeed2, int motorPosition2 )
{
    return panTilt->move2MotorSync(motorID1, motorSpeed1, motorPosition1, motorID2, motorSpeed2, motorPosition2);
}

int CPanTiltServerProxy::moveMotor( int motorID, int motorSpeed, int motorPosition )
{
	return panTilt->moveMotor(motorID, motorSpeed, motorPosition);
}


void CPanTiltServerProxy::getPosition(CPanTiltPosition& position)
{
    return panTilt->getPosition(position);
}

int CPanTiltServerProxy::setCompliance( int option )
{
	return panTilt->setCompliance(option);
}

int CPanTiltServerProxy::moveToABSAll(int panAngle, int tiltAngle, int xtionAngle, int panSpeed, int tiltSpeed, int xtionSpeed)
{
	return panTilt->moveToABSAll(panAngle, tiltAngle, xtionAngle, panSpeed, tiltSpeed, xtionSpeed);
}

int CPanTiltServerProxy::moveXtionTilt(int xtionAngle, int xtionSpeed) {
	return panTilt->moveXtionTilt(xtionAngle,xtionSpeed);
}

int CPanTiltServerProxy::getXtionTiltAngle() {
	return panTilt->getXtionTiltAngle();
}


void CPanTiltServerProxy::emergencyStop() {
	panTilt->emergencyStop();
}



void CPanTiltServerProxy::emergencyRelease() {
	panTilt->emergencyRelease();
}

void CPanTiltServerProxy::detectingError(short errorCode[3]) {
	panTilt->detectingError(errorCode);
}

