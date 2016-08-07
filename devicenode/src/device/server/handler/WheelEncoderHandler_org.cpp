#include "WheelEncoderHandler.h"
#include <math.h>
#include <ros/ros.h>
#define PI 3.14159265

using namespace cir::devicenode;

WheelEncoderHandler::WheelEncoderHandler() {
	_PreviousLeftEncoderCounts = 0;
	_PreviousRightEncoderCounts = 0;
	DistancePerCount = (3.14159265 * 0.1524) / 64000;

	_wheelEncoderServerProxy = CWheelEncoderServerProxy::getInstance();
	this->_WHEEL_ENCODER_THREAD_FLAG = false;
	initHandler();
	this->_this_thread = boost::thread(boost::bind(&WheelEncoderHandler::wheelEncoderPublishThread, this));
}

WheelEncoderHandler::~WheelEncoderHandler() {
	this->_WHEEL_ENCODER_THREAD_FLAG = false;
	this->_this_thread.join();
	ROS_DEBUG("[WheelEncoderHandler] closed... ");
}

void WheelEncoderHandler::initHandler() {
	//this->_wheelEncoderServiceServer = this->_nodeHandle.advertiseService("/DeviceNode/WheelEncoderService", &WheelEncoderHandler::wheelEncoderServiceCallback, this);
	//ROS_INFO("WheelEncoder handler created - /DeviceNode/WheelEncoderService");
	this->_wheelEncoderPublisher = this->_nodeHandle.advertise<cir_msgs::Device_WheelEncoder_Msg>("/DeviceNode/WheelEncoder/data", 1000);
	//this->_odom_pub = this->_nodeHandle.advertise<nav_msgs::Odometry>("odom", 50);
	ROS_INFO("WheelEncoderHandler handler created - /DeviceNode/WheelEncoder/data");
}

bool WheelEncoderHandler::wheelEncoderServiceCallback(cir_msgs::Device_WheelEncoder_Srv::Request &request, cir_msgs::Device_WheelEncoder_Srv::Response &response) {

	string command = request.command;

	if(command == COMMAND_WHEEL_ENCODER_READ_DATA) {
		CWheelEncoderData returnData = _wheelEncoderServerProxy->readData(1);
		response.msg.x = returnData.getX();
		response.msg.y = returnData.getY();
		response.msg.t = returnData.getTheta();

		return true;
	} else {
		cout << "[WheelEncoderHandler] unrecognized command. " << endl;
	}
	return false;
}

