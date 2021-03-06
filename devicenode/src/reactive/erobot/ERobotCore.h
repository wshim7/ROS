#ifndef __EROBOT_CORE_H__
#define __EROBOT_CORE_H__

#include <stdio.h>
#include <iostream>

#include <boost/thread.hpp>
#include <pthread.h>

#include <ros/ros.h>
#include <roscir/env/Config.h>
#include <reactive/erobot/session/ERobotSerialConnector.h>
#include <reactive/erobot/utility/ERobotFunctionFactory.h>
#include <reactive/erobot/session/EWheelEncoderCore.h>
#include <reactive/erobot/session/EUltraCore.h>
#include <reactive/erobot/session/EPSDCore.h>
#include <reactive/erobot/session/ETouchCore.h>
#include <reactive/erobot/session/EWheelCore.h>
#include <reactive/erobot/session/EArmCore.h>
#include <reactive/erobot/session/EPantiltCore.h>
#include <reactive/erobot/session/ELEDCore.h>
#include <reactive/erobot/session/EBatteryCore.h>


#include <cir_msgs/Device_Wheel_Msg.h>

using namespace std;

namespace reactive {
	namespace erobot {
		namespace core {
			class ERobotCore {

			private :
//				UINT m_nTimerID;

				bool _ISEND;
				
//				mutable		CRITICAL_SECTION	_comunicate;
//				mutable		CRITICAL_SECTION	_body_comunicate;
//				mutable		CRITICAL_SECTION	_sensor_comunicate;

				static pthread_mutex_t __comunicate_mutex;
				static pthread_mutex_t __body_mutex;
				static pthread_mutex_t __sensor_mutex;

				ros::NodeHandle	_nodehandle;
				bool _isDeltaMove;
				bool _isArmUpdate;
				bool _isPantiltUpdate;
				bool _isLedUpdate;
				ros::Publisher _deltaPublisher;

				bool isUltraError;
				bool isGyroError;
				bool isErrorCheckEnd;
				bool isTouchErrorChecking;

				EWheelEncoderCore*		_wheel_encoder_core;
				EUltraCore*				_ultrasonic_core;
				EPSDCore*				_psd_core;
				ETouchCore*				_touch_core;
				EWheelCore*				_wheel_core;
				EPantiltCore*			_pantilt_core;
				EArmCore*				_arm_core;
				ELEDCore*				_led_core;
				EBatteryCore*			_battery_core;

			private : 
				ERobotSerialConnector* _baseConnection;
				ERobotSerialConnector* _bodyConnection;
				ERobotSerialConnector* _sensorConnection;
				ERobotSerialConnector* _etcConnection;
				

				void _updateWheelEncoder();
				void _updateUltrasonic();
				void _updatePSD();
				void _updateWheel();
				void _updateArm();
				void _updatePantilt();
				void _updateTouchButton();
				void _updateLED();
				void _updateMotorError();

				
				void handleBodyMessage();

				void _checkUltrasonicGyroError();
				void _checkWheelErrorTimeover();

			public :
				ERobotCore();
				virtual ~ERobotCore();

				static ERobotCore* getInstance();

//				static void CALLBACK TimeProc(UINT m_nTimerID, UINT uiMsg, DWORD dwUser, DWORD dw1, DWORD d2);
				void initERobotCore();
				void checkMotorError();
				void _updateBase();
				void _updateBody();
				void _updateSensor();
				void _updateEtc();
				void _updateBodyPosition();
				void run();
				void getWheelEncoderValue(long* data, int* x, int* y, int* t );
				void getUltrasonicValue(unsigned short *data, int nDataSize);
				void getTouchButtonValue(unsigned short *data, int nDataSize);
				void getPSDValue(unsigned short *data, int nDataSize);
				void getBatteryValue(int* voltage);
				void getArmPosition(short* positions);
				void getPantiltPosition(double* positions);

				int setWheelValue(unsigned char command, int param1, int param2, int param3, int param4);
				int setPanTiltValue(unsigned char id, short anglePan, short angleTilt, short speedPan, short speedTilt);
				int setXtionPanTiltValue(unsigned char id, short anglePan, short angleTilt, short angleXtion, short speedPan, short speedTilt, short speedXtion);
				int setLEDValue(unsigned char id, unsigned char red, unsigned char green, unsigned char blue, unsigned char blink);
				int setArmValue(unsigned char command, short *angles, short *speeds);

				void selfDiagnosisWheel(short errorCode[9]);
				void selfDiagnosisWheelNoMove(short errorCode[9]);
				void errorDetectingPantilt(short errorCode[3]);
				void errorDetectingArm(short errorCode[6]);
				int errorDetectingTouch(int touchID);


				void viewMessageBox(const char* message, const char* title);
			};
		}
	}
}

#endif /* __EROBOT_CORE_H__ */
