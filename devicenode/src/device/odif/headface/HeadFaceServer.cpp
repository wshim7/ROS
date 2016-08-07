/*
 * HeadFaceServer.cpp
 *
 *  Created on: 2014. 2. 11.
 *      Author: msyoo
 */

#include "HeadFaceServer.h"


CHeadFaceServerProxy::CHeadFaceServerProxy()
{
	int typeOfServer	= CConfig::getInstance()->getParamValueInt( "SERVER_DEVICE_TYPE" );
	int typeOfRobot	= CConfig::getInstance()->getParamValueInt( "ROBOT_TYPE" );
	int typeOfHeadFace  = CConfig::getInstance()->getParamValueInt( "HEAD_FACE_TYPE" );
	ROS_DEBUG("[CHeadFaceServerProxy] robot type : %d", typeOfRobot);
	ROS_DEBUG("[CHeadFaceServerProxy] server type : %d",typeOfServer);

	if(typeOfServer == SERVER_DEVICE_MOCK) {
		headFace = new CHeadFaceMock();
	} else {
		switch (typeOfRobot) {
			case ROBOT_TYPE_MERO :
				if(typeOfServer == SERVER_DEVICE_REAL) {

					if(typeOfHeadFace == REAL_HARDWARE ){
						headFace = new CHeadFaceMero();
					}else if(typeOfHeadFace == AVATAR){
						headFace = new CHeadFaceMPAvatar();
					}

				} else if( typeOfServer == SERVER_DEVICE_SIMULATOR) {

				} else if( typeOfServer == SERVER_DEVICE_BOTH) {
					if(typeOfHeadFace == REAL_HARDWARE ){
						headFace = new CHeadFaceMero();
					}else if(typeOfHeadFace == AVATAR){
						headFace = new CHeadFaceMPAvatar();
					}
				}
				break;

			case ROBOT_TYPE_MERO_S :

				if(typeOfServer == SERVER_DEVICE_REAL) {
					if(typeOfHeadFace == REAL_HARDWARE ){

					}else if(typeOfHeadFace == AVATAR){
						headFace = new CHeadFaceMPAvatar();
					}
				} else if( typeOfServer == SERVER_DEVICE_SIMULATOR) {

				} else if( typeOfServer == SERVER_DEVICE_BOTH) {
					if(typeOfHeadFace == REAL_HARDWARE ){

					}else if(typeOfHeadFace == AVATAR){
						headFace = new CHeadFaceMPAvatar();
					}
				}
				break;

			case ROBOT_TYPE_FRI :
				ROS_DEBUG("try to create HeadfaceFRI");
				headFace = CHeadFaceFRIRTAI::getInstance();
				ROS_DEBUG("HeadFaceFRIRTAI created");
				break;
			default:
				cout << "default PantiltServerMock " << endl;
				headFace = new CHeadFaceMock();
				break;
		}
	}
}

CHeadFaceServerProxy::~CHeadFaceServerProxy()
{
}

CHeadFace *CHeadFaceServerProxy::getInstance()
{
	static CHeadFaceServerProxy instance;
	return &instance;
}

int  CHeadFaceServerProxy::on()
{
	return headFace->on();
}

int  CHeadFaceServerProxy::off()
{
	return headFace->off();
}

int CHeadFaceServerProxy::express(string emotion, double intensity, int duration)
{
	return headFace->express(emotion, intensity, duration);
}

int CHeadFaceServerProxy::moveAbsolutePosition(int motorID, int speed, int position)
{
	return headFace->moveAbsolutePosition(motorID, speed, position);
}

int CHeadFaceServerProxy::moveAbsolutePosition(int motorID, double degree, int speed)
{
	return headFace->moveAbsolutePosition(motorID, degree, speed);
}

int CHeadFaceServerProxy::moveLipViseme(int visemeID)
{
	return headFace->moveLipViseme(visemeID);
}

int CHeadFaceServerProxy::moveLip(string visemeTime)
{
	return headFace->moveLip(visemeTime);
}

int CHeadFaceServerProxy::changeAvatar(int avatarType)
{
	return headFace->changeAvatar(avatarType);
}










