/*
 * RollBendHandler.h
 *
 *  Created on: 2014. 1. 16.
 *      Author: msyoo
 */

#ifndef ROLLBENDHANDLER_H_
#define ROLLBENDHANDLER_H_

#include <string>
#include <ros/ros.h>

#include <device/odif/rollbend/RollBendServer.h>
#include <roscir/device/data/RollBendPosition.h>
#include <roscir/device/RosCIRDefinitions.h>


#include <cir_msgs/Device_Rollbend_Msg.h>
#include <cir_msgs/Device_Error_Srv.h>
#include <cir_msgs/Device_Data_Srv.h>
#include <geometry_msgs/Twist.h>

namespace cir {
namespace devicenode {

class RollBendHandler {
public:
	RollBendHandler();
	virtual ~RollBendHandler();

	void rollbendSubscriberCallback(const cir_msgs::Device_Rollbend_Msg::ConstPtr& message);
	bool rollbendErrorServiceCallback(cir_msgs::Device_Error_Srv::Request &request, cir_msgs::Device_Error_Srv::Response &response);
	bool rollbendDataServiceCallback(cir_msgs::Device_Data_Srv::Request &request, cir_msgs::Device_Data_Srv::Response &response);
	void twistMsgCallback(const geometry_msgs::Twist::ConstPtr& message);

private:
	ros::NodeHandle			_nodeHandle;
	ros::ServiceServer		_rollbendServiceServer;
	ros::Subscriber			_rollbendSubscriber;
	ros::ServiceServer		_rollbendErrorServiceServer;
	ros::ServiceServer		_rollbendDataServiceServer;
	ros::Subscriber			_twistMsgSubscriber;
	CRollBend*	_rollbendServerProxy;

	void initHandler();
};

} /* namespace devicenode */
} /* namespace cir */
#endif /* ROLLBENDHANDLER_H_ */
