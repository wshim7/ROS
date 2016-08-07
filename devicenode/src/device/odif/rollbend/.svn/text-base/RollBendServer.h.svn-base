/*
 * RollBendServer.h
 *
 *  Created on: 2014. 1. 14.
 *      Author: msyoo
 */

#ifndef __ROLLBENDSERVER_H__
#define __ROLLBENDSERVER_H__

#include <ros/ros.h>
#include <roscir/device/common/RollBend.h>
#include <roscir/env/Config.h>
#include <device/DeviceServerDefinition.h>
#include <reactive/mero/driver/MeroNeckDriver.h>
#include <reactive/fri/include/RT_FriNeck.h>
#include <reactive/fri/rs232ch0/NeckRS232.h>
#include <reactive/mero/MeroDefinition.h>
#include <reactive/util/motorlimit/RobotConfig.h>

using namespace std;

class CRollBendServerProxy : public CRollBend
{
private :
	CRollBend* RollBend;
	CRollBendServerProxy();

public :
	virtual ~CRollBendServerProxy();
	static CRollBend* getInstance();

    int on();
    int off();
    int stop();
    int moveToHome( int speed );
    int moveToAbsolutePosition( double degreeRoll, double degreeBend, int speed );
    int moveToAbsolutePositionWithSpeed( double degreeRoll, double degreeBend, int speedRoll, int speedBend );
    int moveToRelativePosition( double degreeRoll, double degreeBend, int speed );
	int move2MotorSync( int motorID1, int motorSpeed1, int motorPosition1, int motorID2, int motorSpeed2, int motorPosition2 );
	int moveMotor( int motorID, int motorSpeed, int motorPosition );
    void getPosition(CRollBendPosition& position);
    void detectingError(short errorCode[3]);
};

class CRollBendServerMock : public CRollBend
{
private :
	CRollBend* RollBend;

public :
	CRollBendServerMock();
	virtual ~CRollBendServerMock();

    int on();
    int off();
    int stop();
    int moveToHome( int speed );
    int moveToAbsolutePosition( double degreeRoll, double degreeBend, int speed );
    int moveToAbsolutePositionWithSpeed( double degreeRoll, double degreeBend, int speedRoll, int speedBend );
    int moveToRelativePosition( double degreeRoll, double degreeBend, int speed );
	int move2MotorSync( int motorID1, int motorSpeed1, int motorPosition1, int motorID2, int motorSpeed2, int motorPosition2 );
	int moveMotor( int motorID, int motorSpeed, int motorPosition );
    void getPosition(CRollBendPosition& position);
    void detectingError(short errorCode[3]);
};


class CRollBendMERO : public CRollBend
{

private :
	static int MIN_ROLLBEND_VELOCITY;// = 0;
	static int MAX_ROLLBEND_VELOCITY;// = 100;

	static double MIN_ROLL_DEGREE;// = -40.0;	// CCW
	static double MAX_ROLL_DEGREE;// = 40.0;		// CW

	static double MIN_BEND_DEGREE;// = -45.0;	// DOWN
	static double MAX_BEND_DEGREE;// = 40.0;		// UP

	MeroNeckDriver* rs485;
	CRollBendPosition MERORollBendPos;

	CRobotConfig* robotConfig;
	map<string, double> MEROLimits;
	void setLimits();

public :
	CRollBendMERO();
	virtual ~CRollBendMERO();

	static CRollBendMERO* getInstance();

	int on();
	int off();
	int stop();
	int moveToHome( int speed );
	int moveToAbsolutePosition( double degreeRoll, double degreeBend, int speed );
	int moveToAbsolutePositionWithSpeed( double degreeRoll, double degreeBend, int speedRoll, int speedBend );
	int moveToRelativePosition( double degreeRoll, double degreeBend, int speed );
	int move2MotorSync( int motorID1, int motorSpeed1, int motorPosition1, int motorID2, int motorSpeed2, int motorPosition2 );
	int moveMotor( int motorID, int motorSpeed, int motorPosition );
	void getPosition(CRollBendPosition& position);
	void detectingError(short errorCode[3]);
};

class CRollBendFRIRTAI : public CRollBend
{

private :

	CRollBendPosition FRIRollBendPos;
	// Roll Offset.
	static double ROLL_OFFSET;

	// Bend Offset.
	static double BEND_OFFSET;

	static int MIN_ROLLBEND_VELOCITY;// = 0;
	static int MAX_ROLLBEND_VELOCITY;// = 100;

	static double MIN_ROLL_DEGREE;// = -40.0;	// CCW
	static double MAX_ROLL_DEGREE;// = 40.0;		// CW

	static double MIN_BEND_DEGREE;// = -45.0;	// DOWN
	static double MAX_BEND_DEGREE;//

	NeckRS232* neckrs232;

	int mFriNeckCmdfifo,mFriNeckReportfifo;
	struct Fri_Neck_Cmdfifo FriNeckCmdfifo;
	struct Fri_Neck_Reportfifo FriNeckReportfifo;

	// Send a RT command and return status report..
	int sendRTCommand( struct RB_CMD commandStruct );

	CRobotConfig* robotConfig;
	map<string, double> FRILimits;
	void setLimits();

	int m_neckType;
	int m_encoderEnable;

public :
	~CRollBendFRIRTAI();
	CRollBendFRIRTAI();
	static CRollBendFRIRTAI* getInstance();

	int on();
	int off();
	int stop();
	int moveToHome( int speed );
	int moveToAbsolutePosition( double degreeRoll, double degreeBend, int speed );
	int moveToAbsolutePositionWithSpeed( double degreeRoll, double degreeBend, int speedRoll, int speedBend ){ return 0;}
	int moveToRelativePosition( double degreeRoll, double degreeBend, int speed );
	int move2MotorSync( int motorID1, int motorSpeed1, int motorPosition1, int motorID2, int motorSpeed2, int motorPosition2 );
	int moveMotor( int motorID, int motorSpeed, int motorPosition );
	void getPosition(CRollBendPosition& position);
	void detectingError(short errorCode[3]);
};



#endif /*__ ROLLBENDSERVER_H__ */


