#include "MeroNeckDriver.h"
#include <roscir/env/Config.h>
#include <sstream>
#include <algorithm>
#include <time.h>
//#include <conio.h>
#include <math.h>
#define PI 3.1415926

pthread_mutex_t MeroNeckDriver::__motor_command_mutex = PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP;

double MeroNeckDriver::S_Pantilt_leftRightDegree = 0.0;
double MeroNeckDriver::S_Pantilt_upDownDegree = 0.0;
int MeroNeckDriver::S_Pantilt_speed = 100;

double MeroNeckDriver::S_Rollbend_leftRightDegree = 0.0;
double MeroNeckDriver::S_Rollbend_upDownDegree = 0.0;
int MeroNeckDriver::S_Rollbend_speed = 100;

queue<CH1_CH2_Degree> MeroNeckDriver::m_pantilt_q;
queue<CH1_CH2_Degree> MeroNeckDriver::m_rollbend_q;


MeroNeckDriver::MeroNeckDriver(void)
{
//	m_nTimerID = timeSetEvent(1,0,TimeProc,(DWORD)0, TIME_PERIODIC);
	__IS_EXIST_CONTROL_THREAD = false;

	string comPort = CConfig::getInstance()->getParamValue("MERO_NECK_COM_PORT");
	if(comPort.empty()){
		comPort = "COM3";
	}
	
	cout<<"[Info] Neck Com Port: " << comPort << endl;
	
	serial.setup(comPort, MeroNeckDriver::BAUD_RATE_FACE);
	serial.flush();

//	InitializeCriticalSection(&motor_command_cs);
	//InitializeCriticalSection(&pantilt_q_cs);
	//InitializeCriticalSection(&rollbend_q_cs);
	
}

MeroNeckDriver::~MeroNeckDriver(void)
{
//	timeKillEvent(m_nTimerID);
}

MeroNeckDriver* MeroNeckDriver::getInstance()
{
	static MeroNeckDriver thisInstance;
	cout << "[CRS485.getInstance] : Create Sole Instance(CRS485).." << endl;
	return &thisInstance;
}

bool MeroNeckDriver::writeToMotor( MOTOR::BOARD_ID ID, string command )
{
//	EnterCriticalSection(&motor_command_cs);
	pthread_mutex_lock(&__motor_command_mutex);

	bool result = false;
	string sID = motorIDToString(ID);
	string sCommandCom =  command + "!";
	string sIDCommand = sID + sCommandCom; 
	char id  = (char) ID;
	char* chIDCommand = new char[sIDCommand.length()+1];
	sprintf(chIDCommand,"%c%s", id , sCommandCom.c_str());

	int res = serial.writeBytes((unsigned char*)chIDCommand,sIDCommand.length());

	if(chIDCommand != NULL){
		chIDCommand =NULL;
		delete []chIDCommand;
	}

	if(res == sIDCommand.length()){
		result = true;
	}else{
		result = false;
	}
	//Sleep(2);//Serial communication Time IMPORTANT!!!!
	ros::Duration(0.002).sleep();
//	LeaveCriticalSection(&motor_command_cs);
	pthread_mutex_unlock(&__motor_command_mutex);
	return result;
	
}


std::string MeroNeckDriver::writeToMotorwithAck( MOTOR::BOARD_ID ID, string command )
{
//	EnterCriticalSection(&motor_command_cs);
	pthread_mutex_lock(&__motor_command_mutex);

	clock_t start, end;
	string motorReadResult = "";
	string sID = motorIDToString(ID);
	string sCommandCom =  command + ";";
	string sIDCommand = sID + sCommandCom;
	char id  = (char) ID;
	char* chIDCommand = new char[sIDCommand.length()+1];
	sprintf(chIDCommand,"%c%s", id , sCommandCom.c_str());

	start = clock();
	int res = serial.writeBytes((unsigned char*)chIDCommand,sIDCommand.length());

	if(chIDCommand != NULL){
		chIDCommand =NULL;
		delete []chIDCommand;
	}

	if(res == sIDCommand.length()){
		string commandQuery = sCommandCom.erase(2, sCommandCom.size());
		unsigned char chReadByteResult[256] = {0};
		 
		motorReadResult = readFromMotor();

		if(motorReadResult.size() > 0 ){
		}else{
			motorReadResult  = "";
		}

	}
//	LeaveCriticalSection(&motor_command_cs);
	pthread_mutex_unlock(&__motor_command_mutex);
	return motorReadResult;
}

Encoder MeroNeckDriver::Board1Enc()
{
	return board1Enc;
}

void MeroNeckDriver::Board1Enc(Encoder val)
{
	board1Enc = val;
}


Encoder MeroNeckDriver::Board2Enc()
{
	return board2Enc;
}


void MeroNeckDriver::Board2Enc(Encoder val)
{
	board2Enc = val;
}

std::string MeroNeckDriver::motorIDToString( MOTOR::BOARD_ID ID )
{
	stringstream ssID;
	int idi = ID;
	ssID << ID;
	return ssID.str();
}


