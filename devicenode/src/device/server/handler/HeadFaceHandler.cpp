/*
 * HeadFaceHandler.cpp
 *
 *  Created on: 2014. 2. 13.
 *      Author: msyoo
 */

#include "HeadFaceHandler.h"

namespace cir {
namespace devicenode {

HeadFaceHandler::HeadFaceHandler() {
	initHandler();
	_headfaceServerProxy = CHeadFaceServerProxy::getInstance();

}

HeadFaceHandler::~HeadFaceHandler() {
}

void HeadFaceHandler::initHandler()
{
	this->_headfaceSubscriber = this->_nodeHandle.subscribe<cir_msgs::Device_Headface_Msg>("/DeviceNode/HeadFace/commands", 1000, &HeadFaceHandler::headfaceSubscriberCallback, this);
	ROS_INFO("HeadFace handler created - /DeviceNode/HeadFace/commands");
}

void HeadFaceHandler::headfaceSubscriberCallback(const cir_msgs::Device_Headface_Msg::ConstPtr & message)
{
	string command = message->command;

	if(command == COMMAND_HEADFACE_ON){
		_headfaceServerProxy->on();

	}else if(command == COMMAND_HEADFACE_OFF ){
		_headfaceServerProxy->off();

	}else  if(command == COMMAND_HEADFACE_EXPRESS){
		_headfaceServerProxy->express(message->emotion, message->intensity, message->duration);

	}else if(command == COMMAND_HEADFACE_MOVE_ABSOLUTE_POSITION ){
		_headfaceServerProxy->moveAbsolutePosition(message->motorID.at(0), message->speeds.at(0), (int) message->angles.at(0));
		//ROS_DEBUG("HeadFaceHandler Values: ID: %d, Degree: %f, Speed: %d", message->motorID.at(0),  message->angles.at(0), message->speeds.at(0));

	}else if(command == COMMAND_HEADFACE_MOVE_ABSOLUTE_POSITION_DOUBLE ){
		_headfaceServerProxy->moveAbsolutePosition(message->motorID.at(0), message->angles.at(0), message->speeds.at(0));
		//ROS_DEBUG("HeadFaceHandler Values: ID: %d, Degree: %f, Speed: %d", message->motorID.at(0),  message->angles.at(0), message->speeds.at(0));

	}else if(command == COMMAND_HEADFACE_MOVE_LIP_VISEME_TIME ){
		_headfaceServerProxy->moveLip(message->visemeTime);

	}else if(command == COMMAND_HEADFACE_MOVE_LIP_VISEME ){
		_headfaceServerProxy->moveLipViseme(message->lipID);

	}else if(command == COMMAND_HEADFACE_CHANGE_AVATAR ){
		_headfaceServerProxy->changeAvatar(message->avatarType);
	}else{
		ROS_INFO("[HeadFaceHandler] unrecognized command called!!");
	}
	ROS_DEBUG("HeadFaceHandler subscriber finished [%s]", message->command.c_str());

}


} /* namespace devicenode */
} /* namespace cir */
