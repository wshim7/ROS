#include "ERobotCore.h"
#include <time.h>
#include <roscir/env/Config.h>
#include <fstream>
#include <algorithm>
//#include <mmsystem.h>
#include <device/idif/gyro/GyroServer.h>

using namespace reactive::erobot::core;

ofstream ecfp;
pthread_mutex_t ERobotCore::__comunicate_mutex =  PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP;
pthread_mutex_t ERobotCore::__body_mutex =  PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP;
pthread_mutex_t ERobotCore::__sensor_mutex =  PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP;

ERobotCore::ERobotCore() {
	ecfp.open("C:/opt/device_erobot_core.log");
//	m_nTimerID = timeSetEvent(1,0,TimeProc,(DWORD)0, TIME_PERIODIC);
	_ISEND = false;
	_isDeltaMove = false;
	_isLedUpdate = false;
	_isArmUpdate = false;
	_isPantiltUpdate = false;

	isTouchErrorChecking = false;
	isErrorCheckEnd = false;
	isGyroError = false;
	isUltraError = false;

//	InitializeCriticalSection(&_comunicate);
//	InitializeCriticalSection(&_body_comunicate);
//	InitializeCriticalSection(&_sensor_comunicate);

	_baseConnection = new ERobotSerialConnector();
	_bodyConnection = new ERobotSerialConnector();
	_sensorConnection  = new ERobotSerialConnector();
	_etcConnection = new ERobotSerialConnector();

	CConfig* config = CConfig::getInstance();
	string baseComPort = config->getParamValue("E-ROBOT_COM_PORT_BASE");
	string bodyComPort = config->getParamValue("E-ROBOT_COM_PORT_BODY");
	string sensorComPort = config->getParamValue("E-ROBOT_COM_PORT_SENSOR");
	string etcComPort = config->getParamValue("E-ROBOT_COM_PORT_TOUCH_LED");

	cout<<"baseComPort name :"<<baseComPort<<endl;


	_baseConnection->setup(baseComPort, EROBOT_SERIAL_BAUDRATE);
	_bodyConnection->setup(bodyComPort, EROBOT_SERIAL_BAUDRATE);
	_sensorConnection->setup(sensorComPort, EROBOT_SERIAL_BAUDRATE);
	_etcConnection->setup(etcComPort, EROBOT_SERIAL_BAUDRATE);

	_baseConnection->resetConnection();
	_bodyConnection->resetConnection();
	_sensorConnection->resetConnection();
	_etcConnection->resetConnection();

	_wheel_encoder_core = new EWheelEncoderCore();
	_ultrasonic_core	= new EUltraCore();
	_psd_core			= new EPSDCore();
	_touch_core			= new ETouchCore();
	_wheel_core			= new EWheelCore();
	_arm_core			= new EArmCore();
	_pantilt_core		= new EPantiltCore();
	_led_core			= new ELEDCore();
	_battery_core		= new EBatteryCore();

//	int isOffset = config->getParamValueInt("IS_ARM_OFFSET");
//	if(isOffset == 1) {
//		short offsets[6] = {0,0,0,0,0,0};
//		offsets[0] = (short)config->getParamValueInt("ARM_OFFSET_0");
//		offsets[1] = (short)config->getParamValueInt("ARM_OFFSET_1");
//		offsets[2] = (short)config->getParamValueInt("ARM_OFFSET_2");
//		offsets[3] = (short)config->getParamValueInt("ARM_OFFSET_3");
//		offsets[4] = (short)config->getParamValueInt("ARM_OFFSET_4");
//		offsets[5] = (short)config->getParamValueInt("ARM_OFFSET_5");
//		short speeds[6] = {0,0,0,0,0,0};
//
//		unsigned char command = EROBOT_COMMAND_ARM_SET_OFFSET;
//		_arm_core->setArmValue(command, offsets, speeds);
//		_updateArm();
//	}

	this->_deltaPublisher = _nodehandle.advertise<cir_msgs::Device_Wheel_Msg>("/DeviceNode/Wheel/response", 1000);
}

ERobotCore::~ERobotCore() {
	delete _baseConnection;
	delete _bodyConnection;
	delete _sensorConnection;
	delete _etcConnection;

	delete _wheel_encoder_core;
	delete _ultrasonic_core;
	delete _psd_core;
	delete _touch_core;
	delete _wheel_core;
	delete _arm_core;
	delete _pantilt_core;
	delete _led_core;
	delete _battery_core;
}

ERobotCore* ERobotCore::getInstance() {
	static ERobotCore instance;
	return &instance;
}

void ERobotCore::checkMotorError() {
/*	ROS_INFO("Start Silbot3 Device Motor Error Check");
	// arm check

	int serverDeviceType = CConfig::getInstance()->getParamValueInt("SERVER_DEVICE_TYPE");
	if(serverDeviceType == 6) {
		return;
	}
//	errorDetectingArm(short errorCode[6]);

	ROS_INFO("Start Arm Motor Error Check");
	int errorCount = 0;
	short armErrorCode[6] = {-1,-1,-1,-1,-1,-1};
	while(armErrorCode[0] == -1) {
		errorDetectingArm(armErrorCode);
		if(armErrorCode[0] == -1) {
			errorCount++;
			ros::Duration(0.2).sleep();
		}
		if(errorCount > 10) {
			ROS_WARN("Body Serial Connection Error occured");
			boost::thread( &ERobotCore::viewMessageBox, this, "Body Serial Connection Error have Some Error. Please Check Serial Connection", "Body Serial Connection Error" );
			break;
		}
	}

	if(errorCount <= 10) {
		bool isArmError = false;
		for(int i=0; i<6; i++) {
			if(armErrorCode[i] != 0) {
				isArmError = true;
			}
		}
		if(isArmError) {
			ROS_WARN("Arm Motors have Some Error. Please Run Self Diagnosis Application");
			boost::thread( &ERobotCore::viewMessageBox, this, "Arm Motors have Some Error. Please Run Self Diagnosis Application", "Arm Motors Error Check");
		} else {
			ROS_INFO("Arm Motors have No Error");
		}
	}

	// pantilt check
//	void errorDetectingPantilt(short errorCode[3]);
	ROS_INFO("Start Pantilt Motor Error Check");
	errorCount = 0;
	short pantiltErrorCode[3] = {-1,-1,-1};
	while(pantiltErrorCode[0] == -1) {
		errorDetectingPantilt(pantiltErrorCode);
		ROS_INFO("pantiltErrorCode[0] : %d", pantiltErrorCode[0]);
		if(pantiltErrorCode[0] == -1) {
			ros::Duration(0.2).sleep();
			errorCount++;
		}
		if(errorCount > 10) {
			ROS_WARN("Body Serial Connection Error occured");
			boost::thread( &ERobotCore::viewMessageBox, this, "Body Serial Connection Error have Some Error. Please Check Serial Connection", "Body Serial Connection Error");
			break;
		}
	}
	if(errorCount <= 10) {
		bool isPantiltError = false;
		for(int i=0; i<3; i++) {
			if(pantiltErrorCode[i] != 0) {
				isPantiltError = true;
			}
		}
		if(isPantiltError) {
			ROS_WARN("Pantilt Motors have Some Error. Please Run Self Diagnosis Application");
			boost::thread( &ERobotCore::viewMessageBox, this, "Pantilt Motors have Some Error. Please Run Self Diagnosis Application", "Pantilt Motors Error Check");
		} else {
			ROS_INFO("Pantilt Motors have No Error");
		}
	}

	isUltraError = true;
	isGyroError = true;

	isErrorCheckEnd = false;

	bool isWheelError = false;
	// wheel check
	short wheelErrorCode[9] = {-1,-1,-1,-1,-1,-1,-1,-1,-1};

	int bootCheckType = CConfig::getInstance()->getParamValueInt("CHECK_MOTOR_TYPE");
	if(bootCheckType != 1) {
		selfDiagnosisWheelNoMove(wheelErrorCode);
	} else {
//		MessageBox( 0, "Robot will start moving. Please disconnect charge and keep away.", "Robot Move Start", 0 );
		boost::thread( &ERobotCore::_checkUltrasonicGyroError, this );
		ROS_INFO("Start Wheel Motor Move and Error Check");
		selfDiagnosisWheel(wheelErrorCode);
	}


	isErrorCheckEnd = true;

	if(wheelErrorCode[0] == -1) {
		ROS_WARN("Mobile Base Serial Connection Error occured");
		boost::thread( &ERobotCore::viewMessageBox, this, "Mobile Base Serial Connection Error have Some Error. Please Check Serial Connection", "Mobile Base Serial Connection Error");
	} else {

		if(wheelErrorCode[0] != 0) {
			isWheelError = true;
		}

		if(isWheelError) {
			ROS_WARN("Wheel Motors have Some Error. Please Run Self Diagnosis Application");
			boost::thread( &ERobotCore::viewMessageBox, this, "Wheel Motors have Some Error. Please Run Self Diagnosis Application", "Wheel Motors Error Check");
		} else {
			ROS_INFO("Wheel Motors have No Error");
		}
	}
*/
}

