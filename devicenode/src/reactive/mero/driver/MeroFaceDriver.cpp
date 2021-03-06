/*
 * MeroFaceDriver.cpp
 *
 *  Created on: 2014. 6. 2.
 *      Author: msyoo
 */

#include "MeroFaceDriver.h"
#include <roscir/env/Config.h>

namespace reactive {
namespace mero {
namespace driver {

pthread_mutex_t MeroFaceDriver::__motor_command_mutex = PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP;

double MeroFaceDriver::S_Eyebrow_CH1Degree = 0;
double MeroFaceDriver::S_Eyebrow_CH2Degree = 0;
int MeroFaceDriver::S_Eyebrow_CH1speed = 0;
int MeroFaceDriver::S_Eyebrow_CH2speed = 0;

double MeroFaceDriver::S_Pupil_CH1Degree = 0;
double MeroFaceDriver::S_Pupil_CH2Degree = 0;
int MeroFaceDriver::S_Pupil_CH1speed = 0;
int MeroFaceDriver::S_Pupil_CH2speed = 0;


double MeroFaceDriver::S_EyelidLR_CH1Degree= 0;
double MeroFaceDriver::S_EyelidLR_CH2Degree= 0;
int MeroFaceDriver::S_EyelidLR_CH1speed= 0;
int MeroFaceDriver::S_EyelidLR_CH2speed= 0;

double MeroFaceDriver::S_EyelidR_CH1Degree= 0;
double MeroFaceDriver::S_EyelidR_CH2Degree= 0;
int MeroFaceDriver::S_EyelidR_CH1speed= 0;
int MeroFaceDriver::S_EyelidR_CH2speed= 0;

double MeroFaceDriver::S_LipUL_CH1Degree= 0;
double MeroFaceDriver::S_LipUL_CH2Degree= 0;
int MeroFaceDriver::S_LipUL_CH1speed= 0;
int MeroFaceDriver::S_LipUL_CH2speed= 0;

double MeroFaceDriver::S_LipC_CH1Degree= 0;
double MeroFaceDriver::S_LipC_CH2Degree= 0;
int MeroFaceDriver::S_LipC_CH1speed= 0;
int MeroFaceDriver::S_LipC_CH2speed= 0;


queue<CH_Degree> MeroFaceDriver::m_eybrow_UD;
queue<CH_Degree> MeroFaceDriver::m_eybrow_CW;
queue<CH_Degree> MeroFaceDriver::m_eyelid_R_UD;
queue<CH_Degree> MeroFaceDriver::m_eyelid_L_UD;
queue<CH_Degree> MeroFaceDriver::m_eyelid_Rot_CW;
queue<CH_Degree> MeroFaceDriver::m_pupil_UD;
queue<CH_Degree> MeroFaceDriver::m_pupil_LR;
queue<CH_Degree> MeroFaceDriver::m_lip_UP_CW;
queue<CH_Degree> MeroFaceDriver::m_lip_LO_CW;
queue<CH_Degree> MeroFaceDriver::m_lip_CE_WP;

MeroFaceDriver::MeroFaceDriver() {
//	m_nTimerID = timeSetEvent(1,0,TimeProc,(DWORD)0, TIME_PERIODIC);

	string comPort = CConfig::getInstance()->getParamValue("MERO_FACE_COM_PORT");
	if(comPort.empty()){
		comPort = "COM4";
	}

	m_isFaceThread = false;

	cout<<"[Info] Face Com Port: " << comPort << endl;

	serial.setup(comPort, MeroFaceDriver::BAUD_RATE_FACE);
	serial.flush();

//	InitializeCriticalSection(&motor_command_cs);

	mff = MeroFunctionFactory::getInstance();


}

MeroFaceDriver::~MeroFaceDriver() {
}


MeroFaceDriver *MeroFaceDriver::getInstance()
{
	static MeroFaceDriver thisInstance;
	cout << "[MeroFaceDriver.getInstance] : Create Sole Instance(MeroFaceDriver).." << endl;
	return &thisInstance;
}


//void MeroFaceDriver::TimeProc(UINT m_nTimerID, UINT uiMsg, DWORD dwUser, DWORD dw1, DWORD d2)
//{
//}

bool MeroFaceDriver::motorOn(MOTOR::BOARD_ID ID)
{
	string sID = motorIDToString(ID);
	string readByteResult = "";
	string PR_Command = "PR000" + sID;

	//Servo Error Reset
	readByteResult = writeToMotorwithAck(ID, PR_Command);
	sleep(100);
	//ros::Duration(0.1).sleep();

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
		}else if(ID == THIRD){
			encoderValueChk(ID, board3Enc);
		}else if(ID == FOURTH){
			encoderValueChk(ID, board4Enc);
		}else if(ID == FIFTH){
			encoderValueChk(ID, board5Enc);
		}else if(ID == SIXTH){
			encoderValueChk(ID, board6Enc);
		}

