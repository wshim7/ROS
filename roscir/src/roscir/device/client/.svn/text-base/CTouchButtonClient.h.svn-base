#ifndef __ROSCIR_CLIENT_TOUCHBUTTON_H__
#define __ROSCIR_CLIENT_TOUCHBUTTON_H__

#include <roscir/device/common/TouchButton.h>
#include <roscir/device/RosCIRDefinitions.h>
#include <roscir/env/Config.h>
#include <cir_msgs/Device_Touch_Msg.h>
#include <cir_msgs/Device_Error_Srv.h>
#include <iostream>
#include <sstream>
#include <ros/ros.h>
//#include <cir_msgs/TouchButtonService.h>
using namespace std;
class CIRAPI CTouchButtonClientProxy {
private :
	CTouchButtonClientProxy();

public :
	virtual ~CTouchButtonClientProxy();
	static CTouchButton* newInstance();
};


class CTouchButtonROSStub : public CTouchButton {

private :
	ros::NodeHandle			_nodeHandle;
	ros::ServiceClient		_toubhButtonClient;
	ros::ServiceClient		_toubhButtonErrorClient;
	ros::Subscriber _toubhButtonSubscriber;

	void subscribeCallBack(const cir_msgs::Device_Touch_Msg::ConstPtr& message);


	static const int NUMBER_OF_DATA = 6;
	unsigned int data[ NUMBER_OF_DATA ];

public :
	CTouchButtonROSStub();
	virtual ~CTouchButtonROSStub();

	CTouchButtonData readData( int index );
	CHeadTouchButtonData readHeadData( int index );
	int detectingError(int touchID);
};
#endif /* __ROSCIR_CLIENT_TOUCHBUTTON_H__ */