void ERobotCore::_checkWheelErrorTimeover() {
/*
	ros::Duration(30).sleep();
	if(!isErrorCheckEnd) {
		isErrorCheckEnd = true;
		_baseConnection->resetConnection();
	}
*/
}

void ERobotCore::_checkUltrasonicGyroError() {
	ROS_INFO("Start Ultrasonic Gyro Sensor Error Check");
	CGyroERobot::getInstance();
	ros::Duration(3).sleep();
	bool ultraChangeCheckArray[8];
	bool gyroChangeCheck = false;

	unsigned short ultraData[8];
	unsigned short oldUltraData[8];
	for(int i=0; i<8; i++) {
		ultraChangeCheckArray[i] = false;
		ultraData[i] = -999;
		oldUltraData[i] = -999;
	}

	int readPacketSize				= 13;  // ultra
	int sendPacketSize				= 5;

	unsigned char* sendPacket		= new unsigned char[sendPacketSize];
	unsigned char* receivePacket	= new unsigned char[readPacketSize];

	CGyroData gyroData(0,0);

	double gyroAngle, oldGyroAngle;
	oldGyroAngle = -999.99;
	while(!isErrorCheckEnd) {
		memset(sendPacket, 0x00, sendPacketSize);
		_ultrasonic_core->addUltrsonicCommandPacket( EROBOT_COMMAND_ULTRASONIC_GET_DATA, sendPacket, 0);
		_sensorConnection->writeBytes( sendPacket, sendPacketSize );

		int readSize = _sensorConnection->readBytes(receivePacket,readPacketSize);
		if( readSize < readPacketSize) {
			ros::Duration(0.1).sleep();
			continue;
		}
		if(_ultrasonic_core->isUltrasonicPacket(receivePacket,0)) {
			int ultraReadPacketSize	= ERobotFunctionFactory::getInstance()->getReadPacketSize(EROBOT_TYPE_ULTRASONIC);
			if(RETURN_SUCCESS == _ultrasonic_core->parseAndSetUltrsonicDataPacket(ultraReadPacketSize, receivePacket, 0)) {

			}
		} else {
//			cout << "fail : [_updateSensor] broken or checksum error" << endl;
			_sensorConnection->resetConnection();
			ros::Duration(0.1).sleep();
		}

		_ultrasonic_core->getUltrasonicValue(ultraData, 8);
		if(oldUltraData[0] != -999) {
			for(int i=0; i<8; i++) {
				if(oldUltraData[i] != ultraData[i]) {
					ultraChangeCheckArray[i] = true;
				}
			}

			bool allClear = true;
			for(int i=0; i<8; i++) {
				if(!ultraChangeCheckArray[i]) {
					allClear = false;
				}
			}
			if(allClear) {
				isUltraError = false;
			}

		} else {
			for(int i=0; i<8; i++) {
				oldUltraData[i] = ultraData[i];
			}
		}

		gyroData = CGyroERobot::getInstance()->readData();
		gyroAngle = gyroData.getAngle();
		if(oldGyroAngle != -999.99) {
			if(oldGyroAngle - gyroAngle < -0.5 || oldGyroAngle - gyroAngle > 0.5) {
				isGyroError = false;
			}
			oldGyroAngle = gyroAngle;
		} else {
			oldGyroAngle = gyroAngle;
		}

		if(!isGyroError && !isUltraError) {
			break;
		}
		ros::Duration(0.1).sleep();
	}

	if(isUltraError) {
		ROS_WARN("Ultrasonic Sensors have Some Error. Please Run Self Diagnosis Application");
		viewMessageBox("Ultrasonic Sensors have Some Error. Please Run Self Diagnosis Application", "Ultrasonic Sensors Error Check");
	} else {
		ROS_INFO("Ultrasonic Sensors have No Error");
	}
	if(isGyroError) {
		ROS_WARN("Gyro Sensor has Some Error. Please Run Self Diagnosis Application");
		viewMessageBox("Gyro Sensor have Some Error. Please Run Self Diagnosis Application", "Gyro Sensor Error Check");
	} else {
		ROS_INFO("Gyro Sensor has No Error");
	}
}

void ERobotCore::viewMessageBox(const char* message, const char* title) {
//	MessageBox( 0, message, title, 0 );
}

void ERobotCore::initERobotCore() {

	ROS_DEBUG("init Erobot core start");
	boost::thread( &ERobotCore::_updateBase, this );
	boost::thread( &ERobotCore::_updateSensor, this );
	boost::thread( &ERobotCore::_updateEtc, this );
	boost::thread( &ERobotCore::_updateBody, this );

	int motorCheck = CConfig::getInstance()->getParamValueInt( "CHECK_MOTOR_ERROR" );
	if(motorCheck == 1) {
		boost::thread( &ERobotCore::_updateMotorError, this );
	}

	ROS_DEBUG("init Erobot core stop");
//	boost::thread( &ERobotCore::_updateBodyPosition, this );
}

void ERobotCore::_updateMotorError() {
	ROS_INFO("Start Silbot3 Device Update Motor Error");
	// arm check

	CConfig* config = CConfig::getInstance();
	int serverDeviceType = config->getParamValueInt("SERVER_DEVICE_TYPE");
	double updatePeriod = config->getParamValueDouble("UPDATE_ERROR_CHECK_PERIOD");
		if(updatePeriod == -1 || updatePeriod == 0 ) {
			updatePeriod = 60;
		}
		ROS_INFO("UPDATE_ERROR_CHECK_PERIOD : %f", updatePeriod);

	while(!_ISEND && serverDeviceType != 6 /* mock mode*/) {
		ros::Duration(updatePeriod).sleep();

		if(!_isArmUpdate && !_isPantiltUpdate) {
			ROS_DEBUG("Start Arm Motor Error Check");
			int errorCount = 0;
			short armErrorCode[6] = {-1,-1,-1,-1,-1,-1};
			while(armErrorCode[0] == -1) {
				errorDetectingArm(armErrorCode);
				if(armErrorCode[0] == -1) {
					errorCount++;
					ros::Duration(0.2).sleep();
				}
				if(errorCount > 10) {
					ROS_WARN("Body Serial Connection Error occured");
					boost::thread( &ERobotCore::viewMessageBox, this, "Body Serial Connection Error have Some Error. Please Check Serial Connection", "Body Serial Connection Error");
//					MessageBox( 0, "Body Serial Connection Error have Some Error. Please Check Serial Connection", "Body Serial Connection Error", 0 );
					break;
				}
			}

			if(errorCount <= 10) {
				bool isArmError = false;
				for(int i=0; i<6; i++) {
					if(armErrorCode[i] != 0) {
						isArmError = true;
					}
				}
				if(isArmError) {
					ROS_WARN("Arm Motors have Some Error. Please Run Self Diagnosis Application");
					boost::thread( &ERobotCore::viewMessageBox, this, "Arm Motors have Some Error. Please Run Self Diagnosis Application", "Arm Motors Error Check");
//					MessageBox( 0, "Arm Motors have Some Error. Please Run Self Diagnosis Application", "Arm Motors Error Check", 0 );
				} else {
					ROS_DEBUG("Arm Motors have No Error");
				}
			}

			// pantilt check
			//	void errorDetectingPantilt(short errorCode[3]);
			ROS_DEBUG("Start Pantilt Motor Error Check");
			errorCount = 0;
			short pantiltErrorCode[3] = {-1,-1,-1};
			while(pantiltErrorCode[0] == -1) {
				errorDetectingPantilt(pantiltErrorCode);
//				ROS_INFO("pantiltErrorCode[0] : %d", pantiltErrorCode[0]);
				if(pantiltErrorCode[0] == -1) {
					ros::Duration(0.2).sleep();
					errorCount++;
				}
				if(errorCount > 10) {
					ROS_WARN("Body Serial Connection Error occured");
					boost::thread( &ERobotCore::viewMessageBox, this, "Body Serial Connection Error have Some Error. Please Check Serial Connection", "Body Serial Connection Error");
//					MessageBox( 0, "Body Serial Connection Error have Some Error. Please Check Serial Connection", "Body Serial Connection Error", 0 );
					break;
				}
			}
			if(errorCount <= 10) {
				bool isPantiltError = false;
				for(int i=0; i<3; i++) {
					if(pantiltErrorCode[i] != 0) {
						isPantiltError = true;
					}
				}
				if(isPantiltError) {
					ROS_WARN("Pantilt Motors have Some Error. Please Run Self Diagnosis Application");
					boost::thread( &ERobotCore::viewMessageBox, this, "Pantilt Motors have Some Error. Please Run Self Diagnosis Application", "Pantilt Motors Error Check");
//					MessageBox( 0, "Pantilt Motors have Some Error. Please Run Self Diagnosis Application", "Pantilt Motors Error Check", 0 );
				} else {
					ROS_DEBUG("Pantilt Motors have No Error");
				}
			}
		}

		bool isWheelError = false;
		// wheel check
		short wheelErrorCode[9] = {-1,-1,-1,-1,-1,-1,-1,-1,-1};

		//	void selfDiagnosisWheel(short errorCode[9]);
//		boost::thread( &ERobotCore::_checkUltrasonicGyroError, this );
		selfDiagnosisWheelNoMove(wheelErrorCode);

		if(wheelErrorCode[0] == -1) {
			ROS_WARN("Mobile Base Serial Connection Error occured");
			boost::thread( &ERobotCore::viewMessageBox, this, "Mobile Base Serial Connection Error have Some Error. Please Check Serial Connection", "Mobile Base Serial Connection Error");
		} else {

			if(wheelErrorCode[0] != 0) {
				isWheelError = true;
			}

			if(isWheelError) {
				ROS_WARN("Wheel Motors have Some Error. Please Run Self Diagnosis Application");
				boost::thread( &ERobotCore::viewMessageBox, this, "Wheel Motors have Some Error. Please Run Self Diagnosis Application", "Wheel Motors Error Check");
			} else {
				ROS_DEBUG("Wheel Motors have No Error");
			}
		}

	}

}


