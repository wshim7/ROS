#include "GyroServer.h"

CGyroERobotSimul::CGyroERobotSimul() 
{
	//wsock = new WSocket();
	//const char* host = CConfig::getInstance()->getParamValue("SIMULATOR_IP");
	//const char* port = CConfig::getInstance()->getParamValue("SIMULATOR_PORT");
	//int ret = wsock->connectSocket(host, atoi(port));
	//logger = Logger::getLogger("CGyroERobotSimul");
	//LOG4CXX_DEBUG(logger, "CGyroERobotSimul constructor");
	//if (ret == 0 ) {
	//	cout << " ............ connect simulator failed ................." << endl;
	//	isConnect = false;
	//} else {
	//	isConnect = true;
	//	cout << "CGyroERobotSimul " << endl;
	//}
}

CGyroERobotSimul::~CGyroERobotSimul() {
}

CGyro* CGyroERobotSimul::getInstance( )
{
	static CGyroERobotSimul* thisInstance;
	return thisInstance;
}

CGyroData CGyroERobotSimul::readData() {
	
//	wsock->writeHeader(SIMUL_COMMAND_GYRO);
//
////	cout << " gyrodata size : " << sizeof(GYRODATA) << endl;
//	// readDAta
//	GYRODATA retPacket;	
//	memset(&retPacket, 0x00, sizeof(GYRODATA));
//	int nRead = wsock->read(&retPacket, sizeof(GYRODATA));
////	cout << "CGyroERobotSimul. readByte : " << nRead << endl;
//	int nRet = SimulCommonUtil::getInstance()->checkHeader(retPacket.header, 0x1f, 4);
////	cout << "CGyroERobotSimul.readData] checkHeader (0:OK, -1:failed) : " << nRet << endl;
////	cout << "angle : "  << retPacket.angle  << endl;
//	
//	short rate = 0;
//	double angle = 0;
//
///**
//	if(angle > 0) {
//		angle = angle-360;
//	}
//	return CGyroData(0, retPacket.angle);
//*/
	return CGyroData(0, 0.0);	
}

void CGyroERobotSimul::run() {

}
