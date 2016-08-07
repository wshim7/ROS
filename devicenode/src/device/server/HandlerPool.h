#ifndef __DEVICE_SERVER_HANDLER_POOL_H__
#define __DEVICE_SERVER_HANDLER_POOL_H__

#include <ros/ros.h>

#include <device/server/handler/ArmHandler.h>
#include <device/server/handler/GyroHandler.h>
#include <device/server/handler/PantiltHandler.h>
#include <device/server/handler/PSDHandler.h>
#include <device/server/handler/UltrasonicHandler.h>
#include <device/server/handler/WheelEncoderHandler.h>
#include <device/server/handler/WheelHandler.h>

using namespace std;
using namespace cir::devicenode;

namespace cir {
	namespace devicenode {
		class HandlerPool {

		public :
			HandlerPool();
			virtual ~HandlerPool();

			static HandlerPool* getInstance();
		};
	}
}


#endif /* __DEVICE_SERVER_HANDLER_POOL_H__ */