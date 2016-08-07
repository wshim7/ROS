#ifndef __DEVICE_SERVER_PSD_HANDLER_H__
#define __DEVICE_SERVER_PSD_HANDLER_H__

#include <string>
#include <ros/ros.h>

#include <device/idif/psd/PsdServer.h>
#include <roscir/device/RosCIRDefinitions.h>

#include <cir_msgs/Device_PSD_Srv.h>
#include <cir_msgs/Device_PSD_Msg.h>

using namespace std;

namespace cir {
	namespace devicenode {
		class PSDHandler {

		private :
			ros::NodeHandle			_nodeHandle;
			ros::ServiceServer		_psdServiceServer;
			ros::Publisher			_psdPublisher;
			CPSD*					_psdServerProxy;
			bool					_PSD_THREAD_FLAG;
			boost::thread			_this_thread;

		public :
			PSDHandler();
			virtual ~PSDHandler();

		private :
			void initHandler();

		public :
			bool psdServiceCallback(cir_msgs::Device_PSD_Srv::Request &request, cir_msgs::Device_PSD_Srv::Response &response);
			void psdPublishThread();
		};
	}
}


#endif /* __DEVICE_SERVER_PSD_HANDLER_H__ */