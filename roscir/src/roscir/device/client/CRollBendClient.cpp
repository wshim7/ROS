#include "CRollBendClient.h"

CRollBendClientProxy::CRollBendClientProxy()
{
}

CRollBendClientProxy::~CRollBendClientProxy()
{
}



CRollBend* CRollBendClientProxy::newInstance() {// throw (SocketException, ConnectException) {
	return new CRollBendROSStub();
}

CRollBendROSStub::CRollBendROSStub() {
	this->publisher = this->_nodeHandle.advertise<cir_msgs::Device_Rollbend_Msg>("/DeviceNode/Rollbend/commands", 1000);
	this->_rollbendErrorClient = this->_nodeHandle.serviceClient<cir_msgs::Device_Error_Srv>("/DeviceNode/RollbendErrorService",true);
	this->_rollbendPositionDataClient = this->_nodeHandle.serviceClient<cir_msgs::Device_Data_Srv>("/DeviceNode/RollbendtDataService",true);

	ROS_DEBUG("rollbend publisher created");

	while(this->publisher.getNumSubscribers() < 1) {
		ros::Duration(0.5).sleep();
		ros::spinOnce();
		ROS_DEBUG("wait for subscriber");
	}

}


CRollBendROSStub::~CRollBendROSStub()
{

}

void CRollBendROSStub::close() { // throw (IOException) {
}

int CRollBendROSStub::on()
{
	cir_msgs::Device_Rollbend_Msg msg;
	msg.command = COMMAND_ROLLBEND_ON;
	publisher.publish(msg);
	ros::spinOnce();
	return 0;
}


int CRollBendROSStub::off()
{
	cir_msgs::Device_Rollbend_Msg msg;
	msg.command = COMMAND_ROLLBEND_OFF;
	publisher.publish(msg);
	ros::spinOnce();
	return 0;
}


int CRollBendROSStub::stop()
{
	cir_msgs::Device_Rollbend_Msg msg;
	msg.command = COMMAND_ROLLBEND_STOP;
	publisher.publish(msg);
	ros::spinOnce();
	return 0;
}


int CRollBendROSStub::moveToHome( int speed )
{
	cir_msgs::Device_Rollbend_Msg msg;
	msg.command = COMMAND_ROLLBEND_MOVE_TO_HOME;
	msg.speeds.push_back(speed);
	publisher.publish(msg);
	ros::spinOnce();
	return 0;
}


int CRollBendROSStub::moveToAbsolutePosition( double degreeLeftRight, double degreeUpDown, int speed )
{
	cir_msgs::Device_Rollbend_Msg msg;
	msg.command = COMMAND_ROLLBEND_MOVE_ABSOLUTE_POSITION;
	msg.angles.push_back(degreeLeftRight);
	msg.angles.push_back(degreeUpDown);
	msg.speeds.push_back(speed);
	publisher.publish(msg);
	ros::spinOnce();
	return 0;
}


int CRollBendROSStub::moveToAbsolutePositionWithSpeed(double degreeRoll, double degreeBend, int speedRoll, int speedBend)
{
	cir_msgs::Device_Rollbend_Msg msg;
	msg.command = COMMAND_ROLLBEND_MOVE_ABSOLUTE_POSITION_WITH_SPEED;
	msg.angles.push_back(degreeRoll);
	msg.angles.push_back(degreeBend);
	msg.speeds.push_back(speedRoll);
	msg.speeds.push_back(speedBend);
	publisher.publish(msg);
	ros::spinOnce();
	return 0;
}


int CRollBendROSStub::moveToRelativePosition( double degreeLeftRight, double degreeUpDown, int speed )
{
	return 0;
}


int CRollBendROSStub::move2MotorSync( int motorID1, int motorSpeed1, int motorPosition1, int motorID2, int motorSpeed2, int motorPosition2 )
{
	return 0;
}


int CRollBendROSStub::moveMotor( int motorID, int motorSpeed, int motorPosition )
{
	return 0;
}


void CRollBendROSStub::getPosition(CRollBendPosition& rollBendPosition)
{
	cir_msgs::Device_Data_Srv service;
	service.request.command = COMMAND_ROLLBEND_GETPOSITION;
	if(_rollbendPositionDataClient.call(service)) {
		//ROS_INFO("[CPanTiltROSStub] COMMAND_ROLLBEND_GETPOSITION success");
		rollBendPosition.setDegreeRoll(service.response.dParams.at(0));
		rollBendPosition.setDegreeBend( service.response.dParams.at(1));
	} else {
		//ROS_ERROR("[CPanTiltROSStub] COMMAND_ROLLBEND_GETPOSITION fail");
	}
}

void CRollBendROSStub::detectingError(short errorCode[3])
{
	cir_msgs::Device_Error_Srv service;
	service.request.command = COMMAND_ROLLBEND_DETECTING_ERROR;
	if(_rollbendErrorClient.call(service)) {
		//ROS_INFO("[CRollBendROSStub] COMMAND_ROLLBEND_DETECTING_ERROR success");
		for(int i=0; i<3; i++) {
			errorCode[i] = (short)service.response.iParams.at(i);
		}
	} else {
		//ROS_ERROR("[CRollBendROSStub] COMMAND_ROLLBEND_DETECTING_ERROR fail");
	}
}
