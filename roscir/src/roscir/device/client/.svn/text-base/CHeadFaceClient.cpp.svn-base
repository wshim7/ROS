/*
 * CHeadFaceClient.cpp
 *
 *  Created on: 2014. 2. 13.
 *      Author: msyoo
 */

#include "CHeadFaceClient.h"


CHeadFaceClientProxy::CHeadFaceClientProxy()
{
}



CHeadFaceClientProxy::~CHeadFaceClientProxy()
{
}



CHeadFace *CHeadFaceClientProxy::newInstance()
{
	return new CHeadFaceROSStub();
}



CHeadFaceROSStub::CHeadFaceROSStub()
{
	this->publisher = this->_nodeHandle.advertise<cir_msgs::Device_Headface_Msg>("/DeviceNode/HeadFace/commands", 1000);
	ROS_DEBUG("headface publisher created");

	while(this->publisher.getNumSubscribers() < 1) {
		ros::Duration(0.5).sleep();
		ros::spinOnce();
		ROS_DEBUG("wait for subscriber");
	}
}



CHeadFaceROSStub::~CHeadFaceROSStub()
{
}

int  CHeadFaceROSStub::on()
{
	cir_msgs::Device_Headface_Msg msg;
	msg.command = COMMAND_HEADFACE_ON;
	publisher.publish(msg);
	ros::spinOnce();
	return 0;
}
int  CHeadFaceROSStub::off()
{
	cir_msgs::Device_Headface_Msg msg;
	msg.command = COMMAND_HEADFACE_OFF;
	publisher.publish(msg);
	ros::spinOnce();
	return 0;
}

int CHeadFaceROSStub::express(string emotion, double intensity, int duration)
{
	cir_msgs::Device_Headface_Msg msg;
	msg.command = COMMAND_HEADFACE_EXPRESS;
	msg.emotion = emotion;
	msg.intensity = intensity;
	msg.duration = duration;
	publisher.publish(msg);
	ros::spinOnce();
	return 0;
}



int CHeadFaceROSStub::moveAbsolutePosition(int motorID, int speed, int position)
{
	cir_msgs::Device_Headface_Msg msg;
	msg.command = COMMAND_HEADFACE_MOVE_ABSOLUTE_POSITION;
	msg.motorID.push_back(motorID);
	msg.speeds.push_back(speed);
	msg.angles.push_back((double)position);
	publisher.publish(msg);
	ros::spinOnce();
	return 0;
}


int CHeadFaceROSStub::moveAbsolutePosition( int motorID, double degree, int speed )
{
	cir_msgs::Device_Headface_Msg msg;
	msg.command = COMMAND_HEADFACE_MOVE_ABSOLUTE_POSITION_DOUBLE;
	msg.motorID.push_back(motorID);
	msg.angles.push_back(degree);
	msg.speeds.push_back(speed);
	publisher.publish(msg);
	ros::spinOnce();
	return 0;
}


int CHeadFaceROSStub::moveLip(string visemeTime)
{
	cir_msgs::Device_Headface_Msg msg;
	msg.command = COMMAND_HEADFACE_MOVE_LIP_VISEME_TIME;
	msg.visemeTime = visemeTime;
	publisher.publish(msg);
	ros::spinOnce();
	return 0;
}



int CHeadFaceROSStub::moveLipViseme(int visemeID)
{
	cir_msgs::Device_Headface_Msg msg;
	msg.command = COMMAND_HEADFACE_MOVE_LIP_VISEME;
	msg.lipID = visemeID;
	publisher.publish(msg);
	ros::spinOnce();
	return 0;
}



int CHeadFaceROSStub::changeAvatar(int avatarType)
{
	cir_msgs::Device_Headface_Msg msg;
	msg.command = COMMAND_HEADFACE_CHANGE_AVATAR;
	msg.avatarType = avatarType;
	publisher.publish(msg);
	ros::spinOnce();
	return 0;
}

