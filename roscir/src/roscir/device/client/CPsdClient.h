#ifndef __ROSCIR_CLIENT_PSD_H__
#define __ROSCIR_CLIENT_PSD_H__

#include <roscir/device/common/Psd.h>
#include <roscir/device/RosCIRDefinitions.h>
#include <roscir/env/Config.h>

#include <iostream>

#include <ros/ros.h>
#include <cir_msgs/Device_PSD_Srv.h>
#include <cir_msgs/Device_PSD_Msg.h>

using namespace std;

class CIRAPI CPSDClientProxy
{
private:
	CPSDClientProxy(void);

public:
	virtual ~CPSDClientProxy(void);

public:
	static CPSD* newInstance();
};


class CPsdROSStub : public CPSD
{
private:
	ros::NodeHandle			_nodeHandle;
	ros::ServiceClient		_psdClient;
	ros::Subscriber			_psdSubscriber;
	unsigned short			tempData[6];

public:
	CPsdROSStub(void);
	virtual ~CPsdROSStub(void);

private :
	void subscribeCallBack(const cir_msgs::Device_PSD_Msg::ConstPtr& message);

public:
	int readData(int returnMethod, CPSDData& data);
};


#endif /* __ROSCIR_CLIENT_PSD_H__ */