std::string MeroNeckDriver::readFromMotor()
{
	const int readArraySize = 1;
	const int readReaultArraySize = 256;
	const int responseTimeout = 1000;

	int resultCommandLength = 0;

	unsigned char readByteArray[readArraySize] = {0};
	unsigned char readResultByteArray[readReaultArraySize] = {0};

	clock_t start;
	clock_t end, endRoof;

	start = clock();
	//printf("\nresultByteArray: ");
	while(true){
		int cntByte = serial.readBytes((unsigned char*)readByteArray,readArraySize);
		if(cntByte >0){
			if(readByteArray[0] == ';'){
				readResultByteArray[resultCommandLength] = readByteArray[0];
				//printf("%c\n", readByteArray[0]);
				resultCommandLength += cntByte;
				break;
			}

			readResultByteArray[resultCommandLength] = readByteArray[0];
			//printf("%c", readByteArray[0]);
			resultCommandLength += cntByte;
		}
		endRoof = clock();

		if((endRoof - start) > responseTimeout){
			break;
		}
	}

	end = clock();
	//cout << "Elapsed Time: " << end-start << endl;
	return string ((char*)readResultByteArray);
}


bool MeroNeckDriver::motorOn( MOTOR::BOARD_ID ID)
{
	string sID = motorIDToString(ID);
	string readByteResult = "";
	string PR_Command = "PR000" + sID;
	
	//Servo Error Reset
	readByteResult = writeToMotorwithAck(ID, PR_Command);
	//Sleep(100);
	ros::Duration(0.1).sleep();
	
	string PE_Command = "PE000"+ sID;
	string SM_Command = "SM0202";
	
	readByteResult = writeToMotorwithAck(ID, PE_Command);
	
	int res = readByteResult.size();

	if(res > 0){
		readByteResult = writeToMotorwithAck(ID, SM_Command);
		res = readByteResult.size();
		cout << "Motor [" << ID << "]" << "On OK!! "  <<readByteResult << endl;

		if(ID == FIRST){
			encoderValueChk(ID, board1Enc);
		}else if(ID == SECOND){
			encoderValueChk(ID, board2Enc);
		}

		return true;
	}else{
		return false;
	}
}

bool MeroNeckDriver::motorOff( MOTOR::BOARD_ID ID )
{
	string sID = motorIDToString(ID);
	string PE_Command = "PD000"+ sID;

	string readByteResult = "";
	readByteResult = writeToMotorwithAck(ID, PE_Command);

	int res = readByteResult.size();
	
	if(res > 0){
		return true;
	}else{
		return false;
	}
	
}



MOTOR::OP_SENSOR MeroNeckDriver::checkOpticalSensor( MOTOR::BOARD_ID ID, MOTOR::MOTOR_CH ch )
{
	OP_SENSOR opticalOnOff = SENSOR_ERROR;

	string opSensorResult = writeToMotorwithAck(ID, "QS?");
	
	if(opSensorResult == "" ){
		cout << "Optical Sensor ERROR" << endl;

		return SENSOR_ERROR;
	}

	string commandQuery = "";

	switch(ch){
		case CH1:
			commandQuery = opSensorResult.erase(0, 4);
			commandQuery.erase(1, commandQuery.size());
			if(commandQuery == "D"){
				opticalOnOff = SENSOR_ON;//ON;
			}else {
				opticalOnOff = SENSOR_OFF;//OFF;
			}
			break;

		case CH2:
			commandQuery = opSensorResult.erase(0, 3);
			commandQuery.erase(1, commandQuery.size());
			if(commandQuery == "E"){
				opticalOnOff = SENSOR_ON;//ON;
			}else {
				opticalOnOff = SENSOR_OFF;//OFF;
			}
			break;
	};

	if(commandQuery == "D" || commandQuery == "E" || commandQuery == "F"){
		cout << "Optical commandQuery: " <<  commandQuery << endl;
	}else{
		opticalOnOff = SENSOR_ERROR;//;
	}
	return opticalOnOff;
}


string MeroNeckDriver::checkOpticalMultiSensor( MOTOR::BOARD_ID ID )
{
	string opSensorResult = writeToMotorwithAck(ID, "QS?");
	if(opSensorResult == ""){
		return "";
	}
	
	string commandQuery = "";

	commandQuery = opSensorResult.erase(0, 3);
	commandQuery.erase(2, commandQuery.size());
	return commandQuery;
}


void MeroNeckDriver::serialClear()
{
	serial.flush();
}

