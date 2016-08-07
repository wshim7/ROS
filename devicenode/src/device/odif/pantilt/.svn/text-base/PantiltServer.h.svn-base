#ifndef __PANTILT_SERVER_H__
#define __PANTILT_SERVER_H__

#include <ros/ros.h>
#include <roscir/device/common/PanTilt.h>
#include <roscir/env/Config.h>
#include <reactive/erobot/ERobotCore.h>
#include <device/DeviceServerDefinition.h>
#include <reactive/mero/driver/MeroNeckDriver.h>
#include <reactive/util/motorlimit/RobotConfig.h>
#include <reactive/fri/rs232ch0/NeckRS232.h>
#include <reactive/fri/include/RT_FriNeck.h>

using namespace std;

using namespace reactive::erobot::core;

class CPanTiltServerProxy : public CPanTilt
{
private :
	CPanTilt* panTilt;
	CPanTilt* panTiltSimul;
	CPanTiltServerProxy();

public :

	virtual ~CPanTiltServerProxy();


	static CPanTilt* getInstance();

	int on();
	int off();
	int stop();
	int moveToHome( int speed );
	int moveToAbsolutePosition( double degreeLeftRight, double degreeUpDown, int speed );
	int moveToAbsolutePositionWithSpeed( double degreeLeftRight, double degreeUpDown, int speedLeftRight, int speedUpDown);
	int moveToRelativePosition( double degreeLeftRight, double degreeUpDown, int speed );
	int move2MotorSync( int motorID1, int motorSpeed1, int motorPosition1, int motorID2, int motorSpeed2, int motorPosition2 );
	int moveMotor( int motorID, int motorSpeed, int motorPosition );

	void getPosition(CPanTiltPosition& position);
	int setCompliance(int option);
	int moveToABSAll(int panAngle, int tiltAngle, int xtionAngle, int panSpeed, int tiltSpeed, int xtionSpeed);
	int moveXtionTilt(int xtionAngle, int xtionSpeed);
	int getXtionTiltAngle();
	void emergencyStop();
	void emergencyRelease();
	void detectingError(short errorCode[3]);
};

class CPanTiltServerMock : public CPanTilt
{

private:
	bool isEmergency;
public :
	CPanTiltServerMock();
	virtual ~CPanTiltServerMock();

	int on();
	int off();
	int stop();
	int moveToHome( int speed );
	int moveToAbsolutePosition( double degreeLeftRight, double degreeUpDown, int speed );
	int moveToAbsolutePositionWithSpeed( double degreeLeftRight, double degreeUpDown, int speedLeftRight, int speedUpDown);
	int moveToRelativePosition( double degreeLeftRight, double degreeUpDown, int speed );
	int move2MotorSync( int motorID1, int motorSpeed1, int motorPosition1, int motorID2, int motorSpeed2, int motorPosition2 );
	int moveMotor( int motorID, int motorSpeed, int motorPosition );
	void getPosition(CPanTiltPosition& position);
	int setCompliance(int option);
	int moveToABSAll(int panAngle, int tiltAngle, int xtionAngle, int panSpeed, int tiltSpeed, int xtionSpeed) { return -1;}
	int moveXtionTilt(int xtionAngle, int xtionSpeed) {return -1;}
	int getXtionTiltAngle() {return -1;}
	void emergencyStop();
	void emergencyRelease();
	void detectingError(short errorCode[3]);
};

class CPanTiltERobot : public CPanTilt
{
private:
	ERobotCore* core;
	bool isEmergency;
public :
	CPanTiltERobot();
	virtual ~CPanTiltERobot();

	int on();
	int off();
	int stop();
	int moveToHome( int speed );
	int moveToAbsolutePosition( double degreeLeftRight, double degreeUpDown, int speed );
	int moveToAbsolutePositionWithSpeed( double degreeLeftRight, double degreeUpDown, int speedLeftRight, int speedUpDown);
	int moveToRelativePosition( double degreeLeftRight, double degreeUpDown, int speed );
	int move2MotorSync( int motorID1, int motorSpeed1, int motorPosition1, int motorID2, int motorSpeed2, int motorPosition2 );
	int moveMotor( int motorID, int motorSpeed, int motorPosition );
	void getPosition(CPanTiltPosition& position);
	int setCompliance(int option);
	int moveToABSAll(int panAngle, int tiltAngle, int xtionAngle, int panSpeed, int tiltSpeed, int xtionSpeed);
	int moveXtionTilt(int xtionAngle, int xtionSpeed);
	int getXtionTiltAngle();
	void emergencyStop();
	void emergencyRelease();
	void detectingError(short errorCode[3]);
};

