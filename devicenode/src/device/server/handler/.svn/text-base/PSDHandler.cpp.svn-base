#include "PSDHandler.h"

using namespace cir::devicenode;

PSDHandler::PSDHandler() {
	_psdServerProxy = CPSDServerProxy::getInstance();
	this->_PSD_THREAD_FLAG = false;
	initHandler();
	this->_this_thread = boost::thread(boost::bind(&PSDHandler::psdPublishThread, this));
}

PSDHandler::~PSDHandler() {
	this->_PSD_THREAD_FLAG = false;
	this->_this_thread.join();
	ROS_DEBUG("[PSDHandler] closed... ");
}

void PSDHandler::initHandler() {
	//this->_psdServiceServer = this->_nodeHandle.advertiseService("/DeviceNode/PSDService", &PSDHandler::psdServiceCallback, this);
	//ROS_INFO("PSD handler created - /DeviceNode/PSDService");
	this->_psdPublisher = this->_nodeHandle.advertise<cir_msgs::Device_PSD_Msg>("/DeviceNode/PSD/data", 1000);
	ROS_INFO("PSD handler created - /DeviceNode/PSD/data");
}

bool PSDHandler::psdServiceCallback(cir_msgs::Device_PSD_Srv::Request &request, cir_msgs::Device_PSD_Srv::Response &response) {

	string command = request.command;

	if(command == COMMAND_PSD_READ_DATA) {
		CPSDData returnData;
		_psdServerProxy->readData(1, returnData);
		response.msg.param.push_back(returnData.getData()[0]);
		response.msg.param.push_back(returnData.getData()[1]);
		response.msg.param.push_back(returnData.getData()[2]);
		response.msg.param.push_back(returnData.getData()[3]);
		response.msg.param.push_back(returnData.getData()[4]);
		response.msg.param.push_back(returnData.getData()[5]);
		return true;
	} else {
		cout << "[GyroHandler] unrecognized command. " << endl;
	}
	return false;
}

void PSDHandler::psdPublishThread() {
	this->_PSD_THREAD_FLAG = true;
	ros::Rate loop_rate(10);

	while( ros::ok() && this->_PSD_THREAD_FLAG ) {

		cir_msgs::Device_PSD_Msg message;
		CPSDData returnData;
		_psdServerProxy->readData(1, returnData);
		message.param.push_back(returnData.getData()[0]);
		message.param.push_back(returnData.getData()[1]);
		message.param.push_back(returnData.getData()[2]);
		message.param.push_back(returnData.getData()[3]);
		message.param.push_back(returnData.getData()[4]);
		message.param.push_back(returnData.getData()[5]);
		this->_psdPublisher.publish(message);

		ros::spinOnce();
		loop_rate.sleep();
	}
}