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

void callSaxmlService(ros::NodeHandle nodeHandle) {
	ros::ServiceClient client = nodeHandle.serviceClient<cir_msgs::BehaviorRos_Saxml_Srv>("/behavior_winros/behaviorexpression_SAXML");
	cir_msgs::BehaviorRos_Saxml_Srv srv;
	srv.request.sender = "TestBehavior";
	//srv.request.message = "<sa-message name=\"ExpressionWithSentence\" type=\"request\">          <param name=\"sentenceType\" value=\"idle01\"></param>     <param name=\"emotionID\" value=\"neutral\"></param>     <param name=\"expressionLength\" value=\"short\"></param>     <param name=\"sentence\" value=\"hello good morning.\"></param>     <param name=\"panoffset\" value=\"0\"></param>     <param name=\"tiltoffset\" value=\"0\"></param>     <param name=\"random\" value=\"0\"></param>     <param name=\"recordedSentenceID\" value=\"2\"></param>     <param name=\"wavPosition\" value=\"0\"></param>     <param name=\"speakerID\" value=\"5\"></param> </sa-message>";
	srv.request.message = "<sa-message name=\"ExpressionWithSentence\" type=\"request\">          <param name=\"sentenceType\" value=\"accept\"></param>     <param name=\"emotionID\" value=\"joy\"></param>     <param name=\"expressionLength\" value=\"long\"></param>     <param name=\"sentence\" value=\"hello good morning.\"></param>     <param name=\"panoffset\" value=\"0\"></param>     <param name=\"tiltoffset\" value=\"0\"></param>     <param name=\"random\" value=\"0\"></param>     <param name=\"recordedSentenceID\" value=\"2\"></param>     <param name=\"wavPosition\" value=\"0\"></param>     <param name=\"speakerID\" value=\"5\"></param> </sa-message>";

	if (client.call(srv)) {
		cout << "[TestServiceClient] send message success" << endl;
		cout << "response : " << srv.response.response << endl;
	} else {
		cout << "[TestServiceClient] send message fail" << endl;
	}
}

void callExpressionService(ros::NodeHandle nodeHandle) {

#ifdef WIN32

	ros::ServiceClient client = nodeHandle.serviceClient<cir_msgs::BehaviorRos_Expression_Srv>("/behavior_winros/expression");
	cir_msgs::BehaviorRos_Expression_Srv srv;

	string sentence = "";
	string sentenceType = "";
	string emotionID = "";
	string expressionLength = "";

	cin.clear();
	cout << "input sentenceType : ";
	cin >> sentenceType;
	cin.clear();
	cout << "input emotionID : ";
	cin >> emotionID;
	cin.clear();
	cout << "input expressionLength : ";
	cin >> expressionLength;
	cin.clear();
	cin.ignore();
	cout << "input sentence : ";
	std::getline(cin, sentence);

	cout << "sentence : "<< sentence << endl;


	wchar_t strUnicode[256] = {0,};
	char    strMultibyte[256] = {0,};
	strcpy_s(strMultibyte,256,sentence.c_str());
	int nLen = MultiByteToWideChar(CP_ACP, 0, strMultibyte, strlen(strMultibyte), NULL, NULL);
	MultiByteToWideChar(CP_ACP, 0, strMultibyte, strlen(strMultibyte), strUnicode, nLen);

	char strUtf8[256] ={0,};
	int nnLen = WideCharToMultiByte(CP_UTF8, 0, strUnicode, lstrlenW(strUnicode), NULL, 0, NULL, NULL);
	WideCharToMultiByte (CP_UTF8, 0, strUnicode, lstrlenW(strUnicode), strUtf8, nnLen, NULL, NULL);

	srv.request.sentence = string(strUtf8);
	srv.request.sentenceType = sentenceType;
	srv.request.emotionID = emotionID;
	srv.request.expressionLength = expressionLength;

	if (client.call(srv)) {
		cout << "[TestServiceClient] send message success" << endl;
		cout << "response : " << srv.response.response << endl;
	} else {
		cout << "[TestServiceClient] send message fail" << endl;
	}

#endif
}

