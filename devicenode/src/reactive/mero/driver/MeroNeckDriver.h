#pragma once
#include "RS232.h"
#include <map>
#include <vector>
//#include <process.h>
//#include <roscir/env/Config.h>
#include <boost/thread/thread.hpp>

#include <ros/ros.h>
#include <pthread.h>

#include <queue>
#include "MotorDefinition.h"

#define MOTOR_PULSE_PER_DEGREE 612.36228
#define MOTOR_PULSE_PER_DEGREE_LIMIT 30.0



class MeroNeckDriver
{
public:
	MeroNeckDriver(void);
	~MeroNeckDriver(void);
	
	static MeroNeckDriver* getInstance();
	
	//Timer 
//	UINT m_nTimerID;
//	static void CALLBACK TimeProc(UINT m_nTimerID, UINT uiMsg, DWORD dwUser, DWORD dw1, DWORD d2);
	
	//pantilt rollbend queue
	static double S_Pantilt_leftRightDegree;
	static double S_Pantilt_upDownDegree;
	static int S_Pantilt_speed;
	static double S_Rollbend_leftRightDegree;
	static double S_Rollbend_upDownDegree;
	static int S_Rollbend_speed;
	static queue<CH1_CH2_Degree> m_pantilt_q;
	static queue<CH1_CH2_Degree> m_rollbend_q;

	void serialClear();

	Encoder Board1Enc();
	void Board1Enc(Encoder val);
	Encoder Board2Enc();
	void Board2Enc(Encoder val);

	bool motorOn(MOTOR::BOARD_ID ID);
	bool motorOff(MOTOR::BOARD_ID ID);
	bool initPantiltRollBendMotors();
	bool setMotorSpeed(MOTOR::BOARD_ID id, int speed);
	bool setCompliance(int val);
	bool getDegrees( MOTOR::BOARD_ID ID, double &leftRightDegree, double &upDownDegree );
	bool commandDegreeChk(MOTOR::BOARD_ID ID, double &leftRightDegree, double &upDownDegree );
	bool contorlPeriodmoveAbsMotor(MOTOR::BOARD_ID id, double leftRightDegree, double upDownDegree,  int speed );
	
	void errorCheck(MOTOR::BOARD_ID ID, short* errorCode);


private:

	RS232 serial;

	static const int BAUD_RATE_FACE	= 115200;
	static const int READ_BUFFER_SIZE = 30;

//	CRITICAL_SECTION motor_command_cs;
	static pthread_mutex_t __motor_command_mutex;

	//CRITICAL_SECTION pantilt_q_cs, rollbend_q_cs;

	Encoder board1Enc, board2Enc;
	short m_ERROR_Code[3];
	bool __IS_EXIST_CONTROL_THREAD;

	bool writeToMotor(MOTOR::BOARD_ID ID, string command);
	string writeToMotorwithAck(MOTOR::BOARD_ID ID, string command);
	string readFromMotor();

	string motorBoardValueReset(MOTOR::BOARD_ID ID, Encoder& encoder);
	string motorBoardValueReset(MOTOR::BOARD_ID ID);

	void moveMotors(MOTOR::BOARD_ID id, MOTOR::MOTOR_CH ch, double degree );
	void moveOneMotor(MOTOR::BOARD_ID id, MOTOR::MOTOR_CH ch, double degree );
	void moveOneMotorInit(MOTOR::BOARD_ID id, MOTOR::MOTOR_CH ch);

	void chkMotorLimitNeck(MOTOR::BOARD_ID ID);
	void chkMotorLimitNeckRollBend(MOTOR::BOARD_ID ID);
	void chkMotorLimitNeckSecond(MOTOR::BOARD_ID ID);

	MOTOR::OP_SENSOR checkOpticalSensor(MOTOR::BOARD_ID ID, MOTOR::MOTOR_CH ch);
	string checkOpticalMultiSensor(MOTOR::BOARD_ID ID);
	MOTOR::OP_SENSOR decideStrOpticalSensorValue(string sensorVal);
	string parseSensorpVal(string sensorVal, MOTOR::MOTOR_CH ch);
	bool encoderValueChk(MOTOR::BOARD_ID ID, Encoder& values);
	bool compareEncoderValue( Encoder &preEncoder, Encoder &curEncoder);

	string motorIDToString( MOTOR::BOARD_ID ID );
	string intToString( int intNumber );
	int StringToInt( string str );

	boost::thread		m_PanTiltRollBend_Thread;
	
	void runControlPeriod();
	void moveBoardMotorinThread( MOTOR::BOARD_ID id,  queue<CH1_CH2_Degree>& boardQueue, Encoder &boardEncoder, double& ch1Degree, double& ch2Degree, int& speed );
	int moveAbsfunc( bool period, MOTOR::BOARD_ID id, Encoder& motorEncoder, double CH1Degree, double CH2Degree);
	int contorlPeriodMoveAbsfunc(bool isPeriod, MOTOR::BOARD_ID id, Encoder& motorEncoder, double leftRightDegree, double upDownDegree);
	void pushQueue( MOTOR::BOARD_ID id, CH1_CH2_Degree tmpLR_UD_Degree );
	void startControlPeriodThread();
	string GetBinaryStringFromHexString (string sHex);
	void initErrorCode(short* errorCode);
};

using namespace MOTOR;
