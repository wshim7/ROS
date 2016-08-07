#ifndef __DEVICE_SERVER_ARM_HANDLER_H__
#define __DEVICE_SERVER_ARM_HANDLER_H__

#include <string>
#include <ros/ros.h>
#include <device/odif/arm/ArmServer.h>
#include <cir_msgs/Device_Arm_Srv.h>
#include <cir_msgs/Device_Error_Srv.h>
#include <cir_msgs/Device_Data_Srv.h>
#include <cir_msgs/Device_Arm_Msg.h>
#include <roscir/device/RosCIRDefinitions.h>

using namespace std;

namespace cir {
	namespace devicenode {
		class ArmHandler {
		
		private :
			ros::NodeHandle			_nodeHandle;
			ros::ServiceServer		_armServiceServer;
			ros::ServiceServer		_armErrorServiceServer;
			ros::ServiceServer		_armDataServiceServer;
			ros::Subscriber			_armSubscriber;
			ros::Publisher			_armPublisher;
			CArm*					_armServerProxy;
			bool					_ARM_THREAD_FLAG;
			boost::thread			_this_thread;

		public :
			ArmHandler();
			virtual ~ArmHandler();

		private :
			void initHandler();
			
		public :
			bool armServiceCallback(cir_msgs::Device_Arm_Srv::Request &request, cir_msgs::Device_Arm_Srv::Response &response);
			bool armErrorServiceCallback(cir_msgs::Device_Error_Srv::Request &request, cir_msgs::Device_Error_Srv::Response &response);
			bool armDataServiceCallback(cir_msgs::Device_Data_Srv::Request &request, cir_msgs::Device_Data_Srv::Response &response);
			void armSubscribeCallback(const cir_msgs::Device_Arm_Msg::ConstPtr& message);
			void armPublishThread();
		};
	}
}


#endif /* __DEVICE_SERVER_ARM_HANDLER_H__ */