		return true;
	}else{
		return false;
	}
}

bool MeroFaceDriver::motorOff(MOTOR::BOARD_ID ID)
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


bool MeroFaceDriver::setMotorSpeed( MOTOR::BOARD_ID id, int ch1Speed, int ch2Speed )
{
	string strCh1MotorSpeed, strCh2MotorSpeed;

	if(id == FIRST || id == SECOND){
		strCh1MotorSpeed= MOTOR_2619_MAPPING_RPM_SPEED[ch1Speed];
		strCh2MotorSpeed= MOTOR_2619_MAPPING_RPM_SPEED[ch2Speed];
	}else{
		strCh1MotorSpeed = MOTOR_1512_MAPPING_RPM_SPEED[ch1Speed];
		strCh2MotorSpeed = MOTOR_1512_MAPPING_RPM_SPEED[ch2Speed];
	}
	string strSpeedCommand = "SS" + strCh1MotorSpeed + "," + strCh2MotorSpeed;
	return writeToMotor(id,strSpeedCommand);
}

bool MeroFaceDriver::writeToMotor(MOTOR::BOARD_ID ID, string command)
{
//	EnterCriticalSection(&motor_command_cs);
	pthread_mutex_lock( &__motor_command_mutex );
	bool result = false;
	string sID = motorIDToString(ID);
	string sCommandCom =  command + "!";
	string sIDCommand = sID + sCommandCom;
	char id  = (char)(((ID)));
        char *chIDCommand = new char[sIDCommand.length() + 1];
        sprintf(chIDCommand, "%c%s", id, sCommandCom.c_str());
        int res = serial.writeBytes((unsigned char*)(((chIDCommand))), sIDCommand.length());
        if(chIDCommand != NULL){
		chIDCommand =NULL;
		delete []chIDCommand;
	}
        if(res == sIDCommand.length()){
            result = true;
        }else{
            result = false;
        }
        sleep(2); //Impotant Communication Delay!!!
        //ros::Duration(0.001).sleep();
//        LeaveCriticalSection(&motor_command_cs);
        pthread_mutex_unlock( &__motor_command_mutex );
        return result;
    }

string MeroFaceDriver::writeToMotorwithAck(MOTOR::BOARD_ID ID, string command)
{
//	EnterCriticalSection(&motor_command_cs);
	pthread_mutex_lock( &__motor_command_mutex );
	clock_t start, end;
	string motorReadResult = "";
	string sID = motorIDToString(ID);
	string sCommandCom = command + ";";
	string sIDCommand = sID + sCommandCom;
	char id = (char)((ID));
	char *chIDCommand = new char[sIDCommand.length() + 1];
	sprintf(chIDCommand, "%c%s", id, sCommandCom.c_str());
	start = clock();
	int res = serial.writeBytes((unsigned char*)((chIDCommand)), sIDCommand.length());
	if(chIDCommand != NULL){
	chIDCommand =NULL;
	delete []chIDCommand;
}
	if(res == sIDCommand.length()){
		string commandQuery = sCommandCom.erase(2, sCommandCom.size());
		unsigned char chReadByteResult[256] = {};
		motorReadResult = readFromMotor();
		if(motorReadResult.size() > 0){
		}else{
			motorReadResult = "";
		}
	}

//	LeaveCriticalSection(&motor_command_cs);
	pthread_mutex_unlock( &__motor_command_mutex );
	return motorReadResult;
}

string MeroFaceDriver::readFromMotor()
{
	const int readArraySize = 1;
	const int readReaultArraySize = 256;
	const int responseTimeout = 1000;
	int resultCommandLength = 0;
	unsigned char readByteArray[readArraySize] = {};
	unsigned char readResultByteArray[readReaultArraySize] = {};
	clock_t start;
	clock_t end, endRoof;
	start = clock();
	//printf("\nresultByteArray: ");
	while(true){
		int cntByte = serial.readBytes((unsigned char*)((readByteArray)), readArraySize);
		if(cntByte > 0){
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
	return string((char*)((readResultByteArray)));
}

string MeroFaceDriver::motorBoardValueReset(MOTOR::BOARD_ID ID)
{
	return writeToMotorwithAck(ID, "QEA55A");
}

bool MeroFaceDriver::encoderValueChk(MOTOR::BOARD_ID ID, Encoder & values)
{
	bool res = false;
	string resultQP = writeToMotorwithAck(ID, "QP");
	if(resultQP.size() > 0){
		resultQP.erase(0, 3);
		string ch1Value = resultQP.substr(0, resultQP.find(","));
		string ch2Value = resultQP.substr(resultQP.find(",") + 1, resultQP.find(";") - resultQP.find(",") - 1);
		ch1Value.insert(0, "0x");
		ch2Value.insert(0, "0x");
		char *stop1;
		char *stop2;
		long ch1IntVal = strtol(ch1Value.c_str(), &stop1, 16);
		long ch2IntVal = strtol(ch2Value.c_str(), &stop2, 16);
		values.CH1VALUE = ch1IntVal;
		values.CH2VALUE = ch2IntVal;
		res = true;
	}else{
		res = false;
	}
	return res;
}

bool MeroFaceDriver::compareEncoderCHValue(MOTOR::MOTOR_CH ch, double thresholdDegree, Encoder & preEncoder, Encoder & curEncoder)
{
	bool tempDiff = false;
	long diffValueCH1 = abs(preEncoder.CH1VALUE - curEncoder.CH1VALUE);
	long diffValueCH2 = abs(preEncoder.CH2VALUE - curEncoder.CH2VALUE);
	if(ch == CH1){
		if(diffValueCH1 < thresholdDegree){
			tempDiff = true;
		}
	}
	else
		if(ch == CH2){
			if(diffValueCH2 < thresholdDegree){
				tempDiff = true;
			}
		}

	return tempDiff;
}


int MeroFaceDriver::moveAbsolutePosition(int motorID, double position, int speed )
{
	CH_Degree tmpValue;
		tmpValue.ChDegree =  position;
		tmpValue.speed =speed;
		if(motorID == 0){
			m_eybrow_UD.push(tmpValue);
		}else if(motorID == 1){
			m_eybrow_CW.push(tmpValue);
		}else if(motorID == 2){
			m_eyelid_R_UD.push(tmpValue);
		}else if(motorID == 3){
			m_eyelid_L_UD.push(tmpValue);
		}else if(motorID == 4){
			m_eyelid_Rot_CW.push(tmpValue);
		}else if(motorID == 5){
			m_pupil_UD.push(tmpValue);
		}else if(motorID == 6){
			m_pupil_LR.push(tmpValue);
		}else if(motorID == 7){
			m_lip_UP_CW.push(tmpValue);
		}else if(motorID == 8){
			m_lip_LO_CW.push(tmpValue);
		}else if(motorID == 9){
			m_lip_CE_WP.push(tmpValue);
		}
		return 0;
}

int MeroFaceDriver::moveAbsfunc(bool period, MOTOR::BOARD_ID id, Encoder & motorEncoder, double CH1Degree, double CH2Degree)
{
	if(id == SIXTH){
		S_Eyebrow_CH1Degree = CH1Degree;
		S_Eyebrow_CH2Degree = CH2Degree;
	}else if(id == THIRD){
		S_Pupil_CH1Degree = CH1Degree;
		S_Pupil_CH2Degree = CH2Degree;
	}else if(id == FOURTH){
		S_EyelidLR_CH1Degree = CH1Degree;
		S_EyelidLR_CH2Degree = CH2Degree;
	}else if(id == FIFTH){
		S_EyelidR_CH1Degree = CH1Degree;
		S_EyelidR_CH2Degree = CH2Degree;
	}else if(id == SECOND){
		S_LipUL_CH1Degree = CH1Degree;
		S_LipUL_CH2Degree = CH2Degree;
	}else if(id == FIRST){
		S_LipC_CH1Degree = CH1Degree;
		S_LipC_CH2Degree = CH2Degree;
	}


	string strResult = "";
	string PA_command = "";

	bool resultMove = false;


	double degreeToPulseCH1, degreeToPulseCH2;

	if(id == FIRST || id == SECOND){
		degreeToPulseCH1 = MOTOR_PULSE_PER_DEGREE_2619 * CH1Degree+ 5000000.0;
		degreeToPulseCH2 = MOTOR_PULSE_PER_DEGREE_2619 * CH2Degree+ 5000000.0;
	}else{
		degreeToPulseCH1 = MOTOR_PULSE_PER_DEGREE_1512 * CH1Degree+ 5000000.0;
		degreeToPulseCH2 = MOTOR_PULSE_PER_DEGREE_1512 * CH2Degree+ 5000000.0;
	}


	//writeEncoder
	motorEncoder.CH1VALUE = degreeToPulseCH1;
	motorEncoder.CH2VALUE = degreeToPulseCH2;

	if(period){
		PA_command = "PP"+mff->intToString((int)motorEncoder.CH1VALUE)+","+mff->intToString((int)motorEncoder.CH2VALUE);

	}else{
		PA_command = "PA"+mff->intToString((int)motorEncoder.CH1VALUE)+","+mff->intToString((int)motorEncoder.CH2VALUE);
	}
	resultMove = writeToMotor(id,PA_command);
	//cout<< "writeToMotor Move: [" << id << "]" << "Command: " << PA_command << endl;
	return resultMove;
}

void MeroFaceDriver::runFaceThread()
{
	clock_t start, end;
	m_isFaceThread = true;
	int timeInterval = 1;
	while(true){

		start = clock();

		moveBoardMotorinThread(SIXTH, m_eybrow_UD, m_eybrow_CW, board6Enc, S_Eyebrow_CH1Degree, S_Eyebrow_CH2Degree, S_Eyebrow_CH1speed, S_Eyebrow_CH2speed);

		moveBoardMotorinThread( FOURTH, m_eyelid_R_UD, m_eyelid_L_UD, board4Enc, S_EyelidLR_CH1Degree, S_EyelidLR_CH2Degree, S_EyelidLR_CH1speed, S_EyelidLR_CH2speed);

		moveBoardMotorinThread( FIFTH, m_eyelid_Rot_CW, m_eyelid_Rot_CW, board5Enc, S_EyelidR_CH1Degree, S_EyelidR_CH2Degree, S_EyelidR_CH1speed, S_EyelidR_CH2speed);

		moveBoardMotorinThread( THIRD, m_pupil_UD, m_pupil_LR, board3Enc, S_Pupil_CH1Degree, S_Pupil_CH2Degree, S_Pupil_CH1speed, S_Pupil_CH2speed);

		moveBoardMotorinThread( SECOND, m_lip_UP_CW, m_lip_LO_CW, board2Enc, S_LipUL_CH1Degree, S_LipUL_CH2Degree, S_LipUL_CH1speed, S_LipUL_CH2speed);

		moveBoardMotorinThread( FIRST, m_lip_CE_WP, m_lip_CE_WP, board1Enc, S_LipC_CH1Degree, S_LipC_CH2Degree, S_LipC_CH1speed, S_LipC_CH2speed);

		sleep(timeInterval);
		end = clock();


		//if(end-start > 10)
		//	cout << "Priod Elasped time: " << end-start << "ms " <<endl;
		//cout << "& ";
	}
}

void MeroFaceDriver::startFaceThread()
{
	if(!m_isFaceThread){
		this->m_Face_Thread = boost::thread(boost::bind(&MeroFaceDriver::runFaceThread,this));
		cout << "[INFO] MeroFaceDriver::runFaceThread Starting" << endl;
	}
}

void MeroFaceDriver::moveOneMotor(MOTOR::BOARD_ID id, MOTOR::MOTOR_CH ch, double degree)
{
	string strResult = "";
		string PA_command = "";

		double degreeToPulse;

		if(id == FIRST || id == SECOND){
			degreeToPulse = MOTOR_PULSE_PER_DEGREE_2619* degree;
		}else{
			degreeToPulse = MOTOR_PULSE_PER_DEGREE_1512 * degree;
		}

		if(id == FIRST){
			if(ch == CH1){
				board1Enc.CH1VALUE += degreeToPulse;
				PA_command = "PA"+mff->intToString((int)board1Enc.CH1VALUE)+","+mff->intToString((int)board1Enc.CH2VALUE);

			}else if(ch == CH2){
				board1Enc.CH2VALUE += degreeToPulse;
				PA_command = "PA"+mff->intToString((int)board1Enc.CH1VALUE)+","+mff->intToString((int)board1Enc.CH2VALUE);
			}else{
				board1Enc.CH1VALUE += degreeToPulse;
				board1Enc.CH2VALUE += degreeToPulse;
				PA_command = "PA"+mff->intToString((int)board1Enc.CH1VALUE)+","+mff->intToString((int)board1Enc.CH2VALUE);
			}
		}else if(id == SECOND){
			if(ch == CH1){
				board2Enc.CH1VALUE += degreeToPulse;
				PA_command = "PA"+mff->intToString((int)board2Enc.CH1VALUE)+","+mff->intToString((int)board2Enc.CH2VALUE);

			}else if(ch == CH2){
				board2Enc.CH2VALUE += degreeToPulse;
				PA_command = "PA"+mff->intToString((int)board2Enc.CH1VALUE)+","+mff->intToString((int)board2Enc.CH2VALUE);
			}else{
				board2Enc.CH1VALUE += degreeToPulse;
				board2Enc.CH2VALUE += degreeToPulse;
				PA_command = "PA"+mff->intToString((int)board2Enc.CH1VALUE)+","+mff->intToString((int)board2Enc.CH2VALUE);

			}

		}else if(id == THIRD){
			if(ch == CH1){
				board3Enc.CH1VALUE += degreeToPulse;
				PA_command = "PA"+mff->intToString((int)board3Enc.CH1VALUE)+","+mff->intToString((int)board3Enc.CH2VALUE);

			}else if(ch == CH2){
				board3Enc.CH2VALUE += degreeToPulse;
				PA_command = "PA"+mff->intToString((int)board3Enc.CH1VALUE)+","+mff->intToString((int)board3Enc.CH2VALUE);
			}else{
				board3Enc.CH1VALUE += degreeToPulse;
				board3Enc.CH2VALUE += degreeToPulse;
				PA_command = "PA"+mff->intToString((int)board3Enc.CH1VALUE)+","+mff->intToString((int)board3Enc.CH2VALUE);
			}
		}else if(id == FOURTH){
			if(ch == CH1){
				board4Enc.CH1VALUE += degreeToPulse;
				PA_command = "PA"+mff->intToString((int)board4Enc.CH1VALUE)+","+mff->intToString((int)board4Enc.CH2VALUE);

			}else if(ch == CH2){
				board4Enc.CH2VALUE += degreeToPulse;
				PA_command = "PA"+mff->intToString((int)board4Enc.CH1VALUE)+","+mff->intToString((int)board4Enc.CH2VALUE);
			}else{
				board4Enc.CH1VALUE += degreeToPulse;
				board4Enc.CH2VALUE += degreeToPulse;
				PA_command = "PA"+mff->intToString((int)board4Enc.CH1VALUE)+","+mff->intToString((int)board4Enc.CH2VALUE);
			}
		}else if(id == FIFTH){
			if(ch == CH1){
				board5Enc.CH1VALUE += degreeToPulse;
				PA_command = "PA"+mff->intToString((int)board5Enc.CH1VALUE)+","+mff->intToString((int)board5Enc.CH2VALUE);

			}else if(ch == CH2){
				board5Enc.CH2VALUE += degreeToPulse;
				PA_command = "PA"+mff->intToString((int)board5Enc.CH1VALUE)+","+mff->intToString((int)board5Enc.CH2VALUE);
			}else{
				board5Enc.CH1VALUE += degreeToPulse;
				board5Enc.CH2VALUE += degreeToPulse;
				PA_command = "PA"+mff->intToString((int)board5Enc.CH1VALUE)+","+mff->intToString((int)board5Enc.CH2VALUE);
			}
		}else if(id == SIXTH){
			if(ch == CH1){
				board6Enc.CH1VALUE += degreeToPulse;
				PA_command = "PA"+mff->intToString((int)board6Enc.CH1VALUE)+","+mff->intToString((int)board6Enc.CH2VALUE);

			}else if(ch == CH2){
				board6Enc.CH2VALUE += degreeToPulse;
				PA_command = "PA"+mff->intToString((int)board6Enc.CH1VALUE)+","+mff->intToString((int)board6Enc.CH2VALUE);
			}else{
				board6Enc.CH1VALUE += degreeToPulse;
				board6Enc.CH2VALUE += degreeToPulse;
				PA_command = "PA"+mff->intToString((int)board6Enc.CH1VALUE)+","+mff->intToString((int)board6Enc.CH2VALUE);
			}
		}

		writeToMotorwithAck(id,PA_command);
}

void MeroFaceDriver::chkMotorLimitModiBoardMotor1512(MOTOR::BOARD_ID id, double moveDegree)
{
	Encoder initEncoder;
	Encoder lowEncoder;
	Encoder upEncoder;
	Encoder curEncoder;
	Encoder preEncoder;
	long ch1EncValue = 5000000;
	long ch2EncValue = 5000000;

	motorBoardValueReset(id);
	moveOneMotorInit(id, INIT_POS);


	setCompliance(id, 50);
	sleep(100);
	setMotorSpeed(id, 100, 100);
	sleep(100);


	int sleepTime = 1100;
	moveOneMotor(id, ALL_CH, moveDegree);
	sleep(sleepTime);

	encoderValueChk(id, curEncoder);
	upEncoder = curEncoder;
	initEncoder = curEncoder;


	moveOneMotor(id, ALL_CH, -moveDegree * 2.0);
	sleep(sleepTime);

	encoderValueChk(id, curEncoder);
	lowEncoder = curEncoder;


	ch1EncValue = (upEncoder.CH1VALUE + lowEncoder.CH1VALUE) /2.0;
	ch2EncValue = (upEncoder.CH2VALUE + lowEncoder.CH2VALUE) /2.0;


//	cout << "ID: " << id << endl;
//	cout << "CH1: " << (upEncoder.CH1VALUE - lowEncoder.CH1VALUE)/MOTOR_PULSE_PER_DEGREE_1512 << endl;
//	cout << "CH2: " << (upEncoder.CH2VALUE - lowEncoder.CH2VALUE)/MOTOR_PULSE_PER_DEGREE_1512 << endl;
//
//	cout << "CH1: " << floor((upEncoder.CH1VALUE - lowEncoder.CH1VALUE)/MOTOR_PULSE_PER_DEGREE_1512/2.0) << endl;
//	cout << "CH2: " << floor((upEncoder.CH2VALUE - lowEncoder.CH2VALUE)/MOTOR_PULSE_PER_DEGREE_1512/2.0) << endl;

	string PA_command =  "PA"+mff->intToString((int)ch1EncValue)+","+mff->intToString((int)ch2EncValue);

	writeToMotorwithAck(id,PA_command);
	sleep(sleepTime);
	motorBoardValueReset(id);
	moveOneMotorInit(id, INIT_POS);
}

void MeroFaceDriver::moveOneMotorInit(MOTOR::BOARD_ID id, MOTOR::MOTOR_CH ch)
{
		string strResult = "";
	string PA_command = "";

	switch(id){
		case FIRST:
			switch(ch){
				case CH1:
					board1Enc.CH1VALUE = 5000000.0;
					PA_command = "PA"+mff->intToString((int)board1Enc.CH1VALUE)+","+mff->intToString((int)board1Enc.CH2VALUE);
					break;
				case CH2:
					board1Enc.CH2VALUE = 5000000.0;
					PA_command = "PA"+mff->intToString((int)board1Enc.CH1VALUE)+","+mff->intToString((int)board1Enc.CH2VALUE);
					break;
				case INIT_POS:
					board1Enc.CH1VALUE = 5000000.0;
					board1Enc.CH2VALUE = 5000000.0;
					PA_command = "PA"+mff->intToString((int)board1Enc.CH1VALUE)+","+mff->intToString((int)board1Enc.CH2VALUE);
					break;
			};
			break;

		case SECOND:
			switch(ch){
				case CH1:
					board2Enc.CH1VALUE = 5000000.0;
					PA_command = "PA"+mff->intToString((int)board2Enc.CH1VALUE)+","+mff->intToString((int)board2Enc.CH2VALUE);
					break;
				case CH2:
					board2Enc.CH2VALUE = 5000000.0;
					PA_command = "PA"+mff->intToString((int)board2Enc.CH1VALUE)+","+mff->intToString((int)board2Enc.CH2VALUE);
					break;
				case INIT_POS:
					board2Enc.CH1VALUE = 5000000.0;
					board2Enc.CH2VALUE = 5000000.0;
					PA_command = "PA"+mff->intToString((int)board2Enc.CH1VALUE)+","+mff->intToString((int)board2Enc.CH2VALUE);
					break;
			};
			break;

		case THIRD:
			switch(ch){
				case CH1:
					board3Enc.CH1VALUE = 5000000.0;
					PA_command = "PA"+mff->intToString((int)board3Enc.CH1VALUE)+","+mff->intToString((int)board3Enc.CH2VALUE);
					break;
				case CH2:
					board3Enc.CH2VALUE = 5000000.0;
					PA_command = "PA"+mff->intToString((int)board3Enc.CH1VALUE)+","+mff->intToString((int)board3Enc.CH2VALUE);
					break;
				case INIT_POS:
					board3Enc.CH1VALUE = 5000000.0;
					board3Enc.CH2VALUE = 5000000.0;
					PA_command = "PA"+mff->intToString((int)board3Enc.CH1VALUE)+","+mff->intToString((int)board3Enc.CH2VALUE);
					break;
			};
			break;

		case FOURTH:
			switch(ch){
				case CH1:
					board4Enc.CH1VALUE = 5000000.0;
					PA_command = "PA"+mff->intToString((int)board4Enc.CH1VALUE)+","+mff->intToString((int)board4Enc.CH2VALUE);
					break;
				case CH2:
					board4Enc.CH2VALUE = 5000000.0;
					PA_command = "PA"+mff->intToString((int)board4Enc.CH1VALUE)+","+mff->intToString((int)board4Enc.CH2VALUE);
					break;
				case INIT_POS:
					board4Enc.CH1VALUE = 5000000.0;
					board4Enc.CH2VALUE = 5000000.0;
					PA_command = "PA"+mff->intToString((int)board4Enc.CH1VALUE)+","+mff->intToString((int)board4Enc.CH2VALUE);
					break;
			};
			break;

		case FIFTH:
			switch(ch){
				case CH1:
					board5Enc.CH1VALUE = 5000000.0;
					PA_command = "PA"+mff->intToString((int)board5Enc.CH1VALUE)+","+mff->intToString((int)board5Enc.CH2VALUE);
					break;
				case CH2:
					board5Enc.CH2VALUE = 5000000.0;
					PA_command = "PA"+mff->intToString((int)board5Enc.CH1VALUE)+","+mff->intToString((int)board5Enc.CH2VALUE);
					break;
				case INIT_POS:
					board5Enc.CH1VALUE = 5000000.0;
					board5Enc.CH2VALUE = 5000000.0;
					PA_command = "PA"+mff->intToString((int)board5Enc.CH1VALUE)+","+mff->intToString((int)board5Enc.CH2VALUE);
					break;
					};
			break;

		case SIXTH:
			switch(ch){
				case CH1:
					board6Enc.CH1VALUE = 5000000.0;
					PA_command = "PA"+mff->intToString((int)board6Enc.CH1VALUE)+","+mff->intToString((int)board6Enc.CH2VALUE);
					break;
				case CH2:
					board6Enc.CH2VALUE = 5000000.0;
					PA_command = "PA"+mff->intToString((int)board6Enc.CH1VALUE)+","+mff->intToString((int)board6Enc.CH2VALUE);
					break;
				case INIT_POS:
					board6Enc.CH1VALUE = 5000000.0;
					board6Enc.CH2VALUE = 5000000.0;
					PA_command = "PA"+mff->intToString((int)board6Enc.CH1VALUE)+","+mff->intToString((int)board6Enc.CH2VALUE);
					break;
			};
			break;
	};

	writeToMotorwithAck(id,PA_command);
}

bool MeroFaceDriver::setComplianceAll(int val)
{
	bool res = false;
		string strResult ="";
		string strSs = mff->intToString(val);
		string strSsCommand = "Ss" + strSs + "," + strSs;

		res = writeToMotor(FIRST,strSsCommand);
		sleep(1);
		res = writeToMotor(SECOND,strSsCommand);
		sleep(1);
		res = writeToMotor(THIRD,strSsCommand);
		sleep(1);
		res = writeToMotor(FOURTH,strSsCommand);
		sleep(1);
		res = writeToMotor(FIFTH,strSsCommand);
		sleep(1);
		res = writeToMotor(SIXTH,strSsCommand);
		sleep(1);

		return res;
}

bool MeroFaceDriver::setCompliance(MOTOR::BOARD_ID id, int val)
{
	bool res = false;
	string strResult ="";
	string strSs = mff->intToString(val);
	string strSsCommand = "Ss" + strSs + "," + strSs;

	return writeToMotor(id,strSsCommand);
}

void MeroFaceDriver::chkMotorLimitLipUL()
{
		Encoder standardEncoder;
		Encoder initEncoder;
		Encoder lowEncoder;
		Encoder upEncoder;
		Encoder curEncoder;
		Encoder preEncoder;

		motorBoardValueReset(SECOND);
		sleep(500);

		setCompliance(SECOND, 50);
		sleep(500);
		setMotorSpeed(SECOND, 100, 100);
		sleep(500);

		int sleepTime = 70;
		double moveDegree = 1.0;
		MOTOR_CH ch = ALL_CH;
		bool ch1Flag = false;
		bool ch2Flag = false;

		encoderValueChk(SECOND, initEncoder);
		preEncoder=initEncoder;

		Board2Enc(initEncoder);

		while(ch1Flag==false || ch2Flag==false){

			if(ch == ALL_CH ){
				moveOneMotor(SECOND, ALL_CH, moveDegree);
			}else if(ch == CH1 ){
				moveOneMotor(SECOND, CH1, moveDegree);
			}else if(ch == CH2 ){
				moveOneMotor(SECOND, CH2, moveDegree);
			}
			sleep(sleepTime);
			encoderValueChk(SECOND, curEncoder);

			ch1Flag = compareEncoderCHValue(CH1, 9.0, preEncoder, curEncoder );
			ch2Flag = compareEncoderCHValue(CH2, 9.0, preEncoder, curEncoder );

			preEncoder = curEncoder;

			if(ch1Flag== true && ch2Flag == false){
				upEncoder.CH1VALUE = curEncoder.CH1VALUE;
				ch = CH2;
			}else if(ch1Flag== false && ch2Flag == true){
				upEncoder.CH2VALUE = curEncoder.CH2VALUE;
				ch = CH1;
			}else if(ch1Flag== true && ch2Flag == true){
				upEncoder.CH1VALUE = curEncoder.CH1VALUE;
				upEncoder.CH2VALUE = curEncoder.CH2VALUE;
				break;
			}
		}

		chkLipLimitCh(SECOND, CH1, 1.0, lowEncoder);
		chkLipLimitCh(SECOND, CH2, 1.0, lowEncoder);

		initEncoder.CH1VALUE = (upEncoder.CH1VALUE + lowEncoder.CH1VALUE)/2.0;
		initEncoder.CH2VALUE = (upEncoder.CH2VALUE + lowEncoder.CH1VALUE)/2.0;


		string PA_command =  "PA"+mff->intToString((int)initEncoder.CH1VALUE)+","+mff->intToString((int)initEncoder.CH2VALUE);
		writeToMotorwithAck(SECOND,PA_command);
		sleep(1000);

//		cout << "CH1: " << (upEncoder.CH1VALUE - lowEncoder.CH1VALUE)/MOTOR_PULSE_PER_DEGREE_2619 << endl;
//		cout << "CH2: " << (upEncoder.CH2VALUE - lowEncoder.CH2VALUE)/MOTOR_PULSE_PER_DEGREE_2619 << endl;
//
//		cout << "CH1: " << floor((upEncoder.CH1VALUE - lowEncoder.CH1VALUE)/MOTOR_PULSE_PER_DEGREE_2619/2.0) << endl;
//		cout << "CH2: " << floor((upEncoder.CH2VALUE - lowEncoder.CH2VALUE)/MOTOR_PULSE_PER_DEGREE_2619/2.0) << endl;

		motorBoardValueReset(SECOND);
		moveOneMotorInit(SECOND, INIT_POS);
}

void MeroFaceDriver::chkMotorLimitLipLR(double moveDegree, Encoder & limitValue)
{
	bool chFlag = false;
		int sleepTime = 100;
		Encoder preEncoder, curEncoder;

		encoderValueChk(FIRST, curEncoder);
		Board1Enc(curEncoder);
		preEncoder = curEncoder;

		int moveCnt = 0;
		do{

			moveOneMotor(FIRST, CH1, moveDegree);
			sleep(sleepTime);
			encoderValueChk(FIRST, curEncoder);

			chFlag = compareEncoderCHValue(CH1, 9.0, preEncoder, curEncoder );

			if(chFlag){
				limitValue.CH1VALUE = curEncoder.CH1VALUE;
			}

			preEncoder = curEncoder;
			moveCnt++;
		}while(chFlag == false);

		moveOneMotor(FIRST, CH1, -moveCnt*moveDegree);
		sleep(500);
}

void MeroFaceDriver::chkLipLimitLR()
{
		Encoder initEncoder;
		Encoder lowEncoder;
		Encoder upEncoder;

		motorOff(FIRST);
		sleep(800);
		motorOn(FIRST);
		setCompliance(SECOND, 50);
		setMotorSpeed(SECOND, 100, 100);
		sleep(100);
		encoderValueChk(FIRST, lowEncoder);
		chkMotorLimitLipLR(1.0,upEncoder);
		//chkMotorLimitLipLR(-1.0,lowEncoder);

		initEncoder.CH1VALUE =lowEncoder.CH1VALUE;
		initEncoder.CH2VALUE = 5000000;


		string PA_command =  "PA"+mff->intToString((int)initEncoder.CH1VALUE)+","+mff->intToString((int)initEncoder.CH2VALUE);
		writeToMotorwithAck(FIRST,PA_command);
		sleep(1000);

//		cout << "CH1: " << ((upEncoder.CH1VALUE- lowEncoder.CH1VALUE)/MOTOR_PULSE_PER_DEGREE_2619) << endl;
//
//		cout << "CH1: " << floor(((upEncoder.CH1VALUE- lowEncoder.CH1VALUE )/MOTOR_PULSE_PER_DEGREE_2619)) << endl;

		motorBoardValueReset(FIRST);
		moveOneMotorInit(FIRST, INIT_POS);

}

void MeroFaceDriver::chkLipLimitCh(MOTOR::BOARD_ID id, MOTOR::MOTOR_CH ch, double moveDegree, Encoder & lowEncoder)
{
	bool chFlag = false;
		int sleepTime = 50;
		Encoder preEncoder, curEncoder;

		moveOneMotor(id, ch, -10.0);
		sleep(500);
		encoderValueChk(id, curEncoder);
		preEncoder = curEncoder;

		int moveCnt = 0;
		do{

			moveOneMotor(id, ch, -moveDegree);
			sleep(sleepTime);
			encoderValueChk(id, curEncoder);

			chFlag = compareEncoderCHValue(ch, 9.0, preEncoder, curEncoder );

			if(chFlag){
				if(ch == CH1){
					lowEncoder.CH1VALUE = curEncoder.CH1VALUE;
				}else if(ch == CH2){
					lowEncoder.CH2VALUE = curEncoder.CH2VALUE;
				}
			}

			preEncoder = curEncoder;
			moveCnt++;
		}while(chFlag == false);

		moveOneMotor(id, ch, moveCnt*moveDegree);
		sleep(500);
}

void MeroFaceDriver::chkLimitMotor1512All()
{
	motorOff(SIXTH);
	motorOff(THIRD);
	motorOff(FOURTH);
	motorOff(FIFTH);

	sleep(500);

	motorOn(SIXTH);
	motorOn(THIRD);
	motorOn(FOURTH);
	motorOn(FIFTH);

	motorBoardValueReset(SIXTH);
	motorBoardValueReset(THIRD);
	motorBoardValueReset(FOURTH);
	motorBoardValueReset(FIFTH);

	double degree = 170.0;
	chkMotorLimitModiBoardMotor1512(SIXTH, degree);
	chkMotorLimitModiBoardMotor1512(THIRD, degree);
	chkMotorLimitModiBoardMotor1512(FOURTH, degree);
	chkMotorLimitModiBoardMotor1512(FIFTH, degree);
}

void MeroFaceDriver::chkLimitMotor2619All()
{
	motorOff(SECOND);
	motorOff(FIRST);

	sleep(500);

	motorOn(SECOND);
	motorOn(FIRST);

	motorBoardValueReset(SECOND);
	motorBoardValueReset(FIRST);

	chkMotorLimitLipUL();
	chkLipLimitLR();
}

void MeroFaceDriver::initFace()
{
	chkLimitMotor1512All();
	chkLimitMotor2619All();
	startFaceThread();
}



void MeroFaceDriver::moveBoardMotorinThread( MOTOR::BOARD_ID id, queue<CH_Degree>& CH1Queue, queue<CH_Degree>& CH2Queue, Encoder &boardEncoder, double& ch1Degree, double& ch2Degree, int& ch1speed, int& ch2speed )
{
	int periodIdleTime = 0;

	if(!CH1Queue.empty() || !CH2Queue.empty()){

		chkQueue(CH1Queue, ch1Degree, ch1speed);
		chkQueue(CH2Queue, ch2Degree, ch2speed);

		if(ch1speed == -1 || ch2speed == -1 ){
			moveAbsfunc(true, id, boardEncoder, ch1Degree,ch2Degree);
			//Sleep(timeInterval);

		}else{
			setMotorSpeed(id,ch1speed, ch2speed);
			//Sleep(timeInterval);
			//string result = "";
			//result = writeToMotorwithAck(id, "SS?");
			//cout << "Result: " << result << endl;
			//cout <<"ID: "<< id << " CH1D: " << ch1Degree << " CH2D: "  << ch2Degree << endl;
			moveAbsfunc(false, id, boardEncoder, ch1Degree,ch2Degree);
			//Sleep(timeInterval);
		}
	}else{
		sleep(periodIdleTime);
	}
}


void MeroFaceDriver::chkQueue( queue<CH_Degree> &CHQueue, double &chDegree, int &speed )
{
	if(!CHQueue.empty()){
		while(CHQueue.size() >1){
			//cout << "############################################"<< endl;
			//CH1_CH2_Degree tempD = boardQueue.front();
			//cout <<"ID: " << id <<" Qsize: " << boardQueue.size() <<" LRD: " << tempD.CH1Degree << " UDD: " << tempD.CH2Degree << endl;
			//cout << "############################################"<< endl;
			CHQueue.pop();
		}

		CH_Degree tmpValue = CHQueue.front();
		chDegree = tmpValue.ChDegree;
		speed = tmpValue.speed;

		if(!CHQueue.empty()){
			CHQueue.pop();
		}
	}
}



string MeroFaceDriver::motorIDToString(MOTOR::BOARD_ID ID)
{
	stringstream ssID;
	int idi = ID;
	ssID << ID;
	return ssID.str();
}


Encoder MeroFaceDriver::Board1Enc()
{
	return board1Enc;
}

void MeroFaceDriver::Board1Enc(Encoder val)
{
	board1Enc = val;
}

Encoder MeroFaceDriver::Board2Enc()
{
	return board2Enc;
}

void MeroFaceDriver::Board2Enc(Encoder val)
{
	board2Enc = val;
}

Encoder MeroFaceDriver::Board3Enc()
{
	return board3Enc;
}

void MeroFaceDriver::Board3Enc(Encoder val)
{
	board3Enc = val;
}

Encoder MeroFaceDriver::Board4Enc()
{
	return board4Enc;
}

void MeroFaceDriver::Board4Enc(Encoder val)
{
	board4Enc = val;
}

Encoder MeroFaceDriver::Board5Enc()
{
	return board5Enc;
}

void MeroFaceDriver::Board5Enc(Encoder val)
{
	board5Enc = val;
}

Encoder MeroFaceDriver::Board6Enc()
{
	return board6Enc;
}

void MeroFaceDriver::Board6Enc(Encoder val)
{
	board6Enc = val;
}



} /* namespace driver */
} /* namespace mero */
} /* namespace reactive */
