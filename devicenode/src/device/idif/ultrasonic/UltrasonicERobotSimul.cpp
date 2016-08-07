#include "UltrasonicServer.h"

CUltrasonicERobotSimul::CUltrasonicERobotSimul()
{
	////wsock = new WSocket();
	//session = new SimulatorClientSession();
	//const char* host = CConfig::getInstance()->getParamValue("SIMULATOR_IP");
	//int port = CConfig::getInstance()->getParamValueInt("SIMULATOR_PORT");
	//this->session->connect(string(host), port);
	//logger = Logger::getLogger("CUltrasonicERobotSimul");
	//LOG4CXX_DEBUG(logger, "CUltrasonicERobotSimul constructor");
	//if(host == NULL || port == -1) {
	//	cout << " ............ connect simulator failed ................." << endl;
	//	isConnect = false;
	//} else {
	//	isConnect = true;
	//	cout << "CUltrasonicERobotSimul " << endl;
	//}	
}


CUltrasonicERobotSimul::~CUltrasonicERobotSimul()
{
	/*if(this->session) {
		session->close();
		delete session;
		session = NULL;
	}*/
}

CUltrasonic* CUltrasonicERobotSimul::getInstance( )
{
	static CUltrasonicERobotSimul thisInstance;
	return &thisInstance;
}


CUltrasonicData CUltrasonicERobotSimul::readData(int index)
{	
	//SimulatorMessageSender* sender = this->session->getMessageSender();
	//SimulatorMessageReceiver* receiver = this->session->getMessageReceiver();

	////cout << "CUltrasonicERobotSimul::readData" << endl;
	//unsigned short result[CUltrasonicData::NUMBER_OF_DATA];

	//sender->send(SIMUL_COMMAND_ULTRASONIC);

	////cout << " CUltrasonicERobotSimul size : " << sizeof(ULTRASONICDATA) << endl;
	//// readDAta
	//ULTRASONICDATA retPacket;	
	//memset(&retPacket, 0x00, sizeof(ULTRASONICDATA));

	//int nRead = receiver->read((unsigned char*)&retPacket, sizeof(ULTRASONICDATA));
	////cout << "CUltrasonicERobotSimul.readByte : " << nRead << endl;
	//int nRet = SimulCommonUtil::getInstance()->checkHeader(retPacket.header, 0x1e, 16);
	////cout << "CUltrasonicERobotSimul.readData] checkHeader (0:OK, -1:failed) : " << nRet << endl;

	//result[0] = retPacket.data0;
	//result[1] = retPacket.data1;
	//result[2] = retPacket.data2;
	//result[3] = retPacket.data3;
	//result[4] = retPacket.data4;
	//result[5] = retPacket.data5;
	//result[6] = retPacket.data6;
	//result[7] = retPacket.data7;

	//for(int i=0 ; i<8; i++) {
	//	if(result[i] == 0 || result[i] > 600) {
	//		result[i] = 600;
	//	}
	//}
	//result[8] = 0;
	//result[9] = 0;
	//result[10] = 0;
	//result[11] = 0;
	unsigned short result[CUltrasonicData::NUMBER_OF_DATA];
	CUltrasonicData ultrasonicData(0,0, result);
	return ultrasonicData;
}


void CUltrasonicERobotSimul::close() {

	
}