//void CALLBACK ERobotCore::TimeProc( UINT m_nTimerID, UINT uiMsg, DWORD dwUser, DWORD dw1, DWORD d2 )
//{
//}

void ERobotCore::run() {
	ros::Duration(0.2).sleep();
//	int i=0;
//
//	CConfig* config = CConfig::getInstance();
//	int serverDeviceType = config->getParamValueInt("SERVER_DEVICE_TYPE");
//
//	while(!_ISEND && serverDeviceType != 6 /* mock mode*/) {
////		cout << "==================================" << endl;
////		cout<< " main loop !" << endl;
//
//		pthread_mutex_lock( &__comunicate_mutex );
//		_updateBase();
//		pthread_mutex_unlock( &__comunicate_mutex );
////		Sleep(10);
//		pthread_mutex_lock( &__comunicate_mutex );
//		_updateSensor();
//		pthread_mutex_unlock( &__comunicate_mutex );
////		Sleep(10);
////		EnterCriticalSection(&_comunicate);
////		_updateBody();
////		LeaveCriticalSection(&_comunicate);
////		Sleep(10);
//
//		pthread_mutex_lock( &__comunicate_mutex );
//		_updateEtc();
//		pthread_mutex_unlock( &__comunicate_mutex );
////		Sleep(10);
////		cout << "==================================\n\n" << endl;
//	}
}


void ERobotCore::handleBodyMessage() {

}


void ERobotCore::_updateBase() {
	ros::Duration(2).sleep();
	ROS_INFO("ERobotCore::_updateBase start");
	int state			= RETURN_FAILED;
	int indexPoint		= 0;
	int successCount	= 0;
	
	int readPacketSize				= 14+9;  // wheel encoder
	int sendPacketSize				= 17;  // wheel + wheel encoder
//	int sendPacketSize				= 5;  // wheel + wheel encoder
	int deltaPacketSize				= 7;

	CConfig* config = CConfig::getInstance();
	int serverDeviceType = config->getParamValueInt("SERVER_DEVICE_TYPE");

	unsigned char* sendPacket		= new unsigned char[sendPacketSize];
	unsigned char* receivePacket	= new unsigned char[readPacketSize];
	unsigned char* deltaPacket		= new unsigned char[deltaPacketSize];

//	clock_t start, end;
	clock_t bodyEnd, bodyStart;
	bodyEnd = 0;

	while(!_ISEND && serverDeviceType != 6 ) {
//		printf("------- _updateBase -------");
//		start = clock();
		ros::Duration(0.2).sleep();
		//pthread_mutex_lock( &__comunicate_mutex );
		memset(sendPacket, 0x00, sendPacketSize);

		_wheel_encoder_core->addWheelEncoderCommandPacket( EROBOT_COMMAND_WHEELENCODER_GET_DATA, sendPacket, 0);
		_wheel_core->addWheelCommandPacket(sendPacket, (EROBOT_COMMON_HEADER_PACKET_SIZE+EROBOT_CHECKSUM_PACKET_SIZE));

		_baseConnection->writeBytes( sendPacket, sendPacketSize );
		//printf("send packet : ");
		//for(int i=0 ; i<sendPacketSize ; i++) {
		//	printf("%02x ", sendPacket[i]);
		//}
		//printf("\n");
		int temppp = _baseConnection->readBytes(receivePacket,readPacketSize);
		ROS_DEBUG("read size!!! -> %d",temppp);
		if( temppp < readPacketSize) {
			printf("response size is different... [_updateBase] skip!!!!! \n");
			//pthread_mutex_unlock( &__comunicate_mutex );
			_baseConnection->resetConnection();
		} else {
			printf("read packet : ");
			for(int i=0 ; i<readPacketSize ; i++) {
				printf("%02x ", receivePacket[i]);
			}
			printf("\n");
	
			if(_wheel_encoder_core->isWheelEncoderPacket(receivePacket,indexPoint)) {
				int wheelEncoderReadPacketSize	= ERobotFunctionFactory::getInstance()->getReadPacketSize(EROBOT_TYPE_WHEELENCODER);
				if(RETURN_SUCCESS == _wheel_encoder_core->parseAndSetWheelEncoderDataPacket(wheelEncoderReadPacketSize,receivePacket,indexPoint)) {
				//ROS_DEBUG("parse and set");
				}
				//ROS_DEBUG("222222222222");
			} else {
				_baseConnection->resetConnection();
   			}
			
		}
//		end = clock();
//		cout << "11111111 " << end - start << endl;
	}

	delete[] sendPacket;
	delete[] receivePacket;

}

