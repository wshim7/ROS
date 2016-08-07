#ifndef __ROSCIR_CLIENT_ROLLBEND_H__
#define __ROSCIR_CLIENT_ROLLBEND_H__

#include <roscir/device/common/RollBend.h>
#include <roscir/device/RosCIRDefinitions.h>
#include <roscir/env/Config.h>

#include <iostream>

#include <ros/ros.h>
#include <cir_msgs/Device_Rollbend_Msg.h>
#include <cir_msgs/Device_Error_Srv.h>
#include <cir_msgs/Device_Data_Srv.h>
//#include <cir_msgs/RollBendService.h>

class CIRAPI CRollBendClientProxy
{
private :
	CRollBendClientProxy();
	virtual ~CRollBendClientProxy();
public:
	static CRollBend* newInstance();

};

class CRollBendROSStub : public CRollBend {

private:
	void close();
	ros::NodeHandle			_nodeHandle;
	ros::ServiceClient		_rollbendClient;
	ros::ServiceClient		_rollbendErrorClient;
	ros::ServiceClient		_rollbendPositionDataClient;
	ros::Publisher publisher;

public :
	CRollBendROSStub();
	virtual ~CRollBendROSStub();

	int on();
	int off();
	int stop();
	int moveToHome( int speed );
	int moveToAbsolutePosition( double degreeLeftRight, double degreeUpDown, int speed );
	int moveToAbsolutePositionWithSpeed( double degreeRoll, double degreeBend, int speedRoll, int speedBend );
	int moveToRelativePosition( double degreeLeftRight, double degreeUpDown, int speed );
	int move2MotorSync( int motorID1, int motorSpeed1, int motorPosition1, int motorID2, int motorSpeed2, int motorPosition2 );
	int moveMotor( int motorID, int motorSpeed, int motorPosition );
	void getPosition(CRollBendPosition& pos);
	void detectingError(short errorCode[3]);

};
#endif /* __ROSCIR_CLIENT_ROLLBEND_H__ */