void MeroNeckDriver::moveMotors( MOTOR::BOARD_ID id, MOTOR::MOTOR_CH ch, double degree )
{
	string strResult = "";
	string PA_command = "";

	double degreeToPulse = MOTOR_PULSE_PER_DEGREE * degree;
	double degreeToPulseDouble = MOTOR_PULSE_PER_DEGREE * degree * 2;

	switch(id){
		case FIRST:
			switch(ch){

			case SYNC_CH:
				board1Enc.CH1VALUE += degreeToPulseDouble;
				board1Enc.CH2VALUE += degreeToPulseDouble;
				PA_command = "PA"+intToString((int)board1Enc.CH1VALUE)+","+intToString((int)board1Enc.CH2VALUE);
				writeToMotorwithAck(id,PA_command);
				break;
			case ASYNC_CH:
				board1Enc.CH1VALUE += degreeToPulse;
				board1Enc.CH2VALUE -= degreeToPulse;

				PA_command = "PA"+intToString((int)board1Enc.CH1VALUE)+","+intToString((int)board1Enc.CH2VALUE);
				writeToMotorwithAck(id,PA_command);
				break;
			case INIT_POS:
				board1Enc.CH1VALUE = 5000000.0;
				board1Enc.CH2VALUE = 5000000.0;
				PA_command = "PA"+intToString((int)board1Enc.CH1VALUE)+","+intToString((int)board1Enc.CH2VALUE);
				writeToMotorwithAck(id,PA_command);
				break;

			};
			break;
		case SECOND:
			switch(ch){

			case SYNC_CH:
				board2Enc.CH1VALUE += degreeToPulseDouble;
				board2Enc.CH2VALUE += degreeToPulseDouble;

				PA_command = "PA"+intToString((int)board2Enc.CH1VALUE)+","+intToString((int)board2Enc.CH2VALUE);
				writeToMotorwithAck(id,PA_command);
				break;
			case ASYNC_CH:
				board2Enc.CH1VALUE += degreeToPulse;
				board2Enc.CH2VALUE -= degreeToPulse;

				PA_command = "PA"+intToString((int)board2Enc.CH1VALUE)+","+intToString((int)board2Enc.CH2VALUE);
				writeToMotorwithAck(id,PA_command);
				break;
			case INIT_POS:
				board2Enc.CH1VALUE = 5000000.0;
				board2Enc.CH2VALUE = 5000000.0;

				PA_command = "PA"+intToString((int)board2Enc.CH1VALUE)+","+intToString((int)board2Enc.CH2VALUE);
				writeToMotorwithAck(id,PA_command);
				break;

			};
			break;
	};

}


bool MeroNeckDriver::encoderValueChk( MOTOR::BOARD_ID ID, Encoder& values )
{
	bool res = false;

	do{
		string resultQP = writeToMotorwithAck(ID, "QP");

		if(resultQP.size() >0){

			resultQP.erase(0,3);

			string ch1Value = resultQP.substr(0, resultQP.find(","));
			string ch2Value = resultQP.substr(resultQP.find(",")+1, resultQP.find(";")-resultQP.find(",")-1);

			ch1Value.insert(0,"0x");
			ch2Value.insert(0,"0x");

			char * stop1;
			char * stop2;

			long ch1IntVal =  strtol(ch1Value.c_str(), &stop1, 16);
			long ch2IntVal =  strtol(ch2Value.c_str(), &stop2, 16);

			values.CH1VALUE = ch1IntVal;
			values.CH2VALUE = ch2IntVal;

			res = true;
		}else {
			res = false;
		}

	}while(!res);
	return res;
}

int MeroNeckDriver::StringToInt( string str )
{
	return atoi(str.c_str());
}

std::string MeroNeckDriver::intToString( int intNumber )
{
	stringstream ssID;
	ssID << intNumber;
	return ssID.str();
}

std::string MeroNeckDriver::motorBoardValueReset( MOTOR::BOARD_ID ID, Encoder& encoder )
{
	encoder.CH1VALUE = 5000000.0;
	encoder.CH2VALUE = 5000000.0;
	return writeToMotorwithAck(ID, "QEA55A");
}
std::string MeroNeckDriver::motorBoardValueReset( MOTOR::BOARD_ID ID)
{
	return writeToMotorwithAck(ID, "QEA55A");
}

MOTOR::OP_SENSOR MeroNeckDriver::decideStrOpticalSensorValue( string sensorVal )
{
	MOTOR::OP_SENSOR valueSen = SENSOR_ERROR;
	if(sensorVal == "D" || sensorVal == "E"){
		valueSen =  SENSOR_ON;
	}else if(sensorVal == "F"){
		valueSen =  SENSOR_OFF;
	}else{
		valueSen = SENSOR_ERROR;
	}

	return valueSen;
}

string MeroNeckDriver::parseSensorpVal( string sensorVal, MOTOR::MOTOR_CH ch )
{
	string resultOptical = sensorVal;

	string strResult;
	if(ch == CH1){
		strResult = resultOptical.erase(0, 1);
	}else if(ch == CH2){
		strResult = resultOptical.erase(1,resultOptical.size());
	}
	
	return strResult;
}