void ERobotCore::_updateBodyPosition() {
	ros::Duration(2).sleep();
	ROS_INFO("ERobotCore::_updateBody start");
	int state			= RETURN_FAILED;
	int indexPoint		= 0;
	int successCount	= 0;
	int loopSize = 2;

	int armSendPacketSize 				= 23;
	int pantiltSendPacketSize			= 14;
	int sendPacketAllSize				= armSendPacketSize+pantiltSendPacketSize; // all


	int sendPacketArmFullSize			= armSendPacketSize+pantiltSendPacketSize+armSendPacketSize;
	int sendPacketPantiltFullSize		= armSendPacketSize+pantiltSendPacketSize+pantiltSendPacketSize;
	int sendPacketAllFullSize			= armSendPacketSize+pantiltSendPacketSize+armSendPacketSize+pantiltSendPacketSize;

	int armReadPacketSize 				= 17;
	int pantiltReadPacketSize			= 11;
	int readPacketSize					= 17+11; // all
	CConfig* config = CConfig::getInstance();

	int serverDeviceType = config->getParamValueInt("SERVER_DEVICE_TYPE");
	double updatePeriod = config->getParamValueDouble("UPDATE_BODY_PERIOD");
	if(updatePeriod == -1 || updatePeriod == 0 ) {
		updatePeriod = 0.098;
	}
	ROS_INFO("UPDATE_BODY_PERIOD : %f", updatePeriod);

	unsigned char* sendAllPacket		= new unsigned char[sendPacketAllSize];
	unsigned char* receivePacket		= new unsigned char[readPacketSize];

	unsigned char* sendAllFullPacket		= new unsigned char[sendPacketAllFullSize];
	unsigned char* sendPantiltFullPacket	= new unsigned char[sendPacketPantiltFullSize];
	unsigned char* sendArmFullPacket		= new unsigned char[sendPacketArmFullSize];

	short armAngles[6]= {0,0,0,0,0,0};
	short armSpeeds[6]= {0,0,0,0,0,0};

//	clock_t start, end, el, el1, el2, el3;

	clock_t tend, tstart;
	tstart = 0;
	while(!_ISEND && serverDeviceType != 6 /* mock mode*/) {
//		start = clock();
		memset(sendAllPacket, 0x00, sendPacketAllSize);
		unsigned char* currentPacket = sendAllPacket;
		int currentSendIndex = 0;
		if(_isArmUpdate && _isPantiltUpdate) {
			memset(sendAllFullPacket, 0x00, sendPacketAllFullSize);
			_arm_core->getArmCommandPacket(sendAllFullPacket);
			_pantilt_core->addPantiltCommandPacket(sendPantiltFullPacket,armSendPacketSize);

			_isArmUpdate = false;
			_isPantiltUpdate = false;
			currentPacket = sendAllFullPacket;
			currentSendIndex = sendPacketAllSize;
		} else if(_isArmUpdate) {
			memset(sendArmFullPacket, 0x00, sendPacketArmFullSize);
			_arm_core->getArmCommandPacket(sendArmFullPacket);
			_isArmUpdate = false;
			currentPacket = sendArmFullPacket;
			currentSendIndex = armSendPacketSize;

			//			printf("\n send packet : ");
			//			for(int i=0 ; i<currentSendIndex ; i++) {
			//				printf("%02x ", sendArmFullPacket[i]);
			//			}
			//			printf("\n");


		} else if(_isPantiltUpdate) {
			memset(sendPantiltFullPacket, 0x00, sendPacketPantiltFullSize);
			_pantilt_core->getPantiltCommandPacket(sendPantiltFullPacket);
			_isPantiltUpdate = false;
			currentPacket = sendPantiltFullPacket;
			currentSendIndex = pantiltSendPacketSize;
		} else {

		}
		//		_arm_core->setArmValue(EROBOT_COMMAND_ARM_GET_POSITION, armAngles, armSpeeds);
		//		_pantilt_core->setPantiltValue(EROBOT_COMMAND_PANTILT_XTION_GET_POSITION, 0,0,0,0,0,0);
		_arm_core->addGetPositionPacket(currentPacket, currentSendIndex);
		_pantilt_core->addGetPositionPacket(currentPacket,currentSendIndex+armSendPacketSize);

		//		printf("\n send packet : ");
		//		for(int i=0 ; i<currentSendIndex+sendPacketAllSize ; i++) {
		//			printf("%02x ", currentPacket[i]);
		//		}
		//		printf("\n");
		_bodyConnection->writeBytes( currentPacket, currentSendIndex+sendPacketAllSize );
		int readSize1 = _bodyConnection->readBytes(receivePacket,readPacketSize);
		if(readSize1 < readPacketSize) {
			//			ROS_ERROR("UPDATE_BODY_POSITION response size is different... %d  <  28[_updateBody] skip!!!!! \n", readSize1);
			//			printf("\n read packet : ");
			//			for(int i=0 ; i<readSize1 ; i++) {
			//				printf("%02x ", receivePacket[i]);
			//			}
			//			printf("\n");

			tend = clock();
			double delay = 0.39;
			if(tstart != 0) {
				delay = updatePeriod - (double)((tstart - tend)/1000);
			}
			ros::Duration(delay).sleep();
			tstart = clock();
			continue;
		}
		//		printf("\n read packet : ");
		//		for(int i=0 ; i<readPacketSize ; i++) {
		//			printf("%02x ", receivePacket[i]);
		//		}
		//		printf("\n");

		indexPoint = 0;
		for(int i=0 ; i<loopSize ; i++) {
			if(_arm_core->isArmPacket(receivePacket,indexPoint)) {
				int armReadPacketSize	= ERobotFunctionFactory::getInstance()->getReadPacketSize(EROBOT_TYPE_ARM);
				if(RETURN_SUCCESS == _arm_core->parseAndSetArmDataPacket(armReadPacketSize, receivePacket, indexPoint)) {
					indexPoint += armReadPacketSize;
					successCount++;
				}
			} else if(_pantilt_core->isPantiltPacket(receivePacket,indexPoint)) {
				if(RETURN_SUCCESS == _pantilt_core->parseAndSetPantiltDataPacket(pantiltReadPacketSize,receivePacket,indexPoint)) {
					indexPoint += pantiltReadPacketSize;
					successCount++;
				}
			} else {
				ROS_ERROR("fail : [_updateBodyPosition] broken or checksum error");
				_bodyConnection->resetConnection();
				ros::Duration(0.1).sleep();
			}
		}

		if(successCount < loopSize) {
			ROS_ERROR("something wrong in [_updateBodyPosition] ");
		}

		tend = clock();
		double delay = 0.39;
		if(tstart != 0) {
			delay = updatePeriod - (double)((tstart - tend)/1000);
		}
		ros::Duration(delay).sleep();
		tstart = clock();

	}
	delete[] sendAllPacket;
	delete[] receivePacket;

}


void ERobotCore::_updateBody() {
	ros::Duration(2).sleep();
	ROS_INFO("ERobotCore::_updateBody start");
	int state			= RETURN_FAILED;
	int indexPoint		= 0;
	int successCount	= 0;
	int loopSize = 2;

	int armSendPacketSize 				= 23;
	int pantiltSendPacketSize			= 14;
	int sendPacketAllSize				= armSendPacketSize+pantiltSendPacketSize; // all


	int sendPacketArmFullSize			= armSendPacketSize;
	int sendPacketPantiltFullSize		= pantiltSendPacketSize;
	int sendPacketAllFullSize			= armSendPacketSize+pantiltSendPacketSize;

	CConfig* config = CConfig::getInstance();

	int serverDeviceType = config->getParamValueInt("SERVER_DEVICE_TYPE");
	double updatePeriod = config->getParamValueDouble("UPDATE_BODY_PERIOD");
	if(updatePeriod == -1 || updatePeriod == 0 ) {
		updatePeriod = 0.098;
	}
	ROS_INFO("UPDATE_BODY_PERIOD : %f", updatePeriod);

	unsigned char* sendAllPacket		= new unsigned char[sendPacketAllSize];

	unsigned char* sendAllFullPacket		= new unsigned char[sendPacketAllFullSize];
	unsigned char* sendPantiltFullPacket	= new unsigned char[sendPacketPantiltFullSize];
	unsigned char* sendArmFullPacket		= new unsigned char[sendPacketArmFullSize];

	short armAngles[6]= {0,0,0,0,0,0};
	short armSpeeds[6]= {0,0,0,0,0,0};

	clock_t tend, tstart;
	tstart = 0;
	int base_count = 0;
	while(!_ISEND && serverDeviceType != 6 /* mock mode*/) {
		pthread_mutex_lock( &__body_mutex );
		if(_isArmUpdate && _isPantiltUpdate) {
//			cout << "1111111111111111111" << endl;


			memset(sendAllFullPacket, 0x00, sendPacketAllFullSize);
			_arm_core->getArmCommandPacket(sendAllFullPacket);
			_pantilt_core->addPantiltCommandPacket(sendAllFullPacket,armSendPacketSize);

			char* buff = new char[10];
			ecfp << base_count++ << " : "<< tstart <<  " : " << endl;
				for(int i=0 ; i<sendPacketAllFullSize ; i++) {
				sprintf(buff, "%02x ", sendAllFullPacket[i]);
				ecfp << buff;
			}
			ecfp << endl;

			_isArmUpdate = false;
			_isPantiltUpdate = false;
			_bodyConnection->writeBytes( sendAllFullPacket, sendPacketAllFullSize );

		} else if(_isArmUpdate) {
//			cout << "222222222222222222222" << endl;
			memset(sendArmFullPacket, 0x00, sendPacketArmFullSize);
			_arm_core->getArmCommandPacket(sendArmFullPacket);
			_isArmUpdate = false;
			_bodyConnection->writeBytes( sendArmFullPacket, sendPacketArmFullSize );
		} else if(_isPantiltUpdate) {
//			cout << "333333333333333333333" << endl;
			memset(sendPantiltFullPacket, 0x00, sendPacketPantiltFullSize);
			_pantilt_core->getPantiltCommandPacket(sendPantiltFullPacket);
			_isPantiltUpdate = false;
			_bodyConnection->writeBytes( sendPantiltFullPacket, sendPacketPantiltFullSize );

		} else {
			ros::Duration(0.1).sleep();
		}

		pthread_mutex_unlock( &__body_mutex );
		tend = clock();
		double delay = updatePeriod;
		if(tstart != 0) {
			delay = updatePeriod - (double)((tstart - tend)/1000);
//			cout << delay << endl;
			//			fp << "delay 1 " <<delay <<endl;
		}
		ros::Duration(delay).sleep();
		tstart = clock();
	}
	delete[] sendAllPacket;
	delete[] sendAllFullPacket;
	delete[] sendPantiltFullPacket;
	delete[] sendArmFullPacket;

}

