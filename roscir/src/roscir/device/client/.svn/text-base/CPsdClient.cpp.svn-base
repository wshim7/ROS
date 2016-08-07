#include "CPsdClient.h"

CPSDClientProxy::CPSDClientProxy()
{
}


CPSDClientProxy::~CPSDClientProxy()
{
}

CPSD* CPSDClientProxy::newInstance() { // throw (SocketException, ConnectException) {
	//cout << "[CPSDClientProxy] : Create Sole Instance(PSD).." << endl;
	ROS_INFO("[CPSDClientProxy] : Create Sole Instance(CPsdROSStub)..");
	return new CPsdROSStub();
}

CPsdROSStub::CPsdROSStub() {
	//this->_psdClient = this->_nodeHandle.serviceClient<cir_msgs::PSDService>("/DeviceNode/PSDService",true);
	int typeOfServerDevice = CConfig::getInstance()->getParamValueInt( "SERVER_DEVICE_TYPE" );
	if(typeOfServerDevice == 2) {
		this->_psdSubscriber = this->_nodeHandle.subscribe<cir_msgs::Device_PSD_Msg>("/DeviceNode/PSD_Simul/data", 1000, &CPsdROSStub::subscribeCallBack, this);

	} else {
		this->_psdSubscriber = this->_nodeHandle.subscribe<cir_msgs::Device_PSD_Msg>("/DeviceNode/PSD/data", 1000, &CPsdROSStub::subscribeCallBack, this);
	}

	ROS_INFO("[CPsdROSStub] : check device node state.. ");
	while(this->_psdSubscriber.getNumPublishers() < 1) {
		ros::Duration(0.1).sleep();
	}
	ROS_INFO("   - check finished..(OK) \n");
}

CPsdROSStub::~CPsdROSStub()
{
}

int CPsdROSStub::readData(int returnMethod, CPSDData& data) {
	/*
	cir_msgs::PSDService service;
	service.request.command = COMMAND_PSD_READ_DATA;
	if(_psdClient.call(service)) {
		//ROS_INFO("[CPsdROSStub] COMMAND_PSD_READ_DATA success");
		unsigned short tempData[6] = {
			service.response.msg.param.at(0),
			service.response.msg.param.at(1),
			service.response.msg.param.at(2),
			service.response.msg.param.at(3),
			service.response.msg.param.at(4),
			service.response.msg.param.at(5)
		};
		data.setData(tempData,6);
		return RETURN_SUCCESS;
	} else {
		//ROS_ERROR("[CPsdROSStub] COMMAND_PSD_READ_DATA fail");
		return RETURN_FAIL;
	}
	*/
	data.setData(tempData,6);
	return RETURN_SUCCESS;
}

void CPsdROSStub::subscribeCallBack(const cir_msgs::Device_PSD_Msg::ConstPtr& message) {
	tempData[0] = message->param.at(0);
	tempData[1] = message->param.at(1);
	tempData[2] = message->param.at(2);
	tempData[3] = message->param.at(3);
	tempData[4] = message->param.at(4);
	tempData[5] = message->param.at(5);
}