void MeroNeckDriver::chkMotorLimitNeck( MOTOR::BOARD_ID ID)
{
	Encoder tmpEncoder;
	Encoder curEncoder;
	Encoder preEncoder;
	long ch1EncValue = 5000000;
	long ch2EncValue = 5000000;
	bool setFlag_CH1 = false;
	bool setFlag_CH2 = false;

	setCompliance(250);
	//Sleep(100);
	ros::Duration(0.1).sleep();
	setMotorSpeed(FIRST,100);
	setMotorSpeed(SECOND,100);
	//Sleep(100);
	ros::Duration(0.1).sleep();
	string resultOptical = checkOpticalMultiSensor(ID);

	if(resultOptical == "")
		return;

	MOTOR::OP_SENSOR ch1ChkFlag
		= decideStrOpticalSensorValue(parseSensorpVal( resultOptical,CH1));

	string resultEnc = ""; 
	//Sleep(100);
	ros::Duration(0.1).sleep();
	encoderValueChk(ID, preEncoder);
	//Sleep(100);
	ros::Duration(0.1).sleep();
	for(int i =0; i<= 80; i++){
		moveMotors(ID,ASYNC_CH, 1.0);
		//Sleep(20);
		ros::Duration(0.02).sleep();

		encoderValueChk(ID, curEncoder);
		if(compareEncoderValue(preEncoder, curEncoder)){
			break;
		}
	}

	//Sleep(100);
	ros::Duration(0.1).sleep();

	for(int i =0; i<= 55; i++){

		moveMotors(ID,ASYNC_CH, -1.0);
		//Sleep(20);
		ros::Duration(0.02).sleep();
	} 

	//Sleep(100);
	ros::Duration(0.1).sleep();

	for(int i =0; i<= 270; i++){
		moveMotors(ID,SYNC_CH,-1.0);
		//Sleep(20);
		ros::Duration(0.02).sleep();

		encoderValueChk(ID, curEncoder);
		if(compareEncoderValue(preEncoder, curEncoder)){
			break;
		}
	}

	//Sleep(500);
	ros::Duration(0.5).sleep();

	encoderValueChk(ID, preEncoder);
	//Sleep(500);
	ros::Duration(0.5).sleep();

	for(int i =0; i<= 270; i++){

		moveMotors(ID,SYNC_CH, 0.5);
		//Sleep(20);
		ros::Duration(0.02).sleep();

		resultOptical = checkOpticalMultiSensor(ID);

		if(resultOptical == "")
			return ;

		ch1ChkFlag = decideStrOpticalSensorValue(parseSensorpVal( resultOptical,CH1));

		if (ch1ChkFlag == SENSOR_ON){
			break;
		}
	}

	//Sleep(100);
	ros::Duration(0.1).sleep();
	moveOneMotorInit(ID, INIT_POS);

}

void MeroNeckDriver::chkMotorLimitNeckRollBend( MOTOR::BOARD_ID ID)
{
	Encoder tmpEncoder;
	Encoder startEncoder;
	Encoder endEncoder;
	Encoder curEncoder;
	Encoder preEncoder;
	long ch1EncValue = 5000000;
	long ch2EncValue = 5000000;

	bool setFlag_CH1 = false;
	bool setFlag_CH2 = false;

	int tempFinishDegree = 0;

	string resultOptical = checkOpticalMultiSensor(ID);
	if(resultOptical == "")
		return;

	MOTOR::OP_SENSOR ch1ChkFlag
		= decideStrOpticalSensorValue(parseSensorpVal( resultOptical,CH1));
	MOTOR::OP_SENSOR ch2ChkFlag 
		= decideStrOpticalSensorValue(parseSensorpVal(resultOptical,CH2));
	string resultEnc = ""; 

	double startTMP = 0;
	double endTMP = 0;

	moveMotors(ID,ASYNC_CH,-2.5);
	ros::Duration(0.5).sleep();

	encoderValueChk(ID, preEncoder);
	Board2Enc(preEncoder);
	//Sleep(600);
	ros::Duration(0.5).sleep();

	for(int i =0; i<= 80; i++){
		moveMotors(ID,ASYNC_CH,-1.0);
		//Sleep(40);
		ros::Duration(0.04).sleep();

		encoderValueChk(ID, curEncoder);

		//Sleep(2);
		ros::Duration(0.002).sleep();
		if(compareEncoderValue(preEncoder, curEncoder)){
			break;
		}

	}

	for(int i =0; i<= 55; i++){
		moveMotors(ID,ASYNC_CH,1.0);
		//Sleep(20);
		ros::Duration(0.04).sleep();
	} 

	//Sleep(500);
	ros::Duration(0.5).sleep();

	encoderValueChk(ID, preEncoder);

	//Sleep(500);
	ros::Duration(0.5).sleep();
	for(int i =0; i<= 270; i++){
		moveMotors(ID,SYNC_CH, -1.0);
		//Sleep(20);
		ros::Duration(0.025).sleep();

		encoderValueChk(ID, curEncoder);
		if(compareEncoderValue(preEncoder, curEncoder)){
			break;
		}

	}

	//Sleep(500);
	ros::Duration(0.5).sleep();
	for(int i =0; i<= 280; i++){
		moveMotors(ID, SYNC_CH, 0.5);
		//Sleep(20);
		ros::Duration(0.02).sleep();
		resultOptical = checkOpticalMultiSensor(ID);

		if(resultOptical == "")
			return ;

		ch1ChkFlag
			= decideStrOpticalSensorValue(parseSensorpVal( resultOptical,CH1));


		if (ch1ChkFlag == SENSOR_ON){
			break;
		}

	}
	//Sleep(500);
	ros::Duration(0.5).sleep();
	for(int i =0; i<= 280; i++){
		moveMotors(ID,ASYNC_CH, 0.5);
		//Sleep(20);
		ros::Duration(0.02).sleep();

		resultOptical = checkOpticalMultiSensor(ID);

		if(resultOptical == "")
			return ;

		ch2ChkFlag
			= decideStrOpticalSensorValue(parseSensorpVal( resultOptical,CH2));


		if (ch2ChkFlag == SENSOR_ON){
			break;
		}
	}

	moveMotors(ID,SYNC_CH, -2.0);
	ros::Duration(0.4).sleep();
	moveOneMotorInit(ID, INIT_POS);

}