void ERobotCore::_updateSensor() {
	ros::Duration(2).sleep();
	ROS_INFO("ERobotCore::_updateSensor start");
	int state			= RETURN_FAILED;
	int indexPoint		= 0;
	int successCount	= 0;
	int readSize = 0;

	int readPacketSize				= 13;  // ultra
	int sendPacketSize				= 5;  

	CConfig* config = CConfig::getInstance();
	int serverDeviceType = config->getParamValueInt("SERVER_DEVICE_TYPE");

	unsigned char* sendPacket		= new unsigned char[sendPacketSize];
	unsigned char* receivePacket	= new unsigned char[readPacketSize];
	while(!_ISEND && serverDeviceType != 6 /* mock mode*/) {
//		printf("------- _updateSensor -------");
		memset(sendPacket, 0x00, sendPacketSize);
		indexPoint = 0;
		_ultrasonic_core->addUltrsonicCommandPacket( EROBOT_COMMAND_ULTRASONIC_GET_DATA, sendPacket, indexPoint);
		_sensorConnection->writeBytes( sendPacket, sendPacketSize );

//		printf("\n send packet : ");
//		for(int i=0 ; i<sendPacketSize ; i++) {
//			printf("%02x ", sendPacket[i]);
//		}
		readSize = _sensorConnection->readBytes(receivePacket,readPacketSize);
		if( readSize < readPacketSize) {
//			printf("response size is different... [_updateSensor] skip!!!!!  %d \n", readSize);
			ros::Duration(0.1).sleep();
			continue;
		}
//		printf("\n read packet : ");
//		for(int i=0 ; i<readPacketSize ; i++) {
//			printf("%02x ", receivePacket[i]);
//		}
//		printf("\n");
		if(_ultrasonic_core->isUltrasonicPacket(receivePacket,indexPoint)) {
			int ultraReadPacketSize	= ERobotFunctionFactory::getInstance()->getReadPacketSize(EROBOT_TYPE_ULTRASONIC);
			if(RETURN_SUCCESS == _ultrasonic_core->parseAndSetUltrsonicDataPacket(ultraReadPacketSize, receivePacket, indexPoint)) {
				indexPoint += ultraReadPacketSize;
				successCount++;
			}
		} else {
			cout << "fail : [_updateSensor] broken or checksum error" << endl;
			_sensorConnection->resetConnection();
		}

		ros::Duration(0.1).sleep();
	}
	delete[] sendPacket;
	delete[] receivePacket;
}

void ERobotCore::_updateEtc() {
	ros::Duration(2).sleep();
	ROS_INFO("ERobotCore::_updateEtc start");
	int state			= RETURN_FAILED;
	int indexPoint		= 0;
	int successCount	= 0;
	int readSize = 0;
	int loopSize = 2;

	int ledSize = 15;
	unsigned char* ledPacket		= new unsigned char[ledSize];

	_led_core->setLEDValue(0xF2, 0, 0, 0, 0);
	_led_core->addLEDCommandPacket( ledPacket, 0);
	_etcConnection->writeBytes( ledPacket, ledSize );

	ros::Duration(1.5).sleep();

	_led_core->setLEDValue(0xF5, 0, 0, 0, 0);
	_led_core->addLEDCommandPacket( ledPacket, 0);
	_etcConnection->writeBytes( ledPacket, ledSize );

	int readPacketSize				= 10+8;  // touch + battery
	int sendPacketSize				= 5+5;  // touch + + battery
	int sendAllPacketSize			= 15+5+5; // touch + led + battery

	CConfig* config = CConfig::getInstance();
	int serverDeviceType = config->getParamValueInt("SERVER_DEVICE_TYPE");

	unsigned char* sendPacket		= new unsigned char[sendPacketSize];
	unsigned char* sendAllPacket	= new unsigned char[sendAllPacketSize];
	unsigned char* receivePacket	= new unsigned char[readPacketSize];
	while(!_ISEND && serverDeviceType != 6 /* mock mode*/) {
		if(!isTouchErrorChecking) {
			pthread_mutex_lock( &__sensor_mutex );
			//		printf("------- _updateEtc -------");
			memset(receivePacket, 0x00, readPacketSize);

			if(_isLedUpdate) {
				memset(sendAllPacket, 0x00, sendAllPacketSize);
				indexPoint = 0;
				successCount = 0;
				_touch_core->addTouchButtonCommandPacket( EROBOT_COMMAND_TOUCHBUTTON_GET_DATA, sendAllPacket, 0);
				_led_core->addLEDCommandPacket( sendAllPacket, 5);
				_battery_core->addBatteryCommandPacket(EROBOT_COMMAND_BATTERY_GET_DATA,sendAllPacket,20);

				//		printf("\n send packet : ");
				//		for(int i=0 ; i<sendPacketSize ; i++) {
				//			printf("%02x ", sendPacket[i]);
				//		}

				_etcConnection->writeBytes( sendAllPacket, sendAllPacketSize );
				_isLedUpdate = false;
			} else {
				memset(sendPacket, 0x00, sendPacketSize);
				indexPoint = 0;
				successCount = 0;
				_touch_core->addTouchButtonCommandPacket( EROBOT_COMMAND_TOUCHBUTTON_GET_DATA, sendPacket, 0);
				_battery_core->addBatteryCommandPacket(EROBOT_COMMAND_BATTERY_GET_DATA,sendPacket,5);

				//		printf("\n send packet : ");
				//		for(int i=0 ; i<sendPacketSize ; i++) {
				//			printf("%02x ", sendPacket[i]);
				//		}

				_etcConnection->writeBytes( sendPacket, sendPacketSize );
			}


			readSize = _etcConnection->readBytes(receivePacket,readPacketSize);

			if( readSize < readPacketSize) {
				//			printf("response size is different... [_updateEtc] skip!!!!!  %d \n", readSize);
				_etcConnection->resetConnection();
				pthread_mutex_unlock( &__sensor_mutex );
				ros::Duration(0.2).sleep();
				continue;
			}

			//		printf("\n read packet : ");
			//		for(int i=0 ; i<readSize ; i++) {
			//			printf("%02x ", receivePacket[i]);
			//		}
			//		printf("\n");

			for(int i=0 ; i<loopSize ; i++) {
				if(_touch_core->isTouchButtonPacket(receivePacket,indexPoint)) {
					int touchReadPacketSize	= ERobotFunctionFactory::getInstance()->getReadPacketSize(EROBOT_TYPE_TOUCHBUTTON);
					if(RETURN_SUCCESS == _touch_core->parseAndSetTouchButtonDataPacket(touchReadPacketSize, receivePacket, indexPoint)) {
						indexPoint += touchReadPacketSize;
						successCount++;
					}
				} else if(_battery_core->isBatteryPacket(receivePacket,indexPoint)) {
					int batteryReadPacketSize = 8;
					if(RETURN_SUCCESS == _battery_core->parseAndSetBatteryDataPacket(batteryReadPacketSize,receivePacket,indexPoint)) {
						indexPoint += batteryReadPacketSize;
						successCount++;
					}
				} else {
					//				cout << "fail : [_updateEtc] broken or checksum error" << endl;
					_etcConnection->resetConnection();
					ros::Duration(0.2).sleep();
				}
			}

			if(successCount < loopSize) {
				cout << "something wrong in [_updateEtc] " << endl;
			}
			pthread_mutex_unlock( &__sensor_mutex );
		}
		ros::Duration(0.15).sleep();
	}
	delete[] sendPacket;
	delete[] receivePacket;

}

void ERobotCore::_updateWheelEncoder() {	
/*	int state = RETURN_FAILED;
	
	int readDataSize = ERobotFunctionFactory::getInstance()->getReadPacketSize(EROBOT_TYPE_WHEELENCODER);
	unsigned char* sendPacket = new unsigned char[EROBOT_COMMON_HEADER_PACKET_SIZE + EROBOT_CHECKSUM_PACKET_SIZE];
	unsigned char* receivePacket = new unsigned char[readDataSize];

	_wheel_encoder_core->getWheelEncoderCommandPacket( EROBOT_COMMAND_WHEELENCODER_GET_POSITION, sendPacket);
	while(state==RETURN_FAILED) {
		pthread_mutex_lock( &__comunicate_mutex );
		_baseConnection->writeBytes( sendPacket, EROBOT_COMMON_HEADER_PACKET_SIZE+EROBOT_CHECKSUM_PACKET_SIZE );
		ros::Duration(0.05).sleep();
		_baseConnection->readBytes(receivePacket,readDataSize);
		pthread_mutex_unlock( &__comunicate_mutex );
		state = _wheel_encoder_core->parseAndSetWheelEncoderDataPacket(readDataSize,receivePacket);
		if(state == RETURN_FAILED) {
			_baseConnection->resetConnection();
		}
	}
	delete[] sendPacket;
	delete[] receivePacket; */
}