void callOnlyLip(ros::NodeHandle nodeHandle) {

#ifdef WIN32
	ros::ServiceClient client = nodeHandle.serviceClient<cir_msgs::BehaviorRos_ExpressionOnlyLip_Srv>("/behavior_winros/expression_onlylip");
	cir_msgs::BehaviorRos_ExpressionOnlyLip_Srv srv;

	string sentence = "";
	string sentenceType = "";
	string emotionID = "";
	string expressionLength = "";

	cin.clear();
	cout << "input sentenceType : ";
	cin >> sentenceType;
	cin.clear();
	cout << "input emotionID : ";
	cin >> emotionID;
	cin.clear();
	cout << "input expressionLength : ";
	cin >> expressionLength;
	cin.clear();
	cin.ignore();
	cout << "input sentence : ";
	std::getline(cin, sentence);

	cout << "sentence : "<< sentence << endl;

	wchar_t strUnicode[256] = {0,};
	char    strMultibyte[256] = {0,};
	strcpy_s(strMultibyte,256,sentence.c_str());
	int nLen = MultiByteToWideChar(CP_ACP, 0, strMultibyte, strlen(strMultibyte), NULL, NULL);
	MultiByteToWideChar(CP_ACP, 0, strMultibyte, strlen(strMultibyte), strUnicode, nLen);

	char strUtf8[256] ={0,};
	int nnLen = WideCharToMultiByte(CP_UTF8, 0, strUnicode, lstrlenW(strUnicode), NULL, 0, NULL, NULL);
	WideCharToMultiByte (CP_UTF8, 0, strUnicode, lstrlenW(strUnicode), strUtf8, nnLen, NULL, NULL);

	srv.request.sentence = string(strUtf8);
	srv.request.sentenceType = sentenceType;
	srv.request.emotionID = emotionID;
	srv.request.expressionLength = expressionLength;

	if (client.call(srv)) {
		cout << "[TestServiceClient] send message success" << endl;
		cout << "response : " << srv.response.response << endl;
	} else {
		cout << "[TestServiceClient] send message fail" << endl;
	}
#endif
}

void callModalityService(ros::NodeHandle nodehandle) {
	ros::ServiceClient client = nodehandle.serviceClient<cir_msgs::BehaviorRos_Modality_Srv>("/behavior_winros/modality");
	cir_msgs::BehaviorRos_Modality_Srv srv;
	string isLeftArm;
	string isRightArm;
	string isNeck;
	string isFace;
	string isLED;
	string isSound;
	string isTTS;
	string isWheel;

	cout << " -- modality useset -- " << endl;
	cout << " left arm (on:1 off:0) : ";
	cin >> isLeftArm;
	cout << " right arm (on:1 off:0) : ";
	cin >> isLeftArm;
	cout << " neck arm (on:1 off:0) : ";
	cin >> isLeftArm;
	cout << " face arm (on:1 off:0) : ";
	cin >> isLeftArm;
	cout << " led arm (on:1 off:0) : ";
	cin >> isLeftArm;
	cout << " sound arm (on:1 off:0) : ";
	cin >> isLeftArm;
	cout << " tts arm (on:1 off:0) : ";
	cin >> isLeftArm;
	cout << " wheel arm (on:1 off:0) : ";
	cin >> isLeftArm;

	srv.request.isLeftArm	= (isLeftArm=="1")	? true : false;
	srv.request.isRightArm	= (isRightArm=="1") ? true : false;
	srv.request.isNeck		= (isNeck=="1")		? true : false;
	srv.request.isFace		= (isFace=="1")		? true : false;
	srv.request.isLED		= (isLED=="1")		? true : false;
	srv.request.isSound		= (isSound=="1")	? true : false;
	srv.request.isTTS		= (isTTS=="1")		? true : false;
	srv.request.isWheel		= (isWheel=="1")	? true : false;

	if (client.call(srv)) {
		cout << "[TestServiceClient] send message success" << endl;
		cout << "response : " << srv.response.response << endl;
	} else {
		cout << "[TestServiceClient] send message fail" << endl;
	}
}