void MeroNeckDriver::moveOneMotor( MOTOR::BOARD_ID id, MOTOR::MOTOR_CH ch, double degree )
{
	string strResult = "";
	string PA_command = "";

	double degreeToPulse = MOTOR_PULSE_PER_DEGREE * degree;
	double degreeToPulseDouble = MOTOR_PULSE_PER_DEGREE * degree * 2;

	switch(id){
		case FIRST:
			switch(ch){
				case CH1:
					board1Enc.CH1VALUE += degreeToPulseDouble;
					PA_command = "PA"+intToString((int)board1Enc.CH1VALUE)+","+intToString((int)board1Enc.CH2VALUE);
					writeToMotorwithAck(id,PA_command);
					break;
				case CH2:
					board1Enc.CH2VALUE += degreeToPulseDouble;
					PA_command = "PA"+intToString((int)board1Enc.CH1VALUE)+","+intToString((int)board1Enc.CH2VALUE);
					writeToMotorwithAck(id,PA_command);
					break;
			};

			break;
		case SECOND:
			switch(ch){
				case CH1:
					board2Enc.CH1VALUE += degreeToPulseDouble;
					PA_command = "PA"+intToString((int)board2Enc.CH1VALUE)+","+intToString((int)board2Enc.CH2VALUE);
					writeToMotorwithAck(id,PA_command);
					break;
				case CH2:
					board2Enc.CH2VALUE += degreeToPulseDouble;
					PA_command = "PA"+intToString((int)board2Enc.CH1VALUE)+","+intToString((int)board2Enc.CH2VALUE);
					writeToMotorwithAck(id,PA_command);
					break;
			};

			break;
	};
}


void MeroNeckDriver::moveOneMotorInit( MOTOR::BOARD_ID id, MOTOR::MOTOR_CH ch )
{
	string strResult = "";
	string PA_command = "";

	switch(id){
		case FIRST:
			switch(ch){
				case CH1:
					board1Enc.CH1VALUE = 5000000.0;
					PA_command = "PA"+intToString((int)board1Enc.CH1VALUE)+","+intToString((int)board1Enc.CH2VALUE);
					writeToMotorwithAck(id,PA_command);
					break;
				case CH2:
					board1Enc.CH2VALUE = 5000000.0;
					PA_command = "PA"+intToString((int)board1Enc.CH1VALUE)+","+intToString((int)board1Enc.CH2VALUE);
					writeToMotorwithAck(id,PA_command);
					break;
				case INIT_POS:
					board1Enc.CH1VALUE = 5000000.0;
					board1Enc.CH2VALUE = 5000000.0;
					PA_command = "PA"+intToString((int)board1Enc.CH1VALUE)+","+intToString((int)board1Enc.CH2VALUE);
					writeToMotorwithAck(id,PA_command);
					break;
			};
			break;

		case SECOND:
			switch(ch){
				case CH1:
					board2Enc.CH1VALUE = 5000000.0;
					PA_command = "PA"+intToString((int)board2Enc.CH1VALUE)+","+intToString((int)board2Enc.CH2VALUE);
					writeToMotorwithAck(id,PA_command);
					break;
				case CH2:
					board2Enc.CH2VALUE = 5000000.0;
					PA_command = "PA"+intToString((int)board2Enc.CH1VALUE)+","+intToString((int)board2Enc.CH2VALUE);
					writeToMotorwithAck(id,PA_command);
					break;
				case INIT_POS:
					board2Enc.CH1VALUE = 5000000.0;
					board2Enc.CH2VALUE = 5000000.0;
					PA_command = "PA"+intToString((int)board2Enc.CH1VALUE)+","+intToString((int)board2Enc.CH2VALUE);
					writeToMotorwithAck(id,PA_command);
					break;
			};
			break;
	};
}

bool MeroNeckDriver::compareEncoderValue( Encoder &preEncoder, Encoder &curEncoder)
{
	bool tempDiff = false;
	long diffValueCH1  = abs(preEncoder.CH1VALUE - curEncoder.CH1VALUE);
	long diffValueCH2  = abs(preEncoder.CH2VALUE - curEncoder.CH2VALUE);

	double limit_pulse = MOTOR_PULSE_PER_DEGREE_LIMIT;

	if(diffValueCH1 < limit_pulse || diffValueCH2 < limit_pulse){
		tempDiff = true;
	}	

	preEncoder = curEncoder;
	
	return tempDiff;
}

bool MeroNeckDriver::setCompliance(int val )
{
	//EnterCriticalSection(&motor_command_cs);
	if( val >=1 && val <=6){
		val = 250;
	}else if( val == 7 ){
		val =500;
	}
	setMotorSpeed(FIRST, 100);
	//Sleep(10);
	ros::Duration(0.01).sleep();
	setMotorSpeed(SECOND, 100);
	//Sleep(10);
	ros::Duration(0.01).sleep();

	bool res = false;
	string strResult ="";
	string strSs = intToString(val);
	string strSsCommand = "Ss" + strSs + "," + strSs;

	strResult = writeToMotorwithAck(FIRST,strSsCommand);
	//Sleep(10);
	ros::Duration(0.01).sleep();
	strResult = writeToMotorwithAck(SECOND,strSsCommand);
	//Sleep(10);
	ros::Duration(0.01).sleep();

	if(strResult.size() > 0){
		res = true;
	}
	//LeaveCriticalSection(&motor_command_cs);
	return res;
}

bool MeroNeckDriver::setMotorSpeed(MOTOR::BOARD_ID id, int speed )
{
	string strMotorSpeed = MOTOR_MAPPING_RPM_SPEED[speed];
	string strSpeedCommand = "SS" + strMotorSpeed + "," + strMotorSpeed;
	return writeToMotor(id,strSpeedCommand);
}

