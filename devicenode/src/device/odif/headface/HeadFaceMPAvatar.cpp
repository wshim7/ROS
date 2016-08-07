/*
 * HeadFaceAvatar.cpp
 *
 *  Created on: 2014. 2. 11.
 *      Author: msyoo
 */

#include "HeadFaceServer.h"
#include <cir_msgs/AvatarRos_Expression_Srv.h>
#include <cir_msgs/AvatarRos_MoveFace_Srv.h>
#include <cir_msgs/AvatarRos_FaceFactor_Srv.h>

CHeadFaceMPAvatar::CHeadFaceMPAvatar()
{
	expressionClient = n.serviceClient<cir_msgs::AvatarRos_Expression_Srv>("/avatar_ros/expression", false);
	moveFaceClient = n.serviceClient<cir_msgs::AvatarRos_MoveFace_Srv>("/avatar_ros/move_face", false);
	faceFactorClient = n.serviceClient<cir_msgs::AvatarRos_FaceFactor_Srv>("/avatar_ros/set_face_factor", false);
}



CHeadFaceMPAvatar::~CHeadFaceMPAvatar()
{
}

int  CHeadFaceMPAvatar::on()
{
	return 0;
}

int  CHeadFaceMPAvatar::off()
{
	return 0;
}

CHeadFaceMPAvatar *CHeadFaceMPAvatar::getInstance()
{
	static CHeadFaceMPAvatar thisInstance;
	cout << "[CHeadFaceAvatar.getInstance] : Create Sole Instance(HeadFace).." << endl;
	return &thisInstance;
}



int CHeadFaceMPAvatar::express(string emotion, double intensity, int duration)
{
	cir_msgs::AvatarRos_Expression_Srv srv;
	srv.request.opname = emotion;
	srv.request.weight = intensity;
	srv.request.duartion = duration;

	ROS_DEBUG("wating for service available in CHeadFaceAvatar");
	bool success = ros::service::waitForService("/avatar_ros/expression");
	if(!success) {
		ROS_ERROR("/avatar_ros/expression  not available");
	} else {
		ROS_DEBUG("/avatar_ros/expression available.");
	}

	if(expressionClient.call(srv)){
		ROS_INFO("%s", srv.response.result.c_str());

	}else{
		ROS_ERROR("expression service unavailable..");
	}
	return 0;
}



int CHeadFaceMPAvatar::moveAbsolutePosition(int motorID, int speed, int position)
{
	ROS_DEBUG("CHeadFaceMPAvatar::moveAbsolutePosition called %d, %d, %d", motorID, speed, position);
	return 0;
}

int CHeadFaceMPAvatar::moveAbsolutePosition(int motorID, double degree, int speed)
{
	ROS_DEBUG("CHeadFaceMPAvatar::moveAbsolutePosition called %d, %f, %d", motorID, degree, speed);
	return 0;
}


int CHeadFaceMPAvatar::moveLip(string visemeTime)
{
	ROS_DEBUG("CHeadFaceMPAvatar::moveLip called %s", visemeTime.c_str());
	return 0;
}



int CHeadFaceMPAvatar::moveLipViseme(int visemeID)
{
	cir_msgs::AvatarRos_MoveFace_Srv srv;
	//srv.request.opname =

	if(visemeID == 0){
		srv.request.opname = "closemouth";
	}else if(visemeID == 1){
		srv.request.opname = "moutha";
	}else if(visemeID == 5 || 6){
		srv.request.opname = "mouthe";
	}else if(visemeID == 9 || 11){
		srv.request.opname = "moutho";
	}else{
		srv.request.opname = "moutha";
	}

	srv.request.weight = 1.0;
	srv.request.duration = 200;

	ROS_DEBUG("wating for service available in CHeadFaceAvatar");
	bool success = ros::service::waitForService("/avatar_ros/move_face");
	if(!success) {
		ROS_ERROR("/avatar_ros/move_face  not available");
	} else {
		ROS_DEBUG("/avatar_ros/move_face available.");
	}

	if(moveFaceClient.call(srv)){
		ROS_INFO("%s", srv.response.result.c_str());

	}else{
		ROS_ERROR("move_face service unavailable..");
	}
	return 0;
}



int CHeadFaceMPAvatar::changeAvatar(int avatarType)
{
	cir_msgs::AvatarRos_FaceFactor_Srv srv;
	srv.request.opname = "changeAvatar";
	srv.request.type = avatarType;

	bool success = ros::service::waitForService("/avatar_ros/set_face_factor");
	if(!success) {
		ROS_ERROR("set_face_factor service is not available yet!!");
	} else {
		ROS_INFO("set_face_factor service available..");
	}

	if(faceFactorClient.call(srv)){
		ROS_INFO("%s", srv.response.result.c_str());

	}else{
		ROS_ERROR("set_face_factor service unavailable..");
	}
	return 0;
}


