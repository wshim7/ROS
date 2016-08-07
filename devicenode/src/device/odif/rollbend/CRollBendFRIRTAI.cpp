#include <math.h>
#include "RollBendServer.h"
#include <roscir/env/Config.h>
#include <iostream>
using namespace std;

// initialize static variable
//const double CRollBendFRIRTAI::PAN_OFFSET =0;
//    = CConfig::getInstance()->getParamValueDouble( "common.cpp.odif.CRollBendFRIRTAI.rollOffset" );
//const double CRollBendFRIRTAI::TILT_OFFSET = 0;
//    = CConfig::getInstance()->getParamValueDouble( "common.cpp.odif.CRollBendFRIRTAI.bendOffset" );


int CRollBendFRIRTAI::MIN_ROLLBEND_VELOCITY = 0;
int CRollBendFRIRTAI::MAX_ROLLBEND_VELOCITY = 100;

double CRollBendFRIRTAI::MIN_ROLL_DEGREE = -40.0;	// CCW 
double CRollBendFRIRTAI::MAX_ROLL_DEGREE = 40.0;		// CW

double CRollBendFRIRTAI::MIN_BEND_DEGREE = -45.0;	// DOWN
double CRollBendFRIRTAI::MAX_BEND_DEGREE = 40.0;		// UP

CRollBendFRIRTAI::CRollBendFRIRTAI()
{
	neckrs232 = NeckRS232::getInstance();

	robotConfig = new CRobotConfig(FRILimits);

	if(robotConfig->loadConfig("FRI", "rollbend")){
		setLimits();
		//cout << "[CRollBendFRIRTAI]Limits: " << FRILimits["MIN_BEND_DEGREE"] << endl;
	}

	CConfig* config = CConfig::getInstance();
	m_neckType = config->getParamValueInt("NECK_DEVICE_TYPE");
	if(m_neckType == -1){
		m_neckType =0;
	}

	m_encoderEnable = config->getParamValueInt("ENCODER_ENABLE");
	if(m_encoderEnable == -1){
		m_encoderEnable =0;
	}

}


CRollBendFRIRTAI::~CRollBendFRIRTAI()
{

	if(robotConfig){
		delete robotConfig;
		robotConfig = NULL;
	}

	if(neckrs232){
		delete neckrs232;
		neckrs232 = NULL;
	}
}



CRollBendFRIRTAI* CRollBendFRIRTAI::getInstance()
{
	static CRollBendFRIRTAI thisInstance;
	cout << "[CRollBendFRIRTAI.getInstance] : Create Sole Instance(RollBend).." << endl;
	return &thisInstance;
}

void CRollBendFRIRTAI::setLimits()
{
	MIN_ROLLBEND_VELOCITY = FRILimits["MIN_ROLLBEND_VELOCITY"];
	MAX_ROLLBEND_VELOCITY = FRILimits["MAX_ROLLBEND_VELOCITY"];
	MIN_ROLL_DEGREE	= FRILimits["MIN_ROLL_DEGREE"];
	MAX_ROLL_DEGREE	= FRILimits["MAX_ROLL_DEGREE"];
	MIN_BEND_DEGREE = FRILimits["MIN_BEND_DEGREE"];
	MAX_BEND_DEGREE = FRILimits["MAX_BEND_DEGREE"];
}

int CRollBendFRIRTAI::on()
{
	moveToAbsolutePosition(0.0,0.0,20);
	FRIRollBendPos.setDegreeRoll(0.0);
	FRIRollBendPos.setDegreeBend(0.0);

	return 0;
}


int CRollBendFRIRTAI::off()
{
	// add FRI team code
	return 0;

}


int CRollBendFRIRTAI::stop()
{

	// add FRI team code
	return 0;

}


int CRollBendFRIRTAI::moveToHome( int speed )
{

	// add FRI team code
	moveToAbsolutePosition(0,0,speed);
	return 0;

}


