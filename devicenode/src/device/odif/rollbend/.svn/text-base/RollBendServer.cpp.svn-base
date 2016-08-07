/*
 * RollBendServer.cpp
 *
 *  Created on: 2014. 1. 14.
 *      Author: msyoo
 */



#include "RollBendServer.h"




CRollBendServerProxy::CRollBendServerProxy()
{
	int typeOfServer	= CConfig::getInstance()->getParamValueInt( "SERVER_DEVICE_TYPE" );
    int typeOfRobot		= CConfig::getInstance()->getParamValueInt( "ROBOT_TYPE" );
	ROS_DEBUG("[CRollBendServerProxy] robot type : %d", typeOfRobot);
	ROS_DEBUG("[CRollBendServerProxy] server type : %d",typeOfServer);

	if(typeOfServer == SERVER_DEVICE_MOCK) {
		RollBend = new CRollBendServerMock;
	} else {
		switch (typeOfRobot) {
			case ROBOT_TYPE_MERO :
				if(typeOfServer == SERVER_DEVICE_REAL) {
					RollBend = new CRollBendMERO();
				} else if( typeOfServer == SERVER_DEVICE_SIMULATOR) {

				} else if( typeOfServer == SERVER_DEVICE_BOTH) {
					RollBend = new CRollBendMERO();
				}
				break;
			case ROBOT_TYPE_MERO_S :

				if(typeOfServer == SERVER_DEVICE_REAL) {
					RollBend = new CRollBendMERO();
				} else if( typeOfServer == SERVER_DEVICE_SIMULATOR) {

				} else if( typeOfServer == SERVER_DEVICE_BOTH) {
					RollBend = new CRollBendMERO();
				}
				break;
			case ROBOT_TYPE_FRI :
				RollBend = new CRollBendFRIRTAI;
				break;
			default:
				ROS_ERROR("CRollBendServerProxy : no typeOfRobot defined. ensure the typeOfRobot through roscir config.xml");
				RollBend = new CRollBendServerMock;
				break;
		}
	}

}



CRollBendServerProxy::~CRollBendServerProxy()
{
}


CRollBend *CRollBendServerProxy::getInstance()
{
	static CRollBendServerProxy instance;
	return &instance;

}



int CRollBendServerProxy::on()
{
	return RollBend->on();
}



int CRollBendServerProxy::off()
{
	return RollBend->off();
}



int CRollBendServerProxy::stop()
{
	return RollBend->stop();
}



int CRollBendServerProxy::moveToHome(int speed)
{
	return RollBend->moveToHome(speed);
}



int CRollBendServerProxy::moveToAbsolutePosition(double degreeRoll, double degreeBend, int speed)
{
	return RollBend->moveToAbsolutePosition(degreeRoll,  degreeBend, speed);
}



int CRollBendServerProxy::moveToAbsolutePositionWithSpeed(double degreeRoll, double degreeBend, int speedRoll, int speedBend)
{
	return RollBend->moveToAbsolutePositionWithSpeed(degreeRoll,  degreeBend,  speedRoll,  speedBend);
}



int CRollBendServerProxy::moveToRelativePosition(double degreeRoll, double degreeBend, int speed)
{
	return RollBend->moveToRelativePosition(degreeRoll, degreeBend, speed);
}



int CRollBendServerProxy::move2MotorSync(int motorID1, int motorSpeed1, int motorPosition1, int motorID2, int motorSpeed2, int motorPosition2)
{
	return RollBend->move2MotorSync(motorID1, motorSpeed1, motorPosition1, motorID2, motorSpeed2, motorPosition2);
}



int CRollBendServerProxy::moveMotor(int motorID, int motorSpeed, int motorPosition)
{
	return RollBend->moveMotor(motorID, motorSpeed, motorPosition);
}



void CRollBendServerProxy::getPosition(CRollBendPosition & position)
{
	return RollBend->getPosition(position);
}


void CRollBendServerProxy::detectingError(short errorCode[3])
{
	return RollBend->detectingError(errorCode);
}