bool MeroNeckDriver::getDegrees( MOTOR::BOARD_ID ID, double &leftRightDegree, double &upDownDegree )
{
	//EnterCriticalSection(&motor_command_cs);

	Encoder tempEnc;
	bool res = encoderValueChk(ID,tempEnc);

	double leftRightDegreeTmp, upDownDegreeTmp;
	double a, b, c, d, p, q;

	a = 2.0 * MOTOR_PULSE_PER_DEGREE;
	b = MOTOR_PULSE_PER_DEGREE;
	p = tempEnc.CH1VALUE - 5000000.0;

	c = 2.0 * MOTOR_PULSE_PER_DEGREE;
	d =  -MOTOR_PULSE_PER_DEGREE;
	q = tempEnc.CH2VALUE - 5000000.0;


	leftRightDegreeTmp = (d*p-b*q) / (a*d - b*c);

	upDownDegreeTmp = (a*q-c*p) / (a*d - b*c);

	if((a*d - b*c) == 0)
	{
		leftRightDegreeTmp = 0;
		upDownDegreeTmp = 0;
	}

	if(ID== FIRST){
		leftRightDegreeTmp = -leftRightDegreeTmp;
	}else if(ID== SECOND){
		upDownDegreeTmp = -upDownDegreeTmp;
	}

	leftRightDegree = leftRightDegreeTmp;
	upDownDegree = upDownDegreeTmp;

	//cout << "leftRightDegree: " << leftRightDegreeTmp << " upDownDegree: " <<upDownDegreeTmp<< endl;

	//LeaveCriticalSection(&motor_command_cs);
	return res;

}

void MeroNeckDriver::chkMotorLimitNeckSecond( MOTOR::BOARD_ID ID )
{
	bool setFlag_CH2 = false;

	string resultOptical = checkOpticalMultiSensor(ID);

	if(resultOptical == "")
		return;

	MOTOR::OP_SENSOR ch2ChkFlag 
		= decideStrOpticalSensorValue(parseSensorpVal(resultOptical,CH2));

	for(int i =0; i<= 280; i++){

		moveMotors(ID,ASYNC_CH, 0.5);
		//Sleep(20);
		ros::Duration(0.02).sleep();


		resultOptical = checkOpticalMultiSensor(ID);

		if(resultOptical == "")
			return ;

		setFlag_CH2 = decideStrOpticalSensorValue(parseSensorpVal( resultOptical,CH2));

		if (setFlag_CH2 == SENSOR_ON){
			break;
		}

	}

	moveOneMotorInit(ID, INIT_POS);
}

int MeroNeckDriver::contorlPeriodMoveAbsfunc(bool period, MOTOR::BOARD_ID id, Encoder& motorEncoder, double leftRightDegree, double upDownDegree)
{
	string strResult = "";
		string PA_command = "";

		bool resultMove = false;

		if(id == FIRST){
			leftRightDegree = -leftRightDegree;
		}else if(id == SECOND){
			upDownDegree = -upDownDegree;
		}

		double degreeToPulseDouble = MOTOR_PULSE_PER_DEGREE * leftRightDegree * 2 + 5000000.0; // pan
		double degreeToPulse = MOTOR_PULSE_PER_DEGREE * upDownDegree; // tilt

		double ch1_value = degreeToPulseDouble + degreeToPulse;
		double ch2_value = degreeToPulseDouble - degreeToPulse;

		//writeEncoder
		motorEncoder.CH1VALUE = ch1_value;
		motorEncoder.CH2VALUE = ch2_value;


		if(period){
			PA_command = "PP"+intToString((int)motorEncoder.CH1VALUE)+","+intToString((int)motorEncoder.CH2VALUE);

		}else{
			PA_command = "PA"+intToString((int)motorEncoder.CH1VALUE)+","+intToString((int)motorEncoder.CH2VALUE);
		}

		resultMove = writeToMotor(id,PA_command);
		//cout<< "writeToMotor Move: [" << id << "]" << "Command: " << PA_command << endl;
		return resultMove;
}

bool MeroNeckDriver::commandDegreeChk( MOTOR::BOARD_ID ID, double &leftRightDegree, double &upDownDegree)
{

	Encoder tempEnc;
	if(ID == FIRST){
		tempEnc = Board1Enc();
	}else if(ID == SECOND){
		tempEnc = Board2Enc();
	}

	double leftRightDegreeTmp, upDownDegreeTmp;
	double a, b, c, d, p, q;

	a = 2.0 * MOTOR_PULSE_PER_DEGREE;
	b = MOTOR_PULSE_PER_DEGREE;
	p = tempEnc.CH1VALUE - 5000000.0;

	c = 2.0 * MOTOR_PULSE_PER_DEGREE;
	d =  -MOTOR_PULSE_PER_DEGREE;
	q = tempEnc.CH2VALUE - 5000000.0;


	leftRightDegreeTmp = (d*p-b*q) / (a*d - b*c);

	upDownDegreeTmp = (a*q-c*p) / (a*d - b*c);

	if((a*d - b*c) == 0)
	{
		leftRightDegreeTmp = 0;
		upDownDegreeTmp = 0;
	}

	if(ID== FIRST){
		leftRightDegreeTmp = -leftRightDegreeTmp;
	}else if(ID== SECOND){
		upDownDegreeTmp = -upDownDegreeTmp;
	}

	leftRightDegree = leftRightDegreeTmp;
	upDownDegree = upDownDegreeTmp;

	return false;
}