void ERobotCore::_updateUltrasonic() {

	pthread_mutex_lock( &__sensor_mutex );
	unsigned char* sendPacket = new unsigned char[5];
	unsigned char* receivePacket = new unsigned char[13];
	sendPacket[0] = 0x05;
	sendPacket[1] = 0xF5;
	sendPacket[2] = 0xF5;
	sendPacket[3] = 0xF5;
	sendPacket[4] = 0x0A;

	_baseConnection->writeBytes( sendPacket, 5 );	
	ros::Duration(0.05).sleep();
	_baseConnection->readBytes(receivePacket,13);

//	printf("readByte : " );
//	for(int i=0 ; i<13 ; i++) {
//		printf("%02x ", receivePacket[i]);
//	}
//	printf("\n");
	pthread_mutex_unlock( &__sensor_mutex );

	delete[] sendPacket;
	delete[] receivePacket;
}

void ERobotCore::_updatePSD() {
	int state = RETURN_FAILED;
	
	int readDataSize = ERobotFunctionFactory::getInstance()->getReadPacketSize(EROBOT_TYPE_PSD);
	unsigned char* sendPacket = new unsigned char[EROBOT_COMMON_HEADER_PACKET_SIZE + EROBOT_CHECKSUM_PACKET_SIZE];
	unsigned char* receivePacket = new unsigned char[readDataSize];

	_psd_core->getPSDCommandPacket(EROBOT_COMMAND_PSD_GET_DATA, sendPacket);
	while(state==RETURN_FAILED) {
		pthread_mutex_lock( &__sensor_mutex );
		_baseConnection->writeBytes( sendPacket, EROBOT_COMMON_HEADER_PACKET_SIZE+EROBOT_CHECKSUM_PACKET_SIZE );
		ros::Duration(0.05).sleep();
		_baseConnection->readBytes(receivePacket,readDataSize);
		pthread_mutex_unlock( &__sensor_mutex );
		state = _psd_core->parseAndSetPSDDataPacket(readDataSize,receivePacket);
		if(state == RETURN_FAILED) {
			_baseConnection->resetConnection();
		}
	}
	delete[] sendPacket;
	delete[] receivePacket;
}

void ERobotCore::_updateTouchButton() {
	int state = RETURN_FAILED;
	
	int readDataSize = ERobotFunctionFactory::getInstance()->getReadPacketSize(EROBOT_TYPE_TOUCHBUTTON);
	unsigned char* sendPacket = new unsigned char[EROBOT_COMMON_HEADER_PACKET_SIZE + EROBOT_CHECKSUM_PACKET_SIZE];
	unsigned char* receivePacket = new unsigned char[readDataSize];

	_touch_core->getTouchButtonCommandPacket(EROBOT_COMMAND_TOUCHBUTTON_GET_DATA, sendPacket);
	_etcConnection->writeBytes( sendPacket, 5 );

	int readSize = _etcConnection->readBytes(receivePacket,readDataSize);
	if( readSize < readDataSize) {
//		printf("response size is different... [_updateEtc] skip!!!!!  %d \n", readSize);
		return;
	}

	if(_touch_core->isTouchButtonPacket(receivePacket,0)) {
		int touchReadPacketSize	= ERobotFunctionFactory::getInstance()->getReadPacketSize(EROBOT_TYPE_TOUCHBUTTON);
		if(RETURN_SUCCESS == _touch_core->parseAndSetTouchButtonDataPacket(touchReadPacketSize, receivePacket)) {
			
		}
	} 
	delete[] sendPacket;
	delete[] receivePacket;
}

void ERobotCore::_updateLED() {
	
	int sendPacketSize				= 15;  
	unsigned char* sendPacket		= new unsigned char[sendPacketSize];
	
	memset(sendPacket, 0x00, sendPacketSize);

	_led_core->getLEDCommandPacket( sendPacket);	
	_etcConnection->writeBytes( sendPacket, sendPacketSize );

//	ROS_DEBUG("\n _updateLED send packet : ");
//	for(int i=0 ; i<sendPacketSize ; i++) {
//		ROS_DEBUG("%02x ", sendPacket[i]);
//	}
//	ROS_DEBUG("\n");


	delete[] sendPacket;
}

void ERobotCore::_updateWheel() {
/*	int state = RETURN_FAILED;
	
	int readDataSize = ERobotFunctionFactory::getInstance()->getReadPacketSize(EROBOT_TYPE_WHEEL);
	unsigned char* sendPacket = new unsigned char[EROBOT_COMMON_HEADER_PACKET_SIZE + EROBOT_WHEEL_DATA_PACKET_SIZE + EROBOT_CHECKSUM_PACKET_SIZE];
	unsigned char* receivePacket = new unsigned char[readDataSize];

	_wheel_core->getWheelCommandPacket(sendPacket);
	pthread_mutex_lock( &__comunicate_mutex );
	_baseConnection->writeBytes( sendPacket, EROBOT_COMMON_HEADER_PACKET_SIZE+EROBOT_WHEEL_DATA_PACKET_SIZE+EROBOT_CHECKSUM_PACKET_SIZE );
	ros::Duration(0.01).sleep();
	_baseConnection->readBytes(receivePacket,readDataSize);
	pthread_mutex_unlock( &__comunicate_mutex );
	state = _wheel_core->parseAndSetWheelDataPacket(readDataSize,receivePacket);

	if(state == RETURN_FAILED) {
		_baseConnection->resetConnection();
		//printf("[_updateWheel] call connection reset !!!! \n");
	}
	delete[] sendPacket;
	delete[] receivePacket;  */
}


void ERobotCore::_updateArm() {
	ros::Duration(2).sleep();
	_isArmUpdate = false;
	CConfig* config = CConfig::getInstance();
	int serverDeviceType = config->getParamValueInt("SERVER_DEVICE_TYPE");
	double updateArmPeriod = config->getParamValueDouble("UPDATE_ARM_PERIOD");
	if(updateArmPeriod == -1 || updateArmPeriod == 0 ) {
		updateArmPeriod = 0.1;
	}
	ROS_INFO("ERobotCore::_updateArm start period %f" , updateArmPeriod);
	int sendPacketSize				= 23;
	unsigned char* sendPacket		= new unsigned char[sendPacketSize];
	while(!_ISEND && serverDeviceType != 6 /* mock mode*/) {
		if(_isArmUpdate) {
			memset(sendPacket, 0x00, sendPacketSize);
			_arm_core->getArmCommandPacket(sendPacket);
			_bodyConnection->writeBytes( sendPacket, sendPacketSize );
			_isArmUpdate = false;
		}
		ros::Duration(updateArmPeriod).sleep();
	}

	delete[] sendPacket;
}

void ERobotCore::_updatePantilt() {
	int state = RETURN_FAILED;
	int sendPacketSize				= 14; // pantilt + arm
	unsigned char* sendPacket		= new unsigned char[sendPacketSize];

	memset(sendPacket, 0x00, sendPacketSize);
	_pantilt_core->getPantiltCommandPacket(sendPacket);
	_bodyConnection->writeBytes( sendPacket, sendPacketSize );

	delete[] sendPacket;
}


void ERobotCore::getWheelEncoderValue(long* data, int* x, int* y, int* t ) {
	//pthread_mutex_lock( &__comunicate_mutex );
	//ROS_DEBUG("-------> get wheel encoder value!");
	_wheel_encoder_core->getWheelEncoderValue(data,x,y,t);
	//pthread_mutex_unlock( &__comunicate_mutex );
}

void ERobotCore::getBatteryValue(int* voltage) {
	pthread_mutex_lock( &__sensor_mutex );
	_battery_core->getBatteryValue(voltage);
	pthread_mutex_unlock( &__sensor_mutex );
}

void ERobotCore::getUltrasonicValue(unsigned short *data, int nDataSize) {
	//EnterCriticalSection(&_sensor_comunicate);
	_ultrasonic_core->getUltrasonicValue(data,nDataSize);
	//LeaveCriticalSection(&_sensor_comunicate);
}

