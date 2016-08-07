/*
 * RollBendHandler.cpp
 *
 *  Created on: 2014. 1. 16.
 *      Author: msyoo
 */

#include "RollBendHandler.h"

namespace cir {
namespace devicenode {

RollBendHandler::RollBendHandler() {

	initHandler();
	_rollbendServerProxy = CRollBendServerProxy::getInstance();

}

RollBendHandler::~RollBendHandler() {
}



void RollBendHandler::initHandler(){

	this->_rollbendSubscriber = this->_nodeHandle.subscribe<cir_msgs::Device_Rollbend_Msg>("/DeviceNode/Rollbend/commands", 1000, &RollBendHandler::rollbendSubscriberCallback, this);

	this->_rollbendErrorServiceServer = this->_nodeHandle.advertiseService("/DeviceNode/RollbendErrorService", &RollBendHandler::rollbendErrorServiceCallback, this);
	this->_rollbendDataServiceServer = this->_nodeHandle.advertiseService("/DeviceNode/RollbendDataService", &RollBendHandler::rollbendDataServiceCallback, this);

	this->_twistMsgSubscriber = this->_nodeHandle.subscribe<geometry_msgs::Twist>("/Rollbend/cmd_vel", 1000, &RollBendHandler::twistMsgCallback, this);
	ROS_INFO("Rollbend handler created - /DeviceNode/Rollbend/commands");
}

void RollBendHandler::rollbendSubscriberCallback(const cir_msgs::Device_Rollbend_Msg::ConstPtr& message){


	string command = message->command;
	ROS_DEBUG("[RollBendHandler] receive a message - %s", command.c_str());

	if(command == COMMAND_ROLLBEND_ON) {
		_rollbendServerProxy->on();
	} else if(command == COMMAND_ROLLBEND_OFF) {
		_rollbendServerProxy->off();
	} else if(command == "stop") {
		_rollbendServerProxy->stop();
	}  else if(command ==COMMAND_ROLLBEND_MOVE_TO_HOME) {
		int speed = message->speeds[0];
		_rollbendServerProxy->moveToHome(speed);

	} else if(command == COMMAND_ROLLBEND_MOVE_ABSOLUTE_POSITION) {
		double degRoll = message->angles[0];
		double degBend = message->angles[1];
		int speed = message->speeds[0];
		_rollbendServerProxy->moveToAbsolutePosition(degRoll, degBend, speed);

	}  else if(command == COMMAND_ROLLBEND_MOVE_ABSOLUTE_POSITION_WITH_SPEED) {
		double degRoll = message->angles[0];
		double degBend = message->angles[1];
		int speedRoll = message->speeds[0];
		int speedBend = message->speeds[1];
		_rollbendServerProxy->moveToAbsolutePositionWithSpeed(degRoll, degBend, speedRoll, speedBend);

	}else if(command == COMMAND_ROLLBEND_MOVE_TO_RELATIVE_POSITION) {

	} else if(command == COMMAND_ROLLBEND_MOVE2MOTOR_SYNC) {

	} else if(command == COMMAND_ROLLBEND_MOVE_MOTOR) {

	} else if(command == COMMAND_ROLLBEND_GETPOSITION) {
		CRollBendPosition pos;
		_rollbendServerProxy->getPosition(pos);
	}

}

bool RollBendHandler::rollbendErrorServiceCallback(cir_msgs::Device_Error_Srv::Request & request, cir_msgs::Device_Error_Srv::Response & response)
{
	string command = request.command;

	short errorCode[3] = {0,};
	_rollbendServerProxy->detectingError(errorCode);
	for(int i=0; i<2; i++) {
		response.iParams.push_back(errorCode[i]);
	}
	return RETURN_SUCCESS;
}

bool RollBendHandler::rollbendDataServiceCallback(cir_msgs::Device_Data_Srv::Request & request, cir_msgs::Device_Data_Srv::Response & response)
{
	string command = request.command;

	CRollBendPosition position;
	_rollbendServerProxy->getPosition(position);

	response.dParams.push_back(position.getDegreeRoll());
	response.dParams.push_back(position.getDegreeBend());

	return RETURN_SUCCESS;
}



void RollBendHandler::twistMsgCallback(const geometry_msgs::Twist::ConstPtr& message){
	//ROS_DEBUG("RollBendHandler::twistMsgCallback");

	float rollvel = message->linear.x;
	float bendvel = message->linear.y;

	float rollang = message->angular.x;
	float bendang = message->angular.y;

	_rollbendServerProxy->moveToAbsolutePosition(rollang, bendang, rollvel);
}

} /* namespace devicenode */
} /* namespace cir */
