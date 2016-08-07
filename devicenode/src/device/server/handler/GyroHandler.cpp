#include "GyroHandler.h"

using namespace cir::devicenode;

GyroHandler::GyroHandler() {
	_gyroServerProxy = CGyroServerProxy::getInstance();
	this->_GYRO_THREAD_FLAG = false;
	initHandler();
	this->_this_thread = boost::thread(boost::bind(&GyroHandler::gyroPublishThread, this));
}

GyroHandler::~GyroHandler() {
	this->_GYRO_THREAD_FLAG = false;
	this->_this_thread.join();
	ROS_DEBUG("[GyroHandler] closed... ");
}

void GyroHandler::initHandler() {
	//this->_gyroServiceServer = this->_nodeHandle.advertiseService("/DeviceNode/GyroService", &GyroHandler::gyroServiceCallback, this);
	this->_gyroPublisher = this->_nodeHandle.advertise<cir_msgs::Device_Gyro_Msg>("/DeviceNode/Gyro/data", 1000);
	ROS_INFO("Gyro handler created - /DeviceNode/Gyro/data");
}

bool GyroHandler::gyroServiceCallback(cir_msgs::Device_Gyro_Srv::Request &request, cir_msgs::Device_Gyro_Srv::Response &response) {

	string command = request.command;

	if(command == COMMAND_GYRO_READ_DATA) {
		CGyroData data = _gyroServerProxy->readData();
		response.msg.angle	= data.getAngle();
		response.msg.rate	= data.getRate();
		return true;
	} else {
		cout << "[GyroHandler] unrecognized command. " << endl;
	}
	return false;
}

void GyroHandler::gyroPublishThread() {
	this->_GYRO_THREAD_FLAG = true;
	ros::Rate loop_rate(10);

	while( ros::ok() && this->_GYRO_THREAD_FLAG ) {

		cir_msgs::Device_Gyro_Msg message;

		CGyroData data = _gyroServerProxy->readData();
		message.angle = data.getAngle();
		message.rate = data.getRate();
		this->_gyroPublisher.publish(message);

		ros::spinOnce();
		loop_rate.sleep();
	}
}