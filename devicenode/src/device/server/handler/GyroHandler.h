#ifndef __DEVICE_SERVER_GYRO_HANDLER_H__
#define __DEVICE_SERVER_GYRO_HANDLER_H__

#include <string>
#include <ros/ros.h>
#include <device/idif/gyro/GyroServer.h>
#include <cir_msgs/Device_Gyro_Srv.h>
#include <roscir/device/RosCIRDefinitions.h>

using namespace std;

namespace cir {
	namespace devicenode {
		class GyroHandler {

		private :
			ros::NodeHandle			_nodeHandle;
			ros::ServiceServer		_gyroServiceServer;
			ros::Publisher			_gyroPublisher;
			CGyro*					_gyroServerProxy;
			bool					_GYRO_THREAD_FLAG;
			boost::thread			_this_thread;

		public :
			GyroHandler();
			virtual ~GyroHandler();

		private :
			void initHandler();

		public :
			bool gyroServiceCallback(cir_msgs::Device_Gyro_Srv::Request &request, cir_msgs::Device_Gyro_Srv::Response &response);
			void gyroPublishThread();
		};
	}
}


#endif /* __DEVICE_SERVER_GYRO_HANDLER_H__ */