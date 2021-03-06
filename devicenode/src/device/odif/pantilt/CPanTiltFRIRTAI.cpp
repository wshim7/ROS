#include "PantiltServer.h"
#include <math.h>
#include <roscir/env/Config.h>

#include <iostream>
using namespace std;

//const double CPanTiltFRIRTAI::MIN_PAN_DEGREE = -60.0;		// CCW 
//const double CPanTiltFRIRTAI::MAX_PAN_DEGREE = 60.0;		// CW
//
//const double CPanTiltFRIRTAI::MIN_TILT_DEGREE = -30.0;	// DOWN
//const double CPanTiltFRIRTAI::MAX_TILT_DEGREE = 30.0;		// UP
//
//const double CPanTiltFRIRTAI::MIN_PANTILT_VELOCITY = 0.0;
//const double CPanTiltFRIRTAI::MAX_PANTILT_VELOCITY = 100.0;


double CPanTiltFRIRTAI::MIN_PAN_DEGREE = -60.0;		// CCW 
double CPanTiltFRIRTAI::MAX_PAN_DEGREE = 60.0;		// CW

double CPanTiltFRIRTAI::MIN_TILT_DEGREE = -30.0;	// DOWN
double CPanTiltFRIRTAI::MAX_TILT_DEGREE = 30.0;		// UP

double CPanTiltFRIRTAI::MIN_PANTILT_VELOCITY = 0.0;
double CPanTiltFRIRTAI::MAX_PANTILT_VELOCITY = 100.0;