int CRollBendFRIRTAI::moveToAbsolutePosition( double degreeLeftRight, double degreeUpDown, int speed )
{
	unsigned int RollingDegree, BendingDegree;

	if(speed < MIN_ROLLBEND_VELOCITY)	speed = MIN_ROLLBEND_VELOCITY;
	if(speed > MAX_ROLLBEND_VELOCITY)	speed = MAX_ROLLBEND_VELOCITY;

	if(degreeLeftRight < MIN_ROLL_DEGREE )	degreeLeftRight = MIN_ROLL_DEGREE;
	if(degreeLeftRight > MAX_ROLL_DEGREE )	degreeLeftRight = MAX_ROLL_DEGREE;
	if(degreeUpDown < MIN_BEND_DEGREE )	degreeUpDown = MIN_BEND_DEGREE;
	if(degreeUpDown > MAX_BEND_DEGREE )	degreeUpDown = MAX_BEND_DEGREE;

	//printf("==> roll= %.2f, bend= %.2f, speed= %d\n", degreeLeftRight, degreeUpDown, speed);


	if(m_neckType == 0){
		FRIRollBendPos.setDegreeRoll(degreeLeftRight);
		FRIRollBendPos.setDegreeBend (degreeUpDown);
	}

	degreeUpDown *= -1;

	if(m_neckType == 0){
		RollingDegree=150-(int)(degreeUpDown+2.0*degreeLeftRight);
		BendingDegree=150-(int)(-degreeUpDown+2.0*degreeLeftRight);
	}else if(m_neckType == 1){

		degreeLeftRight = degreeLeftRight/1.5;
		RollingDegree=150-(int)(degreeUpDown+2.0*degreeLeftRight);
		BendingDegree=150-(int)(-degreeUpDown+2.0*degreeLeftRight);
	}
	


	move2MotorSync( 3, speed, RollingDegree, 4, speed, BendingDegree );

	// add FRI team code
	return 0;

}


int CRollBendFRIRTAI::moveToRelativePosition( double degreeLeftRight, double degreeUpDown, int speed )
{

	return 0;

}


int CRollBendFRIRTAI::move2MotorSync( int motorID1, int motorSpeed1, int motorPosition1, int motorID2, int motorSpeed2, int motorPosition2 )
{
	FriNeckCmdfifo.cmd = FRI_NECK_CMDFIFO_CMD_MOVE2MOTORSYNC;
	FriNeckCmdfifo.motorID[0] = motorID1;
	FriNeckCmdfifo.motorID[1] = motorID2;
	FriNeckCmdfifo.speed[0] = motorSpeed1;
	FriNeckCmdfifo.speed[1] = motorSpeed2;
	FriNeckCmdfifo.position[0] = motorPosition1;
	FriNeckCmdfifo.position[1] = motorPosition2;
	
	return neckrs232->sendMessageToNeck(&FriNeckCmdfifo);

}

int CRollBendFRIRTAI::moveMotor( int motorID, int motorSpeed, int motorPosition )
{

	FriNeckCmdfifo.cmd = FRI_NECK_CMDFIFO_CMD_MOVEMOTOR;
	FriNeckCmdfifo.motorID[0] = motorID;
	FriNeckCmdfifo.speed[0] = motorSpeed;
	FriNeckCmdfifo.position[0] = motorPosition;

	return neckrs232->sendMessageToNeck(&FriNeckCmdfifo);

}


void CRollBendFRIRTAI::getPosition(CRollBendPosition& position)
{

	double roll, bend;

	if(m_encoderEnable ==0){

		roll = FRIRollBendPos.getDegreeRoll();
		bend = FRIRollBendPos.getDegreeBend();
	}else if(m_encoderEnable ==1){
		neckrs232->getNeckPosition(2, roll, bend);
		roll *= 1.5;
		//bend *= 1.5;
	} 
	
	position.setDegreeRoll(roll);
	position.setDegreeBend (-bend);

}

void CRollBendFRIRTAI::detectingError(short errorCode[3])
{
	errorCode[0] = 0;
	errorCode[1] = 0;
	errorCode[2] = 0;
}