void MeroNeckDriver::startControlPeriodThread()
{
	if(!__IS_EXIST_CONTROL_THREAD) {
		this->m_PanTiltRollBend_Thread = boost::thread(boost::bind(&MeroNeckDriver::runControlPeriod,this));
	}
}

void MeroNeckDriver::runControlPeriod()
{
	__IS_EXIST_CONTROL_THREAD = true;
	clock_t start, end;

	while(true){
		start = clock();
		moveBoardMotorinThread( FIRST, m_pantilt_q, board1Enc, S_Pantilt_leftRightDegree, S_Pantilt_upDownDegree, S_Pantilt_speed );
		moveBoardMotorinThread( SECOND, m_rollbend_q, board2Enc, S_Rollbend_leftRightDegree, S_Rollbend_upDownDegree, S_Rollbend_speed );
		//Sleep(1);
		ros::Duration(0.01).sleep();
		end = clock();
		//if(end-start  > 5)
		//cout << "motor Priod: " << end-start <<" ms" <<endl;

	}
}

bool MeroNeckDriver::contorlPeriodmoveAbsMotor( MOTOR::BOARD_ID id,  double leftRightDegree, double upDownDegree, int speed )
{
	CH1_CH2_Degree tmpLR_UD_Degree;

	tmpLR_UD_Degree.CH1Degree = leftRightDegree;
	tmpLR_UD_Degree.CH2Degree = upDownDegree;
	tmpLR_UD_Degree.speed = speed;

	pushQueue(id, tmpLR_UD_Degree);
	return true;
}

void MeroNeckDriver::pushQueue( MOTOR::BOARD_ID id, CH1_CH2_Degree tmpLR_UD_Degree )
{
	if(id == FIRST){
		m_pantilt_q.push(tmpLR_UD_Degree);
	}else if(id == SECOND){
		m_rollbend_q.push(tmpLR_UD_Degree);
	}
}

//void CALLBACK MeroNeckDriver::TimeProc( UINT m_nTimerID, UINT uiMsg, DWORD dwUser, DWORD dw1, DWORD d2 )
//{
//}

bool MeroNeckDriver::initPantiltRollBendMotors()
{
	bool res = false;
	//Sleep(500);
	//ros::Duration(0.5).sleep();
	res = motorOff(FIRST);
	res = motorOff(SECOND);

	//Sleep(500);
	ros::Duration(1).sleep();
	res = motorOn(FIRST);
	res = motorOn(SECOND);

	Encoder bo1;
	bo1.CH1VALUE = 5000000.0;
	bo1.CH2VALUE = 5000000.0;
	Board1Enc(bo1);
	Board2Enc(bo1);

	motorBoardValueReset(FIRST);
	motorBoardValueReset(SECOND);
	ros::Duration(0.5).sleep();
	setCompliance(200);
	setMotorSpeed(FIRST, 1);
	setMotorSpeed(SECOND, 1);

	chkMotorLimitNeck(FIRST);
	motorBoardValueReset(FIRST);
	//Sleep(500);
	ros::Duration(0.5).sleep();

	chkMotorLimitNeckRollBend(SECOND);
	motorBoardValueReset(SECOND);
	//Sleep(500);
	ros::Duration(0.5).sleep();

	chkMotorLimitNeckSecond(FIRST);
	motorBoardValueReset(FIRST);
	//Sleep(500);
	ros::Duration(0.5).sleep();

	setCompliance(250);

	bo1.CH1VALUE = 5000000.0;
	bo1.CH2VALUE = 5000000.0;
	Board1Enc(bo1);
	Board2Enc(bo1);

	//start main thread
	startControlPeriodThread();
	
	return res;
}

void MeroNeckDriver::moveBoardMotorinThread( MOTOR::BOARD_ID id, queue<CH1_CH2_Degree>& boardQueue, Encoder &boardEncoder, double& ch1Degree, double& ch2Degree, int& speed )
{
	if(!boardQueue.empty()){

		while(boardQueue.size() >1){
			boardQueue.pop();
		}

		CH1_CH2_Degree tempDegrees = boardQueue.front();
		ch1Degree = tempDegrees.CH1Degree;
		ch2Degree = tempDegrees.CH2Degree;
		speed = tempDegrees.speed;

		if(!boardQueue.empty()){
			boardQueue.pop();
		}

		if(speed == -1){
			moveAbsfunc(true, id, boardEncoder, ch1Degree,ch2Degree);

		}else{
			setMotorSpeed(id,speed);
			moveAbsfunc(false, id, boardEncoder, ch1Degree,ch2Degree);
		}
	}
}