CPanTiltFRIRTAI::CPanTiltFRIRTAI()
{
	neckrs232 =  NeckRS232::getInstance();

	robotConfig = new CRobotConfig(FRILimits);

	if(robotConfig->loadConfig("FRI", "pantilt")){
		setLimits();
		//cout << "[CPanTiltFRIRTAI]Limits: " << FRILimits["MIN_PAN_DEGREE"] << endl;
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


CPanTiltFRIRTAI::~CPanTiltFRIRTAI()
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


CPanTiltFRIRTAI* CPanTiltFRIRTAI::getInstance()
{
	static CPanTiltFRIRTAI thisInstance;
    cout << "[CPanTiltRTAI.getInstance] : Create Sole Instance(PanTilt).." << endl;
    return &thisInstance;
}

void CPanTiltFRIRTAI::setLimits()
{
	MIN_PAN_DEGREE = FRILimits["MIN_PAN_DEGREE"];
	MAX_PAN_DEGREE = FRILimits["MAX_PAN_DEGREE"];
	MIN_TILT_DEGREE	= FRILimits["MIN_TILT_DEGREE"];
	MAX_TILT_DEGREE	= FRILimits["MAX_TILT_DEGREE"];
	MIN_PANTILT_VELOCITY = FRILimits["MIN_PANTILT_VELOCITY"];
	MAX_PANTILT_VELOCITY = FRILimits["MAX_PANTILT_VELOCITY"];
}

int CPanTiltFRIRTAI::on()
{
	moveToAbsolutePosition(0.0,0.0,20);
	FRIPanTiltPos.setDegreeLeftRight(0.0);
	FRIPanTiltPos.setDegreeUpDown(0.0);
	
	// add FRI team code
	return 0;

}


int CPanTiltFRIRTAI::off()
{
	// add FRI team code
	return 0;
}


int CPanTiltFRIRTAI::stop()
{
	// add FRI team code
    return 0;
}


int CPanTiltFRIRTAI::moveToHome( int speed )
{
	// add FRI team code
	moveToAbsolutePosition(0,0,speed);
	return 0;
}


int CPanTiltFRIRTAI::moveToAbsolutePosition( double degreeLeftRight, double degreeUpDown, int speed )
{
	// add FRI team code
	unsigned int PanningDegree, TiltingDegree;

	if(speed < MIN_PANTILT_VELOCITY)	speed = MIN_PANTILT_VELOCITY;
	if(speed > MAX_PANTILT_VELOCITY)	speed = MAX_PANTILT_VELOCITY;
	if(degreeLeftRight < MIN_PAN_DEGREE )	degreeLeftRight = MIN_PAN_DEGREE;
	if(degreeLeftRight > MAX_PAN_DEGREE )	degreeLeftRight = MAX_PAN_DEGREE;
	if(degreeUpDown < MIN_TILT_DEGREE )	degreeUpDown = MIN_TILT_DEGREE;
	if(degreeUpDown > MAX_TILT_DEGREE )	degreeUpDown = MAX_TILT_DEGREE;

	//printf("==> pan= %.2f, tilt= %.2f, speed= %d\n", degreeLeftRight, degreeUpDown, speed);
	
	if(m_neckType == 0){
		FRIPanTiltPos.setDegreeLeftRight(degreeLeftRight);
		FRIPanTiltPos.setDegreeUpDown(degreeUpDown);
		//PanningDegree=150-((int)degreeUpDown+2*(int)degreeLeftRight);
		PanningDegree=150-(int)(degreeUpDown+ 2.0 * degreeLeftRight);
		TiltingDegree=150 - (int)(-degreeUpDown + 2.0 * degreeLeftRight);
	}else if(m_neckType == 1){

		degreeLeftRight = degreeLeftRight/1.5;

		PanningDegree=150-(int)(degreeUpDown + 2 * degreeLeftRight);
		TiltingDegree=150 - (int)(-degreeUpDown + 2 * degreeLeftRight);
	}
	//TiltingDegree=150-(-(int)degreeUpDown+2*(int)degreeLeftRight);
	
    return move2MotorSync( 1, speed, PanningDegree, 2, speed, TiltingDegree );
}

int CPanTiltFRIRTAI::moveToRelativePosition( double degreeLeftRight, double degreeUpDown, int speed )
{
	// add FRI team code
    return 0;
}

int CPanTiltFRIRTAI::move2MotorSync( int motorID1, int motorSpeed1, int motorPosition1, int motorID2, int motorSpeed2, int motorPosition2 )
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

int CPanTiltFRIRTAI::moveMotor( int motorID, int motorSpeed, int motorPosition )
{

	FriNeckCmdfifo.cmd = FRI_NECK_CMDFIFO_CMD_MOVEMOTOR;
	FriNeckCmdfifo.motorID[0] = motorID;
	FriNeckCmdfifo.speed[0] = motorSpeed;
	FriNeckCmdfifo.position[0] = motorPosition;

	return neckrs232->sendMessageToNeck(&FriNeckCmdfifo);
}


void CPanTiltFRIRTAI::getPosition(CPanTiltPosition& position)
{
	double pan, tilt;

	if(m_encoderEnable == 0){
		pan = FRIPanTiltPos.getDegreeLeftRight();
		tilt = FRIPanTiltPos.getDegreeUpDown();
	}else if(m_encoderEnable == 1){
		neckrs232->getNeckPosition(1, pan, tilt);
		pan *= 1.5;
	//	tilt *= 1.5;
	}
	position.setDegreeLeftRight(pan);
	position.setDegreeUpDown(tilt);
}


int CPanTiltFRIRTAI::setCompliance(int option)
{
	return neckrs232->setMotorCompliance(option);
}

int CPanTiltFRIRTAI::moveToAbsolutePositionWithSpeed(double degreeLeftRight, double degreeUpDown, int speedLeftRight, int speedUpDown) {
	return 0;
}

void CPanTiltFRIRTAI::emergencyStop() {
}

void CPanTiltFRIRTAI::emergencyRelease() {
}

int CPanTiltFRIRTAI::moveToABSAll(int panAngle, int tiltAngle, int xtionAngle, int panSpeed, int tiltSpeed, int xtionSpeed) {
	return RETURN_SUCCESS;
}
int CPanTiltFRIRTAI::moveXtionTilt(int xtionAngle, int xtionSpeed) {


	return RETURN_SUCCESS;

}

int CPanTiltFRIRTAI::getXtionTiltAngle() {
	return RETURN_SUCCESS;
}

void CPanTiltFRIRTAI::detectingError(short errorCode[3]) {
}
