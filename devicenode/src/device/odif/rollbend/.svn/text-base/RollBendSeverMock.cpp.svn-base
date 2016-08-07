/*
 * RollBendSeverMock.cpp
 *
 *  Created on: 2014. 1. 14.
 *      Author: msyoo
 */

#include "RollBendServer.h"



CRollBendServerMock::CRollBendServerMock()
{
}



CRollBendServerMock::~CRollBendServerMock()
{
}



int CRollBendServerMock::on()
{
	return RETURN_SUCCESS;
}


int CRollBendServerMock::off()
{
	return RETURN_SUCCESS;
}



int CRollBendServerMock::stop()
{
	return RETURN_SUCCESS;
}



int CRollBendServerMock::moveToHome(int speed)
{
	return RETURN_SUCCESS;
}



int CRollBendServerMock::moveToAbsolutePosition(double degreeRoll, double degreeBend, int speed)
{
	ROS_DEBUG("CRollBendServerMock::moveToAbsolutePosition(degLR : %f, degUD: %f, speed: %d) called", degreeRoll, degreeBend, speed);
	return RETURN_SUCCESS;
}



int CRollBendServerMock::moveToAbsolutePositionWithSpeed(double degreeRoll, double degreeBend, int speedRoll, int speedBend)
{
	ROS_DEBUG("CRollBendServerMock::moveToAbsolutePositionWithSpeed(degLR : %f, degUD: %f, speedRoll: %d, speedBend: %d) called", degreeRoll, degreeBend, speedRoll, speedBend);
	return RETURN_SUCCESS;
}


int CRollBendServerMock::moveToRelativePosition(double degreeRoll, double degreeBend, int speed)
{
	return RETURN_SUCCESS;
}



int CRollBendServerMock::move2MotorSync(int motorID1, int motorSpeed1, int motorPosition1, int motorID2, int motorSpeed2, int motorPosition2)
{
	return RETURN_SUCCESS;
}



int CRollBendServerMock::moveMotor(int motorID, int motorSpeed, int motorPosition)
{
	return RETURN_SUCCESS;
}



void CRollBendServerMock::getPosition(CRollBendPosition & position)
{
	position.setDegreeRoll(0.0);
	position.setEncoderBend(0.0);
	ROS_DEBUG("CRollBendServerMock::getPosition(degreeRoll : %f, degreeBend: %f) called",  position.getDegreeRoll(), position.getDegreeBend() );
}


void  CRollBendServerMock::detectingError(short errorCode[3])
{
	ROS_DEBUG("CRollBendServerMock::detectingError called");
	errorCode[0] =0;
	errorCode[1] =0;
	errorCode[2] =0;
}
