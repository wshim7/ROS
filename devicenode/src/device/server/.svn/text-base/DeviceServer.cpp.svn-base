#include "DeviceServer.h"
#include <ros/ros.h>
#include <roscir/env/Config.h>
using namespace cir::devicenode;

DeviceServer::DeviceServer() {
	m_Robot_TYPE = CConfig::getInstance()->getParamValueInt("ROBOT_TYPE");
	this->initRobot();
}

DeviceServer::~DeviceServer() {

}

void DeviceServer::initNode(int argc, char** argv) {


	ROS_INFO("--------------------------------------------");
	ROS_INFO("\t\t Create node handle... ");
	ROS_INFO("\t\t ROBOT_TYPES  6:MOCK, 7:Mero, 8:MeroS, 11:E-Robot");
	ROS_INFO("\t\t ROBOT_TYPE: %d: ", m_Robot_TYPE);
	ROS_INFO("--------------------------------------------");


//	switch (m_Robot_TYPE) {
//		case ROBOT_TYPE_EROBOT:
//			ERobotCore::getInstance();
//			break;
//
////		case ROBOT_TYPE_MERO :
////			MeroRS485Driver::getInstance();
////			break;
////
////		case ROBOT_TYPE_MERO_S :
////			MeroRS485Driver::getInstance();
////			break;
//		default:
//			break;
//	}

	ArmHandler	armHandler;
	GyroHandler gyroHandler;
	PSDHandler	psdHandler;
	UltrasonicHandler ultrasonicHandler;
	WheelEncoderHandler wheelencoderHandler;
	WheelHandler wheelHandler;
	LEDHandler ledHandler;
	TouchHandler touchHandler;
	RollBendHandler rollbendHandler;
	PantiltHandler pantiltHandler;
	BatteryHandler batteryHandler;
	HeadFaceHandler heafaceHandler;
	ROS_INFO("-------------------------------------------- Device Server init fin.");

	ros::MultiThreadedSpinner spinner(4); // Use 4 threads
	spinner.spin(); // spin() will not return until the node has been shutdown
//	ros::spin();
}


void DeviceServer::initRobot() {
	if(m_Robot_TYPE == ROBOT_TYPE_MERO_S) {

		int typeOfServer	= CConfig::getInstance()->getParamValueInt( "SERVER_DEVICE_TYPE" );
		if(typeOfServer == SERVER_DEVICE_REAL) {
			MeroNeckDriver::getInstance()->initPantiltRollBendMotors();
		} else {
			//
			// mock mode
			//
			//
		}
	}else if(m_Robot_TYPE == ROBOT_TYPE_MERO){
		int typeOfServer	= CConfig::getInstance()->getParamValueInt( "SERVER_DEVICE_TYPE" );
		if(typeOfServer == SERVER_DEVICE_REAL) {
			MeroNeckDriver::getInstance()->initPantiltRollBendMotors();
			MeroFaceDriver::getInstance()->initFace();
		} else {
			//
			// mock mode
			//
			//
		}

	}
	else if(m_Robot_TYPE == ROBOT_TYPE_EROBOT) {
		int motorCheck = CConfig::getInstance()->getParamValueInt( "CHECK_MOTOR_ERROR" );
		if(motorCheck == 1) {
			ERobotCore::getInstance()->checkMotorError();
		}
		ERobotCore::getInstance()->initERobotCore();
	}
}

int main(int argc, char** argv) {
	
	ros::init(argc, argv, "DeviceServerNode");
	ros::NodeHandle nodeHandle;

	DeviceServer server;
	server.initNode(argc,argv);
	
	return 0;
}