class CPanTiltMero : public CPanTilt
{
private:
	MeroNeckDriver* rs485;

	static  double MIN_PAN_DEGREE;
	static  double MAX_PAN_DEGREE;

	static  double MIN_TILT_DEGREE;
	static  double MAX_TILT_DEGREE;

	static  int MIN_PANTILT_VELOCITY;
	static  int MAX_PANTILT_VELOCITY;

	CRobotConfig* robotConfig;
	map<string, double> MEROLimits;
	void setLimits();

public :
	CPanTiltMero();
	virtual ~CPanTiltMero();

	static CPanTiltMero* getInstance();

	int on();
	int off();
	int stop();
	int moveToHome( int speed );
	int moveToAbsolutePosition( double degreeLeftRight, double degreeUpDown, int speed );
	int moveToAbsolutePositionWithSpeed( double degreeLeftRight, double degreeUpDown, int speedLeftRight, int speedUpDown);
	int moveToRelativePosition( double degreeLeftRight, double degreeUpDown, int speed );
	int move2MotorSync( int motorID1, int motorSpeed1, int motorPosition1, int motorID2, int motorSpeed2, int motorPosition2 );
	int moveMotor( int motorID, int motorSpeed, int motorPosition );
	void getPosition(CPanTiltPosition& position);
	int setCompliance(int option);
	int moveToABSAll(int panAngle, int tiltAngle, int xtionAngle, int panSpeed, int tiltSpeed, int xtionSpeed);
	int moveXtionTilt(int xtionAngle, int xtionSpeed) {return -1;}
	int getXtionTiltAngle() {return -1;}
	void emergencyStop();
	void emergencyRelease();
	void detectingError(short errorCode[3]);
};

class CPanTiltFRIRTAI : public CPanTilt
{

private:
	CPanTiltPosition FRIPanTiltPos;

	static  double MIN_PAN_DEGREE;
	static  double MAX_PAN_DEGREE;

	static  double MIN_TILT_DEGREE;
	static  double MAX_TILT_DEGREE;

	static  double MIN_PANTILT_VELOCITY;
	static  double MAX_PANTILT_VELOCITY;

	CPanTiltPosition* currentPanTiltPosition;
	NeckRS232* neckrs232;

	int mFriNeckCmdfifo,mFriNeckReportfifo;
	struct Fri_Neck_Cmdfifo FriNeckCmdfifo;
	struct Fri_Neck_Reportfifo FriNeckReportfifo;

	CRobotConfig* robotConfig;
	map<string, double> FRILimits;
	void setLimits();

	int m_neckType;
	int m_encoderEnable;

public :
	CPanTiltFRIRTAI();
	~CPanTiltFRIRTAI();
	static CPanTiltFRIRTAI* getInstance();

	int on();
	int off();
	int stop();
	int moveToHome( int speed );
	int moveToAbsolutePosition( double degreeLeftRight, double degreeUpDown, int speed );
	int moveToAbsolutePositionWithSpeed( double degreeLeftRight, double degreeUpDown, int speedLeftRight, int speedUpDown);
	int moveToRelativePosition( double degreeLeftRight, double degreeUpDown, int speed );
	int move2MotorSync( int motorID1, int motorSpeed1, int motorPosition1, int motorID2, int motorSpeed2, int motorPosition2 );
	int moveMotor( int motorID, int motorSpeed, int motorPosition );
	void getPosition(CPanTiltPosition& position);
	int setCompliance(int option);
	int moveToABSAll(int panAngle, int tiltAngle, int xtionAngle, int panSpeed, int tiltSpeed, int xtionSpeed);
	int moveXtionTilt(int xtionAngle, int xtionSpeed);
	int getXtionTiltAngle();
	void emergencyStop();
	void emergencyRelease();
	void detectingError(short errorCode[3]);

};


#endif /* __PANTILT_SERVER_H__ */
