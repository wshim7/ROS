/*
 * HeadFaceMock.cpp
 *
 *  Created on: 2014. 2. 11.
 *      Author: msyoo
 */


#include "HeadFaceServer.h"


CHeadFaceMock::CHeadFaceMock()
{
}



CHeadFaceMock::~CHeadFaceMock()
{
}

int  CHeadFaceMock::on()
{
	ROS_DEBUG("CHeadFaceMock::on");
	return 0;
}

int  CHeadFaceMock::off()
{
	ROS_DEBUG("CHeadFaceMock::off");
	return 0;
}


int CHeadFaceMock::express(string emotion, double intensity, int duration)
{
	ROS_DEBUG("CHeadFaceMock::express %s %f %d", emotion.c_str(), intensity, duration);
	return 0;
}



int CHeadFaceMock::moveAbsolutePosition(int motorID, int speed, int position)
{
	ROS_DEBUG("CHeadFaceMock::moveAbsolutePosition %d %d %d", motorID, speed, position);
	return 0;
}


int CHeadFaceMock::moveAbsolutePosition( int motorID, double degree, int speed )
{
	ROS_DEBUG("CHeadFaceMock::moveAbsolutePosition Double Degree %d %f %d", motorID, degree, speed);
	return 0;
}


int CHeadFaceMock::moveLip(string visemeTime)
{
	ROS_DEBUG("CHeadFaceMock::moveLip %s", visemeTime.c_str());
	return 0;
}



int CHeadFaceMock::moveLipViseme(int visemeID)
{
	ROS_DEBUG("CHeadFaceMock::moveLipViseme %d", visemeID);
	return 0;
}



int CHeadFaceMock::changeAvatar(int avatarType)
{
	ROS_DEBUG("CHeadFaceMock::changeAvatar %d", avatarType);
	return 0;
}
