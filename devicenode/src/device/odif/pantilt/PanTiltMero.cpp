/*
 * PanTiltMeroS.cpp
 *
 *  Created on: 2014. 1. 14.
 *      Author: msyoo
 */

#include <device/odif/pantilt/PantiltServer.h>


double CPanTiltMero::MIN_PAN_DEGREE = -90.0;		// CCW
double CPanTiltMero::MAX_PAN_DEGREE = 90.0;		// CW

double CPanTiltMero::MIN_TILT_DEGREE = -15.0;	// DOWN
double CPanTiltMero::MAX_TILT_DEGREE = 15.0;		// UP

int CPanTiltMero::MIN_PANTILT_VELOCITY = -1;
int CPanTiltMero::MAX_PANTILT_VELOCITY = 100;


CPanTiltMero::CPanTiltMero()
{
	rs485 =  MeroNeckDriver::getInstance();

	robotConfig = new CRobotConfig(MEROLimits);

	if(robotConfig->loadConfig("MERO", "pantilt")){
		setLimits();
	}
}

CPanTiltMero::~CPanTiltMero()
{
}




CPanTiltMero *CPanTiltMero::getInstance()
{
	static CPanTiltMero thisInstance;
	cout << "[CPanTiltMeroS.getInstance] : Create Sole Instance(PanTilt).." << endl;
	return &thisInstance;
}


int CPanTiltMero::on()
{
	int res = 0;
	res = rs485->initPantiltRollBendMotors();
	return res;
}



int CPanTiltMero::off()
{
	int res = 0;
	res = rs485->motorOff(FIRST);
	return res;
}



int CPanTiltMero::stop()
{
	return RETURN_SUCCESS;
}



int CPanTiltMero::moveToHome(int speed)
{
	moveToAbsolutePosition(0.0, 0.0, 50);
	return RETURN_SUCCESS;
}



int CPanTiltMero::moveToAbsolutePosition(double degreeLeftRight, double degreeUpDown, int speed)
{
	if(speed < MIN_PANTILT_VELOCITY)	speed = MIN_PANTILT_VELOCITY;

	if(speed > MAX_PANTILT_VELOCITY)	speed = MAX_PANTILT_VELOCITY;

	if(degreeLeftRight < MIN_PAN_DEGREE )	degreeLeftRight = MIN_PAN_DEGREE;

	if(degreeLeftRight > MAX_PAN_DEGREE )	degreeLeftRight = MAX_PAN_DEGREE;

	if(degreeUpDown < MIN_TILT_DEGREE )	degreeUpDown = MIN_TILT_DEGREE;

	if(degreeUpDown > MAX_TILT_DEGREE )	degreeUpDown = MAX_TILT_DEGREE;

	rs485->contorlPeriodmoveAbsMotor(FIRST,  degreeLeftRight,  degreeUpDown, speed);
	return RETURN_SUCCESS;
}


int CPanTiltMero::moveToAbsolutePositionWithSpeed(double degreeLeftRight, double degreeUpDown, int speedLeftRight, int speedUpDown)
{
	if(speedLeftRight < MIN_PANTILT_VELOCITY)	speedLeftRight = MIN_PANTILT_VELOCITY;

	if(speedLeftRight > MAX_PANTILT_VELOCITY)	speedLeftRight = MAX_PANTILT_VELOCITY;

	if(degreeLeftRight < MIN_PAN_DEGREE )	degreeLeftRight = MIN_PAN_DEGREE;

	if(degreeLeftRight > MAX_PAN_DEGREE )	degreeLeftRight = MAX_PAN_DEGREE;

	if(degreeUpDown < MIN_TILT_DEGREE )	degreeUpDown = MIN_TILT_DEGREE;

	if(degreeUpDown > MAX_TILT_DEGREE )	degreeUpDown = MAX_TILT_DEGREE;

	rs485->contorlPeriodmoveAbsMotor(FIRST,  degreeLeftRight,  degreeUpDown, speedLeftRight);
	//cout<< "moveToAbsolutePositionWithSpeed: " << degreeLeftRight <<" " << degreeUpDown<<" " << speedLeftRight <<" " << speedUpDown << endl ;
	return RETURN_SUCCESS;
}



int CPanTiltMero::moveToRelativePosition(double degreeLeftRight, double degreeUpDown, int speed)
{
	return RETURN_SUCCESS;
}



int CPanTiltMero::move2MotorSync(int motorID1, int motorSpeed1, int motorPosition1, int motorID2, int motorSpeed2, int motorPosition2)
{
	return RETURN_SUCCESS;
}



int CPanTiltMero::moveMotor(int motorID, int motorSpeed, int motorPosition)
{
	return RETURN_SUCCESS;
}



void CPanTiltMero::getPosition(CPanTiltPosition & position)
{
	double pan, tilt;
	rs485->getDegrees(FIRST, pan, tilt);
	position.setDegreeLeftRight(pan);
	position.setDegreeUpDown(tilt);
}



int CPanTiltMero::setCompliance(int option)
{
	bool res;
	cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
	cout << "setCompliance [ " << option << " ]" << endl;
	cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
	res = rs485->setCompliance(option);
	return (int)res;
}




int CPanTiltMero::moveToABSAll(int panAngle, int tiltAngle, int xtionAngle, int panSpeed, int tiltSpeed, int xtionSpeed)
{
	return RETURN_SUCCESS;
}

void CPanTiltMero::emergencyStop() {
}

void CPanTiltMero::setLimits(){
	MIN_PAN_DEGREE = MEROLimits["MIN_PAN_DEGREE"];
	MAX_PAN_DEGREE = MEROLimits["MAX_PAN_DEGREE"];
	MIN_TILT_DEGREE	= MEROLimits["MIN_TILT_DEGREE"];
	MAX_TILT_DEGREE	= MEROLimits["MAX_TILT_DEGREE"];
	MIN_PANTILT_VELOCITY = (int)MEROLimits["MIN_PANTILT_VELOCITY"];
	MAX_PANTILT_VELOCITY = (int)MEROLimits["MAX_PANTILT_VELOCITY"];
}



void CPanTiltMero::emergencyRelease() {

}

void CPanTiltMero::detectingError(short errorCode[3]) {

	rs485->errorCheck(FIRST, errorCode);
}
