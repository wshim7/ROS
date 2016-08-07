#include <ros/ros.h>
#include <time.h>
#include <iostream>
#include <cir_msgs/BehaviorRos_Saxml_Srv.h>
#include <cir_msgs/BehaviorRos_Expression_Srv.h>
#include <cir_msgs/BehaviorRos_Modality_Srv.h>
#include <cir_msgs/BehaviorRos_Idle_Srv.h>
#include <cir_msgs/BehaviorRos_Stop_Srv.h>
#include <cir_msgs/BehaviorRos_Song_Srv.h>
#include <cir_msgs/BehaviorRos_ExpressionOnlyLip_Srv.h>
#include <ros/package.h>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>


using namespace std;


int main(int argc, char **argv) {

	ros::init(argc, argv, "TestBehavior");

	ros::NodeHandle nodeHandle;

	cout << "Start behavior loop test" << endl;

	ros::ServiceClient client = nodeHandle.serviceClient<cir_msgs::BehaviorRos_Expression_Srv>("/behavior_winros/expression");
	cir_msgs::BehaviorRos_Expression_Srv srv;


	srv.request.sentence = string("test");
	srv.request.sentenceType = "accept";
	srv.request.emotionID = "joy";
	srv.request.expressionLength = "long";

	while(true) {
		client.call(srv);
	}

//	if (client.call(srv)) {
//		cout << "[TestServiceClient] send message success" << endl;
//	} else {
//		cout << "[TestServiceClient] send message fail" << endl;
//	}

	ros::spin();
	return -1;
}