int MeroNeckDriver::moveAbsfunc( bool period, MOTOR::BOARD_ID id, Encoder& motorEncoder, double CH1Degree, double CH2Degree )
{

	double leftRightDegree = CH1Degree;
	double upDownDegree = CH2Degree;
	
	if(id == FIRST){
		 leftRightDegree = -1.0 * leftRightDegree;
		S_Pantilt_leftRightDegree =leftRightDegree;
		S_Pantilt_upDownDegree = upDownDegree;
	}else if(id == SECOND){
		upDownDegree = -1.0 * upDownDegree;
		S_Rollbend_leftRightDegree = leftRightDegree;
		S_Rollbend_upDownDegree = upDownDegree;
	}

	string strResult = "";
	string PA_command = "";
	bool resultMove = false;

	double degreeToPulseDouble = MOTOR_PULSE_PER_DEGREE * leftRightDegree * 2 + 5000000.0; // pan
	double degreeToPulse = MOTOR_PULSE_PER_DEGREE * upDownDegree; // tilt

	double ch1_value = degreeToPulseDouble + degreeToPulse;
	double ch2_value = degreeToPulseDouble - degreeToPulse;

	//writeEncoder
	motorEncoder.CH1VALUE = ch1_value;
	motorEncoder.CH2VALUE = ch2_value;


	if(period){
		PA_command = "PP"+intToString((int)motorEncoder.CH1VALUE)+","+intToString((int)motorEncoder.CH2VALUE);

	}else{
		PA_command = "PA"+intToString((int)motorEncoder.CH1VALUE)+","+intToString((int)motorEncoder.CH2VALUE);
	}

	resultMove = writeToMotor(id,PA_command);
	//cout<< "writeToMotor Move: [" << id << "]" << "Command: " << PA_command << endl;
	return resultMove;

}

void MeroNeckDriver::errorCheck( MOTOR::BOARD_ID ID, short* errorCode)
{
	MOTOR::MOTOR_ERROR_CODE motorErrorFirst_V = MOTOR_OK;
	MOTOR::MOTOR_ERROR_CODE motorErrorFirst_C = MOTOR_OK;
	MOTOR::MOTOR_ERROR_CODE motorErrorSecond_V = MOTOR_OK;
	MOTOR::MOTOR_ERROR_CODE motorErrorSecond_C = MOTOR_OK;
	string result = "";
	result = writeToMotorwithAck(ID, "Q2");
	//cout << "Error Result: " << result<<" Size:" <<result.size() <<endl;
	cout << "Error Result Ins: " << result<<endl;

    initErrorCode(errorCode);

	if(result.size()>0 && result.size()<15){
		string voltAmp = result.erase(0,4);
		voltAmp.erase(4,6);
		string strBinary = GetBinaryStringFromHexString(voltAmp);
		if(strBinary.size() == 16){
			if(strBinary.compare(15, 1, "1")==  0){
				//1�� ���� ��п���
				if(strBinary.compare(13, 1, "1")==  0){
					motorErrorFirst_V = LOW_VOLT;
				}else if(strBinary.compare(12, 1, "1")==  0){
					motorErrorFirst_V = HIGH_VOLT;
				}
			}

			if(strBinary.compare(14, 1, "1")==  0){
				//2�� ���� ��п���
				if(strBinary.compare(13, 1, "1")==  0){
					motorErrorSecond_V = LOW_VOLT;
				}else if(strBinary.compare(12, 1, "1")==  0){
					motorErrorSecond_V = HIGH_VOLT;
				}
			}

			if(strBinary.compare(7, 1, "1")==  0){
				motorErrorFirst_C = OVER_CURRENT;

			}

			if(strBinary.compare(3, 1, "1")==  0){
				motorErrorSecond_C = OVER_CURRENT;
			}
		}
	}

	if(motorErrorFirst_V == LOW_VOLT){
		errorCode[0] = 1;
	}else if(motorErrorFirst_V == HIGH_VOLT){
		errorCode[0] = 2;
	}

	if(motorErrorFirst_C == OVER_CURRENT){
		errorCode[0] += 3;
	}

	if(motorErrorSecond_V == LOW_VOLT){
		errorCode[1] = 1;
	}else if(motorErrorSecond_V == HIGH_VOLT){
		errorCode[1] = 2;
	}

	if(motorErrorSecond_C == OVER_CURRENT){
		errorCode[1] += 3;
	}
//0:OK, 1: low_volt, 2: high_volt, 3: over_current, 4: low_volt +over_current,��5: high_volt��over_current
}

string MeroNeckDriver::GetBinaryStringFromHexString (string sHex)
{
	string sReturn = "";
	for (int i = 0; i < sHex.length (); ++i)
	{
		switch (sHex [i])
		{
		case '0': sReturn.append ("0000"); break;
		case '1': sReturn.append ("0001"); break;
		case '2': sReturn.append ("0010"); break;
		case '3': sReturn.append ("0011"); break;
		case '4': sReturn.append ("0100"); break;
		case '5': sReturn.append ("0101"); break;
		case '6': sReturn.append ("0110"); break;
		case '7': sReturn.append ("0111"); break;
		case '8': sReturn.append ("1000"); break;
		case '9': sReturn.append ("1001"); break;
		case 'a': sReturn.append ("1010"); break;
		case 'b': sReturn.append ("1011"); break;
		case 'c': sReturn.append ("1100"); break;
		case 'd': sReturn.append ("1101"); break;
		case 'e': sReturn.append ("1110"); break;
		case 'f': sReturn.append ("1111"); break;
		}
	}
	return sReturn;
}

void MeroNeckDriver::initErrorCode(short* errorCode)
{
	for(int i =0; i<3; i++){
		errorCode[i] = 0;
	}
}


