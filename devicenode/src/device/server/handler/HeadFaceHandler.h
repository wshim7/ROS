/*
 * HeadFaceHandler.h
 *
 *  Created on: 2014. 2. 13.
 *      Author: msyoo
 */

#ifndef HEADFACEHANDLER_H_
#define HEADFACEHANDLER_H_

#include <string>
#include <ros/ros.h>

#include <device/odif/headface/HeadFaceServer.h>
#include <roscir/device/RosCIRDefinitions.h>
#include <roscir/device/CirApi.h>
#include <cir_msgs/Device_Headface_Msg.h>

using namespace std;

namespace cir {
namespace devicenode {

class HeadFaceHandler {
public:
	HeadFaceHandler();
	virtual ~HeadFaceHandler();

	void headfaceSubscriberCallback(const cir_msgs::Device_Headface_Msg::ConstPtr& message);

private:
	ros::NodeHandle			_nodeHandle;
	ros::Subscriber			_headfaceSubscriber;
	CHeadFace*	_headfaceServerProxy;

	void initHandler();
};

} /* namespace devicenode */
} /* namespace cir */
#endif /* HEADFACEHANDLER_H_ */
