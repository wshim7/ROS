#ifndef __DEVICE_SERVER_PANTILT_HANDLER_H__
#define __DEVICE_SERVER_PANTILT_HANDLER_H__

#include <string>
#include <ros/ros.h>

#include <device/odif/pantilt/PantiltServer.h>
#include <roscir/device/data/PanTiltPosition.h>
#include <roscir/device/RosCIRDefinitions.h>

#include <cir_msgs/Device_Pantilt_Srv.h>
#include <cir_msgs/Device_Error_Srv.h>
#include <cir_msgs/Device_Data_Srv.h>
#include <cir_msgs/Device_Pantilt_Msg.h>
#include <geometry_msgs/Twist.h>
#include <cir_msgs/Device_ErobotPantilt_Msg.h>

using namespace std;

namespace cir {
	namespace devicenode {
		class PantiltHandler {

		private :
			ros::NodeHandle			_nodeHandle;
			ros::ServiceServer		_pantiltServiceServer;
			ros::ServiceServer		_pantiltErrorServiceServer;
			ros::ServiceServer		_pantiltDataServiceServer;
			ros::Subscriber			_pantiltSubscriber;
			ros::Subscriber			_twistMsgSubscriber;
			CPanTilt*				_pantiltServerProxy;
			ros::Publisher			_pantiltPublisher;
			bool					_PANTILT_THREAD_FLAG;
			boost::thread			_this_thread;

		public :
			PantiltHandler();
			virtual ~PantiltHandler();

		private :
			void initHandler();

		public :
			bool pantiltServiceCallback(cir_msgs::Device_Pantilt_Srv::Request &request, cir_msgs::Device_Pantilt_Srv::Response &response);
			bool pantiltErrorServiceCallback(cir_msgs::Device_Error_Srv::Request &request, cir_msgs::Device_Error_Srv::Response &response);
			bool pantiltDataServiceCallback(cir_msgs::Device_Data_Srv::Request &request, cir_msgs::Device_Data_Srv::Response &response);
			void pantiltSubscriberCallback(const cir_msgs::Device_ErobotPantilt_Msg::ConstPtr& message);
			void twistMsgCallback(const geometry_msgs::Twist::ConstPtr& message);
			void pantiltPublishThread();
		};
	}
}


#endif /* __DEVICE_SERVER_PANTILT_HANDLER_H__ */