void WheelEncoderHandler::wheelEncoderPublishThread() {
	this->_WHEEL_ENCODER_THREAD_FLAG = true;
	ros::Rate loop_rate(10);
	tf::TransformBroadcaster odom_broadcaster;
	tf::TransformBroadcaster broadcaster;
	ros::Time current_time, last_time;
	current_time = ros::Time::now();
	last_time = current_time;

	CWheelEncoderData org_data = _wheelEncoderServerProxy->readData(1);
	double org_x = org_data.getX()/100;
	double org_y = org_data.getY()/100;

	double pose_x = 0.0f;
	double pose_y = 0.0f;

	while( ros::ok() && this->_WHEEL_ENCODER_THREAD_FLAG ) {

		cir_msgs::Device_WheelEncoder_Msg message;
		CWheelEncoderData data = _wheelEncoderServerProxy->readData(1);
		message.x = data.getX();
		message.y = data.getY();
		message.t = data.getTheta();
		this->_wheelEncoderPublisher.publish(message);

		//ROS_DEBUG("x : %f  //  y : %f  // z : %f ",data.getX(),data.getY(),data.getTheta());
		//ROS_DEBUG("0 : %f  //  1 : %f  // 2 : %f ",data.getData()[0] , data.getData()[1] , data.getData()[2]);
		
		// Get latest odometry data
		// Translate into ROS message format and publish
		current_time = ros::Time::now();
		double diff_time = (current_time-last_time).toSec();
		
		//ROS_DEBUG("diff time : %ld", diff_time);
		
		double temp_x = data.getX()/100;
		double temp_y = data.getY()/100;
		double temp_th = data.getTheta()*PI/180;
		//double result_x = (temp_x-org_x)*cos(temp_th) + (temp_y-org_y)*sin(temp_th);
		//double result_y = -(temp_x-org_x)*sin(temp_th) + (temp_y-org_y)*cos(temp_th);

	//	double vx = (temp_x-org_x)/diff_time;
	//	double vy = (temp_y-org_y)/diff_time;
	//
	//	double delta_x = (vx*cos(temp_th)-vy*sin(temp_th))*diff_time;
	//	double delta_y = (vx*sin(temp_th)+vy*cos(temp_th))*diff_time;

	//	pose_x += delta_x;
	//	pose_y += delta_y;
		
		//ROS_DEBUG("Wheel encoder value x:%f  // y:%f  // th:%f ", pose_x, pose_y, temp_th);

		this->odomMsgs.pose.pose.position.x = pose_x;
		this->odomMsgs.pose.pose.position.y = pose_y;
		this->odomMsgs.pose.pose.orientation = tf::createQuaternionMsgFromYaw(temp_th);

//		Stg::Velocity v = this->positionmodels[r]->GetVelocity();
		this->odomMsgs.twist.twist.linear.x = 0;
		this->odomMsgs.twist.twist.linear.y = 0;
		this->odomMsgs.twist.twist.angular.z = 0;

		//@todo Publish stall on a separate topic when one becomes available
		//this->odomMsgs[r].stall = this->positionmodels[r]->Stall();
		//
		this->odomMsgs.header.frame_id = "odom";
		this->odomMsgs.header.stamp = current_time;

		this->_odom_pub.publish(this->odomMsgs);

		// broadcast odometry transform
		//tf::Quaternion odomQ;
		//tf::quaternionMsgToTF(odomMsgs.pose.pose.orientation, odomQ);
		//tf::Transform txOdom(odomQ, tf::Point(odomMsgs.pose.pose.position.x, odomMsgs.pose.pose.position.y, 0.0));
		//tfBroadcaster.sendTransform(tf::StampedTransform(txOdom, current_time_encoder,"odom", "base_footprint"));
		geometry_msgs::TransformStamped odom_trans;
		odom_trans.header.stamp = current_time;
		odom_trans.header.frame_id = "odom";
		odom_trans.child_frame_id = "base_link";
		 
		odom_trans.transform.translation.x = pose_x;
		odom_trans.transform.translation.y = pose_y;
		odom_trans.transform.translation.z = 0.0;
		odom_trans.transform.rotation = tf::createQuaternionMsgFromYaw(temp_th);

		//send the transform
		tfBroadcaster.sendTransform(odom_trans);

		broadcaster.sendTransform(
		tf::StampedTransform(
		tf::Transform(tf::Quaternion(0, 0, 0, 1), tf::Vector3(0.1, 0.0, 0.2)),
		ros::Time::now(),"base_link", "laser"));		

		
		deltaLeft = data.getX() - _PreviousLeftEncoderCounts;
		deltaRight = data.getY() - _PreviousRightEncoderCounts;

		vx = deltaLeft * DistancePerCount; // (current_time_encoder - last_time_encoder).toSec();
		vy = deltaRight * DistancePerCount; // (current_time_encoder - last_time_encoder).toSec();

		_PreviousLeftEncoderCounts = data.getX();
		_PreviousRightEncoderCounts = data.getY();


		// make and publish
		double dt = (current_time - last_time).toSec();
		double delta_x = (vx * cos(th) - vy * sin(th)) * dt;
		double delta_y = (vx * sin(th) + vy * cos(th)) * dt;
		double delta_th = vth * dt;

		x += delta_x;
		y += delta_y;
		th += delta_th;

//		//since all odometry is 6DOF we'll need a quaternion created from yaw
//		geometry_msgs::Quaternion odom_quat = tf::createQuaternionMsgFromYaw(th);
//
//		//first, we'll publish the transform over tf
//		geometry_msgs::TransformStamped odom_trans;
//		odom_trans.header.stamp = current_time;
//		odom_trans.header.frame_id = "odom";
//		odom_trans.child_frame_id = "base_link";
//
//		odom_trans.transform.translation.x = x;
//		odom_trans.transform.translation.y = y;
//		odom_trans.transform.translation.z = 0.0;
//		odom_trans.transform.rotation = odom_quat;
//
//		//send the transform
//		odom_broadcaster.sendTransform(odom_trans);
//
//		//next, we'll publish the odometry message over ROS
//		nav_msgs::Odometry odom;
//		odom.header.stamp = current_time;
//		odom.header.frame_id = "odom";
//
//		//set the position
//		odom.pose.pose.position.x = x;
//		odom.pose.pose.position.y = y;
//		odom.pose.pose.position.z = 0.0;
//		odom.pose.pose.orientation = odom_quat;
//
//		//set the velocity
//		odom.child_frame_id = "base_link";
//		odom.twist.twist.linear.x = vx;
//		odom.twist.twist.linear.y = vy;
//		odom.twist.twist.angular.z = vth;

		//publish the message
		//_odom_pub.publish(odom);


		org_x = temp_x;
		org_y = temp_y;
		last_time = current_time;
		ros::spinOnce();
		loop_rate.sleep();
	}
}

