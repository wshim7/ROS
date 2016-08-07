#ifndef __DEVICE_SERVER_WHEEL_HANDLER_H__
#define __DEVICE_SERVER_WHEEL_HANDLER_H__

#include <string>
#include <ros/ros.h>
#include <device/odif/wheel/WheelServer.h>
#include <cir_msgs/Device_Wheel_Msg.h>
#include <cir_msgs/Device_Wheel_Srv.h>
#include <cir_msgs/Device_Error_Srv.h>
#include <roscir/device/RosCIRDefinitions.h>
#include <geometry_msgs/Twist.h>

using namespace std;

namespace cir {
	namespace devicenode {
		class WheelHandler {

		private :
			ros::NodeHandle			_nodeHandle;
			ros::ServiceServer		_wheelServiceServer;
			ros::ServiceServer		_wheelErrorServiceServer;
			ros::Subscriber			_subscriber;
			ros::Subscriber			_twistSubscriber;
			CWheel*					_wheelServerProxy;

		public :
			WheelHandler();
			virtual ~WheelHandler();

		private :
			void initHandler();

		public :
			bool wheelServiceCallback(cir_msgs::Device_Wheel_Srv::Request &request, cir_msgs::Device_Wheel_Srv::Response &response);
			bool wheelErrorServiceCallback(cir_msgs::Device_Error_Srv::Request &request, cir_msgs::Device_Error_Srv::Response &response);
			void wheelSubscribeCallBack(const cir_msgs::Device_Wheel_Msg::ConstPtr& message);
			void twistMsgCallback(const geometry_msgs::Twist::ConstPtr& msg);
		};
	}
}


#endif /* __DEVICE_SERVER_WHEEL_HANDLER_H__ */
