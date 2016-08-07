#ifndef __DEVICE_SERVER_H__
#define __DEVICE_SERVER_H__

#include <iostream>
#include <ros/ros.h>
#include <device/server/handler/ArmHandler.h>
#include <device/server/handler/GyroHandler.h>
#include <device/server/handler/PantiltHandler.h>
#include <device/server/handler/PSDHandler.h>
#include <device/server/handler/UltrasonicHandler.h>
#include <device/server/handler/WheelEncoderHandler.h>
#include <device/server/handler/WheelHandler.h>
#include <device/server/handler/LEDHandler.h>
#include <device/server/handler/TouchHandler.h>
#include <device/server/handler/RollBendHandler.h>
#include <device/server/handler/BatteryHandler.h>
#include <device/server/handler/HeadFaceHandler.h>
#include <reactive/erobot/ERobotCore.h>
#include <reactive/mero/driver/MeroNeckDriver.h>

using namespace std;

namespace cir {
	namespace devicenode {
		class DeviceServer {

		public :
			DeviceServer();
			virtual ~DeviceServer();

			void initNode(int argc, char** argv);

		private :
			int m_Robot_TYPE;
			void initRobot();
		};
	}
}


#endif /* __DEVICE_SERVER_H__ */