void ERobotCore::getPSDValue(unsigned short *data, int nDataSize) {
//	pthread_mutex_lock( &__comunicate_mutex );
	_psd_core->getPSDValue(data,nDataSize);
//	pthread_mutex_unlock( &__comunicate_mutex );
}

int ERobotCore::setWheelValue(unsigned char command, int param1, int param2, int param3, int param4) {
	//EnterCriticalSection(&_comunicate);
	//pthread_mutex_lock(&__comunicate_mutex);

	//int sendPacketSize = 12;
	//unsigned char* sendPacket = new unsigned char[sendPacketSize];

	//memset(sendPacket, 0x00, sendPacketSize);
	_wheel_core->setWheelValue(command,param1,param2,param3,param4);
	//_wheel_core->addWheelCommandPacket(sendPacket, 0);
	//_baseConnection->writeBytes(sendPacket,sendPacketSize);
/*
	if(command == EROBOT_COMMAND_WHEEL_MOVE_TO_DELTA_XYT) {
//		boost::mutex::scoped_lock lock(_mutex);
//		_condition.wait(lock);
		ROS_DEBUG("Delta move started\n");
		_isDeltaMove = true;
//		_deltaClock
	}
	//LeaveCriticalSection(&_comunicate);
	ros::Duration(0.1).sleep();
	pthread_mutex_unlock(&__comunicate_mutex);
*/
	return 0;
}

int ERobotCore::setPanTiltValue(unsigned char id, short anglePan, short angleTilt, short speedPan, short speedTilt) {
	pthread_mutex_lock( &__body_mutex );
//	cout << "   ERobotCore::setPanTiltValue " << endl;
	_isPantiltUpdate = true;
	_pantilt_core->setPantiltValue(id, anglePan, angleTilt, 0, speedPan, speedTilt, 0);
//	_updatePantilt();
	pthread_mutex_unlock( &__body_mutex );
	return 0;
}

int ERobotCore::setXtionPanTiltValue(unsigned char id, short anglePan, short angleTilt, short angleXtion, short speedPan, short speedTilt, short speedXtion) {
	pthread_mutex_lock( &__body_mutex );
	_isPantiltUpdate = true;
	_pantilt_core->setPantiltValue(id, anglePan,angleTilt,angleXtion, speedPan,speedTilt,speedXtion);
//	_updatePantilt();
	pthread_mutex_unlock( &__body_mutex );
	return 0;
}


int ERobotCore::setLEDValue(unsigned char command, unsigned char red, unsigned char green, unsigned char blue, unsigned char blink) {
	pthread_mutex_lock( &__sensor_mutex );
	_isLedUpdate = true;
	_led_core->setLEDValue(command,red,green,blue,blink);
	//_updateLED();
	pthread_mutex_unlock( &__sensor_mutex );
	return 0;
}

void ERobotCore::getTouchButtonValue(unsigned short *data, int nDataSize) {
	pthread_mutex_lock( &__sensor_mutex );
//	_updateTouchButton();
	_touch_core->getTouchButtonValue(data,nDataSize);
	pthread_mutex_unlock( &__sensor_mutex );
}

int ERobotCore::setArmValue(unsigned char command, short *angles, short *speeds) {
	pthread_mutex_lock( &__body_mutex );
	_isArmUpdate = true;
	_arm_core->setArmValue(command,angles,speeds);
//	_updateArm();
	pthread_mutex_unlock( &__body_mutex );
	return 0;
}

void ERobotCore::getArmPosition(short* positions) {
	pthread_mutex_lock( &__body_mutex );
//	_arm_core->getArmPositons(positions);

	int sendPacketSize = 23;
	unsigned char* sendPacket = new unsigned char[sendPacketSize];

	memset(sendPacket, 0x00, sendPacketSize);
	short angles[6] = {0,0,0,0,0,0};
	short speeds[6] = {0,0,0,0,0,0};
	_arm_core->setArmValue(EROBOT_COMMAND_ARM_GET_POSITION,angles,speeds);
	_arm_core->addArmCommandPacket(sendPacket, 0);
	_bodyConnection->writeBytes(sendPacket,sendPacketSize);

	int receivePacketSize = 17;
	unsigned char* receivePacket = new unsigned char[receivePacketSize];
	memset(receivePacket, 0x00, receivePacketSize);

	int real = _bodyConnection->readBytes(receivePacket,receivePacketSize);
//	printf("\n readBytes packet : ");
//	for(int i=0 ; i<real ; i++) {
//		printf("%02x ", receivePacket[i]);
//	}
//	printf("\n");
	if( real < receivePacketSize) {
		ROS_ERROR("ARM_GET_POSITION readBytes size is different need 16 real %d", real);
		positions[0] = -999;
		pthread_mutex_unlock( &__body_mutex );
		return;
	}


	if(_arm_core->isArmPositionPacket(receivePacket)) {
		if(RETURN_SUCCESS == _arm_core->parseAndSetArmPositionDataPacket(receivePacketSize,receivePacket, positions)) {

		} else {
			positions[0] = -999;
		}
	} else {
		positions[0] = -999;
	}

	pthread_mutex_unlock( &__body_mutex );
}

void ERobotCore::getPantiltPosition(double* positions) {
	pthread_mutex_lock( &__body_mutex );
//	_pantilt_core->getPantiltPositons(positions);

	int sendPacketSize = 14;
	unsigned char* sendPacket = new unsigned char[sendPacketSize];

	memset(sendPacket, 0x00, sendPacketSize);
	_pantilt_core->setPantiltValue(EROBOT_COMMAND_PANTILT_GET_POSITION,0,0,0,0,0,0);
	_pantilt_core->addPantiltCommandPacket(sendPacket, 0);
	_bodyConnection->writeBytes(sendPacket,sendPacketSize);

	int receivePacketSize = 11;
	unsigned char* receivePacket = new unsigned char[receivePacketSize];
	memset(receivePacket, 0x00, receivePacketSize);


	int real = _bodyConnection->readBytes(receivePacket,receivePacketSize);
//	printf("\n readBytes packet : ");
//	for(int i=0 ; i<real ; i++) {
//		printf("%02x ", receivePacket[i]);
//	}
//	printf("\n");

	if(real < receivePacketSize) {
		ROS_ERROR("PANTILT_DETECTING_ERROR readBytes size is different");
		positions[0] = -999;
		pthread_mutex_unlock( &__body_mutex );
		return;
	}

	if(_pantilt_core->isPantiltPositionPacket(receivePacket)) {
		if(RETURN_SUCCESS == _pantilt_core->parseAndSetPantiltPositionDataPacket(receivePacketSize,receivePacket, positions)) {

		} else {
			positions[0] = -999;
		}
	} else {
		positions[0] = -999;
	}

	pthread_mutex_unlock( &__body_mutex );
}

void ERobotCore::selfDiagnosisWheel(short errorCode[9]) {
//	pthread_mutex_lock( &__comunicate_mutex );
/*
		int stopPacketSize = 5;
		unsigned char* stopPacket = new unsigned char[stopPacketSize];
		memset(stopPacket, 0x00, stopPacketSize);

		if(_isDeltaMove) {
			_isDeltaMove = false;
			cir_msgs::Device_Wheel_Msg errorMessage;
			errorMessage.command = EROBOT_COMMAND_WHEEL_MOVE_TO_DELTA_XYT;
			errorMessage.iParams.push_back(-1);
			this->_deltaPublisher.publish(errorMessage);
			ROS_DEBUG("delta move publish errorMessage");
		}
		_wheel_core->addWheelStopCommandPacket(stopPacket, 0);
		ROS_DEBUG("send stop packet");
		_baseConnection->writeBytes(stopPacket,stopPacketSize);

		ros::Duration(0.1).sleep();
		memset(stopPacket, 0x00, stopPacketSize);
		ROS_DEBUG("set SelfDiagnosis packet 0");
		_wheel_core->addWheelSelfDiagnosisCommandPacket(stopPacket, 0);
		ROS_DEBUG("send SelfDiagnosis packet");
		_baseConnection->writeBytes(stopPacket,stopPacketSize);

		int receivePacketSize = 14;
		unsigned char* receivePacket	= new unsigned char[receivePacketSize];
		memset(receivePacket, 0x00, receivePacketSize);

		int ss = 0;
		isErrorCheckEnd = false;
		while(ss == 0) {
			ss = _baseConnection->readBytes(receivePacket,receivePacketSize);
			ros::Duration(0.1).sleep();
			if(isErrorCheckEnd) {
				break;
			}
		}
	//	printf("\n WHEEL_SELF_DIAGNOSIS receive packet: ");
	//	for(int i=0 ; i<ss ; i++) {
	//		printf("%02x ", receivePacket[i]);
	//	}
		if(ss < receivePacketSize) {
	//		printf("WHEEL_SELF_DIAGNOSIS readBytes size is different. need is 14, real is %d ", ss);
			errorCode[0] = -1;

	//		printf("\n WHEEL_SELF_DIAGNOSIS receive packet : ");
	//		for(int i=0 ; i<ss ; i++) {
	//			printf("%02x ", receivePacket[i]);
	//		}
	//		printf("\n");
	//		pthread_mutex_unlock( &__comunicate_mutex );
			return;
		}
	//	printf("\n");
		if(_wheel_core->isWheelErrorPacket(receivePacket)) {
			if(RETURN_SUCCESS == _wheel_core->parseAndSetWheelErrorDataPacket(receivePacketSize,receivePacket, errorCode)) {
			} else {
				errorCode[0] = -1;
			}
		} else {
			errorCode[0] = -1;
		}
	//	pthread_mutex_unlock( &__comunicate_mutex );
*/
}