void callIdleService(ros::NodeHandle nodeHandle) {
	ros::ServiceClient client = nodeHandle.serviceClient<cir_msgs::BehaviorRos_Idle_Srv>("/behavior_winros/idle");

	cir_msgs::BehaviorRos_Idle_Srv srv;
	string command;
	cout << " -- idle -- " << endl;
	cout << " idle setting (on:1 off:0) : ";
	cin >> command;

	srv.request.command = (command=="1") ? "true" : "false";
	if (client.call(srv)) {
		cout << "[TestServiceClient] send message success" << endl;
		cout << "response : " << srv.response.response << endl;
	} else {
		cout << "[TestServiceClient] send message fail" << endl;
	}
}

void callSongService(ros::NodeHandle nodeHandle) {
	ros::ServiceClient client = nodeHandle.serviceClient<cir_msgs::BehaviorRos_Song_Srv>("/behavior_winros/song");

	cir_msgs::BehaviorRos_Song_Srv srv;

	string sentenceType = "";
	string emotionID = "";
	string expressionLength = "";


	cin.clear();
	cout << "input sentenceType : ";
	cin >> sentenceType;
	cin.clear();
	cout << "input emotionID : ";
	cin >> emotionID;
	cin.clear();
	cout << "input expressionLength : ";
	cin >> expressionLength;



	srv.request.sentenceType = sentenceType;
	srv.request.emotionID = emotionID;
	srv.request.expressionLength = expressionLength;



	if (client.call(srv)) {
		cout << "[TestServiceClient] send message success" << endl;
		cout << "response : " << srv.response.response << endl;
	} else {
		cout << "[TestServiceClient] send message fail" << endl;
	}
}

void callStopService(ros::NodeHandle nodeHandle) {
	ros::ServiceClient client = nodeHandle.serviceClient<cir_msgs::BehaviorRos_Stop_Srv>("/behavior_winros/stop");

	cir_msgs::BehaviorRos_Stop_Srv srv;
	cout << " -- stop -- " << endl;

	srv.request.command = "stop";
	if (client.call(srv)) {
		cout << "[TestServiceClient] send message success" << endl;
		cout << "response : " << srv.response.response << endl;
	} else {
		cout << "[TestServiceClient] send message fail" << endl;
	}
}

void test33() {
	bool temp = false;
	int temp2 = -1;
	try	{
		temp2 = boost::lexical_cast<int>(temp);
	} catch (boost::bad_lexical_cast e) {
		cout << " ee!! " << endl;
	}
	cout << " ??  : " << temp2 << endl;
}

void test44() {

	string temp = "/work/cir/data/Sound/SoundSource/song/basic_07.wav";
	string songDIR = "";
	string songName = "";

	std::vector<std::string> strs;
	boost::split(strs, temp, boost::is_any_of("/"));
	int size = strs.size();

	songName = strs.at(size-1);

	for(int i=0; i< size-1; i++) {
		songDIR += strs.at(i);
		if(i<size-2) {
			songDIR += "/";
		}
	}
	cout << "songName : " << songName << endl;
	cout << "songDIR : " << songDIR << endl;

	getchar();
}

int main(int argc, char **argv) {

	ros::init(argc, argv, "TestBehavior");

	ros::NodeHandle n;
	//test33();
	string command = "";

	while(ros::ok()) {
		cout << " ===== select command ===== " << endl;
		cout << " 1 . call saxml service "		<< endl;
		cout << " 2 . call expression service " << endl;
		cout << " 3 . call modality service "	<< endl;
		cout << " 4 . call idle service "		<< endl;
		cout << " 5 . call song service "		<< endl;
		cout << " 6 . call stop service "		<< endl;
		cout << " 7 . call only lip service "	<< endl;
		cout << " exit . ctrl+C "				<< endl;
		cout << " ========================== " << endl;
		cin >> command;

		if(command == "1") {
			callSaxmlService(n);
		} else if(command == "2") {
			callExpressionService(n);
		} else if(command == "3") {
			callModalityService(n);
		} else if(command == "4") {
			callIdleService(n);
		} else if(command == "5") {
			callSongService(n);
		} else if(command == "6") {
			callStopService(n);
		} else if(command == "7") {
			callOnlyLip(n);
		} else {
			cout << " command not selected" << endl;
		}
	}

	ros::spin();
	return -1;
}
