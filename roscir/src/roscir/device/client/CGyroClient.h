#ifndef __ROSCIR_CLIENT_GYRO_H__
#define __ROSCIR_CLIENT_GYRO_H__

#include <iostream>
#include <ros/ros.h>

#include <roscir/device/common/Gyro.h>
#include <roscir/device/RosCIRDefinitions.h>
#include <roscir/env/Config.h>

#include <cir_msgs/Device_Gyro_Srv.h>
#include <cir_msgs/Device_Gyro_Msg.h>

using namespace std;

class CIRAPI CGyroClientProxy
{
private:
	CGyroClientProxy(void);

public:
	virtual ~CGyroClientProxy(void);

public:
	static CGyro* newInstance();
};


class CGyroROSStub : public CGyro
{

private:
	ros::NodeHandle			_nodeHandle;
	ros::ServiceClient		_gyroClient;
	ros::Subscriber			_gyroSubscriber;
	double					_this_rate;
	double					_this_angle;

public:
	CGyroROSStub(void);
	CGyroROSStub(string type);
	virtual ~CGyroROSStub(void);

private :
	void subscribeCallBack(const cir_msgs::Device_Gyro_Msg::ConstPtr& message);

public:
	CGyroData readData();
};


#endif /* __ROSCIR_CLIENT_GYRO_H__ */
