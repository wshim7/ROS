/*
 * CHeadFaceClient.h
 *
 *  Created on: 2014. 2. 13.
 *      Author: msyoo
 */

#ifndef CHEADFACECLIENT_H_
#define CHEADFACECLIENT_H_

#include <iostream>
#include <ros/ros.h>
#include <roscir/device/common/HeadFace.h>
#include <roscir/device/RosCIRDefinitions.h>
#include <roscir/env/Config.h>
#include <cir_msgs/Device_Headface_Msg.h>


class CIRAPI CHeadFaceClientProxy
{
private :
	CHeadFaceClientProxy();
	virtual ~CHeadFaceClientProxy();
public:
	static CHeadFace* newInstance();

};

class CHeadFaceROSStub : public CHeadFace {

private:
	ros::NodeHandle			_nodeHandle;
	ros::ServiceClient		_rollbendClient;
	ros::Publisher publisher;

public :
	CHeadFaceROSStub();
	virtual ~CHeadFaceROSStub();
	int on();
	int off();
	int express( string emotion, double intensity, int duration );
	int moveAbsolutePosition( int motorID, int speed, int position );
	int moveAbsolutePosition( int motorID, double degree, int speed );
	int moveLip( string visemeTime );
	int moveLipViseme(int visemeID);
	int changeAvatar(int avatarType);

};



#endif /* CHEADFACECLIENT_H_ */