void ERobotCore::selfDiagnosisWheelNoMove(short errorCode[9]) {
/*	ROS_DEBUG("ERobotCore::selfDiagnosisWheelNoMove start");
	if(_wheel_core->isWheelStop() && !_isDeltaMove) {
//		pthread_mutex_lock( &__comunicate_mutex );

		int stopPacketSize = 5;
		unsigned char* stopPacket = new unsigned char[stopPacketSize];
		memset(stopPacket, 0x00, stopPacketSize);
		ROS_DEBUG("set selfDiagnosisWheelNoMove packet");
		_wheel_core->addWheelSelfDiagnosisCommandPacket2(stopPacket, 0);
		ROS_DEBUG("send SelfDiagnosis packet");
		_baseConnection->writeBytes(stopPacket,stopPacketSize);

		int receivePacketSize = 14;
		unsigned char* receivePacket	= new unsigned char[receivePacketSize];
		memset(receivePacket, 0x00, receivePacketSize);

		int ss = 0;
		int count = 0;
		while(ss == 0 && count <= 10) {
			ss = _baseConnection->readBytes(receivePacket,receivePacketSize);
			ros::Duration(0.1).sleep();
			count++;
		}
//		printf("\n WHEEL_SELF_DIAGNOSIS_NO_MOVE receive packet: ");
//		for(int i=0 ; i<ss ; i++) {
//			printf("%02x ", receivePacket[i]);
//		}
//		printf("\n");
		if(ss < receivePacketSize) {
			errorCode[0] = -1;
//			pthread_mutex_unlock( &__comunicate_mutex );
			return;
		}
		if(_wheel_core->isWheelErrorPacket(receivePacket)) {
			if(RETURN_SUCCESS == _wheel_core->parseAndSetWheelErrorDataPacket(receivePacketSize,receivePacket, errorCode)) {
			} else {
				errorCode[0] = -1;
			}
		} else {
			errorCode[0] = -1;
		}
//		pthread_mutex_unlock( &__comunicate_mutex );
	} else {
		for(int in = 0; in < 9; in++) {
			errorCode[in] = 0;
		}
	}
*/
}

void ERobotCore::errorDetectingPantilt(short errorCode[3]) {
	pthread_mutex_lock( &__body_mutex );

	int sendPacketSize = 14;
	unsigned char* sendPacket = new unsigned char[sendPacketSize];

	memset(sendPacket, 0x00, sendPacketSize);
	_pantilt_core->setPantiltValue(EROBOT_COMMAND_ARM_DETECTING_ERROR,0,0,0,0,0,0);
	_pantilt_core->addPantiltCommandPacket(sendPacket, 0);
	_bodyConnection->writeBytes(sendPacket,sendPacketSize);

	int receivePacketSize = 8;
	unsigned char* receivePacket = new unsigned char[receivePacketSize];
	memset(receivePacket, 0x00, receivePacketSize);

	int real = _bodyConnection->readBytes(receivePacket,receivePacketSize);
//	printf("\n errorDetectingArm receive packet: ");
//	for(int i=0 ; i<real ; i++) {
//		printf("%02x ", receivePacket[i]);
//	}
//	printf("\n");

	if(real < receivePacketSize) {
		ROS_ERROR("PANTILT_DETECTING_ERROR readBytes size is different need is %d , real is %d", receivePacketSize, real);
		errorCode[0] = -1;
		pthread_mutex_unlock( &__body_mutex );
		return;
	}

	if(_pantilt_core->isPantiltErrorPacket(receivePacket)) {
		if(RETURN_SUCCESS == _pantilt_core->parseAndSetPantiltErrorDataPacket(receivePacketSize,receivePacket, errorCode)) {

		} else {
			errorCode[0] = -1;
		}
	} else {
		errorCode[0] = -1;
	}
	pthread_mutex_unlock( &__body_mutex );
}

void ERobotCore::errorDetectingArm(short errorCode[6]) {

	pthread_mutex_lock( &__body_mutex );

	int sendPacketSize = 23;
	unsigned char* sendPacket = new unsigned char[sendPacketSize];

	memset(sendPacket, 0x00, sendPacketSize);
	short angles[6] = {0,0,0,0,0,0};
	short speeds[6] = {0,0,0,0,0,0};
	_arm_core->setArmValue(EROBOT_COMMAND_PANTILT_DETECTING_ERROR,angles,speeds);
	_arm_core->addArmCommandPacket(sendPacket, 0);
	_bodyConnection->writeBytes(sendPacket,sendPacketSize);

	int receivePacketSize = 11;
	unsigned char* receivePacket = new unsigned char[receivePacketSize];
	memset(receivePacket, 0x00, receivePacketSize);

	int real = _bodyConnection->readBytes(receivePacket,receivePacketSize);
//	printf("\n errorDetectingArm receive packet: ");
//	for(int i=0 ; i<real ; i++) {
//		printf("%02x ", receivePacket[i]);
//	}
//	printf("\n");
	if(real < receivePacketSize) {
		ROS_ERROR("ARM_DETECTING_ERROR readBytes size is different");
		errorCode[0] = -1;
		pthread_mutex_unlock( &__body_mutex );
		return;
	}


	if(_arm_core->isArmErrorPacket(receivePacket)) {
		if(RETURN_SUCCESS == _arm_core->parseAndSetArmErrorDataPacket(receivePacketSize,receivePacket, errorCode)) {

		} else {
			errorCode[0] = -1;
		}
	} else {
		errorCode[0] = -1;
	}
	pthread_mutex_unlock( &__body_mutex );
}


int ERobotCore::errorDetectingTouch(int touchID) {
	isTouchErrorChecking = true;

	pthread_mutex_lock( &__sensor_mutex );

	ros::Duration(0.15).sleep();
	int readPacketSize2				= 10+8;  // touch + battery

	unsigned char* receivePacket2	= new unsigned char[readPacketSize2];
	memset(receivePacket2, 0x00, readPacketSize2);
	_etcConnection->readBytes(receivePacket2,readPacketSize2);

	int result = -1;
	int sendPacketSize = 6;
	unsigned char* sendPacket = new unsigned char[sendPacketSize];

	memset(sendPacket, 0x00, sendPacketSize);

	_touch_core->addTouchButtonErrorPacket(EROBOT_COMMAND_TOUCHBUTTON_DETECTING_ERROR,sendPacket,touchID, 0);

//	printf("\n errorDetectingTouch send packet: ");
//	for(int i=0 ; i<sendPacketSize ; i++) {
//		printf("%02x ", sendPacket[i]);
//	}
//	printf("\n");

	_etcConnection->writeBytes(sendPacket,sendPacketSize);

	int receivePacketSize = 7;
	unsigned char* receivePacket = new unsigned char[receivePacketSize];
	memset(receivePacket, 0x00, receivePacketSize);

	int real = _etcConnection->readBytes(receivePacket,receivePacketSize);

//	printf("\n errorDetectingTouch receive packet: ");
//	for(int i=0 ; i<real ; i++) {
//		printf("%02x ", receivePacket[i]);
//	}
//	printf("\n");
	if(real < receivePacketSize) {
		ROS_ERROR("TOUCH_DETECTING_ERROR readBytes size is different need is 7, reals is %d", real);
		pthread_mutex_unlock( &__sensor_mutex );
		return -1;
	}

	if(_touch_core->isTouchErrorPacket(receivePacket)) {
		result = _touch_core->parseAndSetTouchErrorDataPacket(receivePacketSize,receivePacket);
	} else {

	}
	pthread_mutex_unlock( &__sensor_mutex );
	isTouchErrorChecking = false;
	return result;
}
