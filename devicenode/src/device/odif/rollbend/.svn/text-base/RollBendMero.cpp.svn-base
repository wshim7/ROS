/*
 * RollBendMeroS.cpp
 *
 *  Created on: 2014. 1. 14.
 *      Author: msyoo
 */

#include "RollBendServer.h"

int CRollBendMERO::MIN_ROLLBEND_VELOCITY = -1;
int CRollBendMERO::MAX_ROLLBEND_VELOCITY = 100;

double CRollBendMERO::MIN_ROLL_DEGREE = -13.0;
double CRollBendMERO::MAX_ROLL_DEGREE = 13.0;

double CRollBendMERO::MIN_BEND_DEGREE = -20.0;
double CRollBendMERO::MAX_BEND_DEGREE = 20.0;


CRollBendMERO::CRollBendMERO()
{
	rs485 =  MeroNeckDriver::getInstance();
	robotConfig = new CRobotConfig(MEROLimits);

	if(robotConfig->loadConfig("MERO", "rollbend")){
		setLimits();
	}
}



CRollBendMERO::~CRollBendMERO()
{
}



CRollBendMERO *CRollBendMERO::getInstance()
{
	static CRollBendMERO thisInstance;
	cout << "[CRollBendMERO.getInstance] : Create Sole Instance(RollBend).." << endl;
	return &thisInstance;
}



int CRollBendMERO::on()
{
	return RETURN_SUCCESS;
}



int CRollBendMERO::off()
{
	int res = 0;
	res = rs485->motorOff(SECOND);
	return res;
}



int CRollBendMERO::stop()
{
	return RETURN_SUCCESS;
}



int CRollBendMERO::moveToHome(int speed)
{
	moveToAbsolutePosition(0.0, 0.0, speed);
	return RETURN_SUCCESS;
}



int CRollBendMERO::moveToAbsolutePosition(double degreeRoll, double degreeBend, int speed)
{
	if(speed < MIN_ROLLBEND_VELOCITY)	speed = MIN_ROLLBEND_VELOCITY;
	if(speed > MAX_ROLLBEND_VELOCITY)	speed = MAX_ROLLBEND_VELOCITY;

	if(degreeRoll < MIN_ROLL_DEGREE )	degreeRoll = MIN_ROLL_DEGREE;
	if(degreeRoll > MAX_ROLL_DEGREE )	degreeRoll = MAX_ROLL_DEGREE;
	if(degreeBend < MIN_BEND_DEGREE )	degreeBend = MIN_BEND_DEGREE;
	if(degreeBend > MAX_BEND_DEGREE )	degreeBend = MAX_BEND_DEGREE;

	rs485->contorlPeriodmoveAbsMotor(SECOND,  degreeRoll,  degreeBend, speed);
	return RETURN_SUCCESS;
}

int CRollBendMERO::moveToAbsolutePositionWithSpeed(double degreeRoll, double degreeBend, int speedRoll, int speedBend)
{
	if(speedRoll < MIN_ROLLBEND_VELOCITY)	speedRoll = MIN_ROLLBEND_VELOCITY;
	if(speedRoll > MAX_ROLLBEND_VELOCITY)	speedRoll = MAX_ROLLBEND_VELOCITY;

	if(degreeRoll < MIN_ROLL_DEGREE )	degreeRoll = MIN_ROLL_DEGREE;
	if(degreeRoll > MAX_ROLL_DEGREE )	degreeRoll = MAX_ROLL_DEGREE;
	if(degreeBend < MIN_BEND_DEGREE )	degreeBend = MIN_BEND_DEGREE;
	if(degreeBend > MAX_BEND_DEGREE )	degreeBend = MAX_BEND_DEGREE;

	//cout<< "moveToAbsolutePositionWithSpeed: " << degreeRoll <<" " << degreeBend<<" " << speedRoll <<" " << speedBend << endl ;
	rs485->contorlPeriodmoveAbsMotor(SECOND,  degreeRoll,  degreeBend, speedRoll);
	return RETURN_SUCCESS;
}



int CRollBendMERO::moveToRelativePosition(double degreeRoll, double degreeBend, int speed)
{
	return RETURN_SUCCESS;
}



int CRollBendMERO::move2MotorSync(int motorID1, int motorSpeed1, int motorPosition1, int motorID2, int motorSpeed2, int motorPosition2)
{
	return RETURN_SUCCESS;
}



int CRollBendMERO::moveMotor(int motorID, int motorSpeed, int motorPosition)
{
	return RETURN_SUCCESS;
}



void CRollBendMERO::setLimits()
{
	MIN_ROLLBEND_VELOCITY = (int)MEROLimits["MIN_ROLLBEND_VELOCITY"];
	MAX_ROLLBEND_VELOCITY = (int)MEROLimits["MAX_ROLLBEND_VELOCITY"];
	MIN_ROLL_DEGREE	= MEROLimits["MIN_ROLL_DEGREE"];
	MAX_ROLL_DEGREE	= MEROLimits["MAX_ROLL_DEGREE"];
	MIN_BEND_DEGREE = MEROLimits["MIN_BEND_DEGREE"];
	MAX_BEND_DEGREE = MEROLimits["MAX_BEND_DEGREE"];
}



void CRollBendMERO::getPosition(CRollBendPosition & position)
{
	double roll, bend;
	rs485->getDegrees(SECOND, roll, bend);
	position.setDegreeRoll(roll);
	position.setDegreeBend(bend);
}

void CRollBendMERO::detectingError(short errorCode[3])
{
	rs485->errorCheck(SECOND, errorCode);
}
