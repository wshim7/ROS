#ifndef __ROSCIR_CLIENT_ULTRA_H__
#define __ROSCIR_CLIENT_ULTRA_H__

#include <roscir/device/common/Ultrasonic.h>
#include <roscir/device/RosCIRDefinitions.h>
#include <roscir/env/Config.h>

#include <iostream>

#include <ros/ros.h>
#include <cir_msgs/Device_Ultra_Srv.h>
#include <cir_msgs/Device_Ultra_Msg.h>

using namespace std;

class CIRAPI CUltrasonicClientProxy
{
private:
	CUltrasonicClientProxy(void);

public:
	virtual ~CUltrasonicClientProxy(void);

public:
	static CUltrasonic* newInstance();
};


class CUltraROSStub : public CUltrasonic
{
private:
	static const string DEVICE_NAME;

private:
	ros::NodeHandle			_nodeHandle;
	ros::ServiceClient		_ultraClient;
	ros::Subscriber			_ultraSubscriber;
	unsigned short			tempData[12];

public:
	CUltraROSStub(void);
	virtual ~CUltraROSStub(void);

private :
	void subscribeCallBack(const cir_msgs::Device_Ultra_Msg::ConstPtr& message);

public :
	CUltrasonicData readData(int index);
	void close();

};


#endif /* __ROSCIR_CLIENT_ULTRA_H__ */
