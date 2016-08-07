#include "WheelEncoderServer.h"

CWheelEncoderERobotSimul::CWheelEncoderERobotSimul()
{
	/*wsock = new WSocket();
	const char* host = CConfig::getInstance()->getParamValue("SIMULATOR_IP");
	const char* port = CConfig::getInstance()->getParamValue("SIMULATOR_PORT");
	wsock->connectSocket(host, atoi(port));
	cout << "ERobotWheelEncoder. Simul... " << endl;*/
}

CWheelEncoderERobotSimul::~CWheelEncoderERobotSimul() 
{
	/*wsock->closeSocket();
	delete host;
	delete port;
	delete wsock;*/
}

CWheelEncoderData CWheelEncoderERobotSimul::readData(int index) 
{
	//wsock->writeHeader(SIMUL_COMMAND_WHEELENCODER);

	////cout << " CWheelEncoderData size : " << sizeof(WHEELENCODERDATA) << endl;
	//// readDAta
	//WHEELENCODERDATA retPacket;	
	//memset(&retPacket, 0x00, sizeof(WHEELENCODERDATA));
	//int nRead = wsock->read(&retPacket, sizeof(WHEELENCODERDATA));
	//cout << "WHEELENCODERDATASimul. readByte : " << nRead << endl;
	//int nRet = SimulCommonUtil::getInstance()->checkHeader(retPacket.header, 0x1d, 12);
	//cout << "WHEELENCODERDATASimul.readData] checkHeader (0:OK, -1:failed) : " << nRet << endl;
	//long data[3] = {0,0,0};
	//CWheelEncoderData encoderData(data, retPacket.x, retPacket.y, retPacket.theta, 3);
	//return encoderData;

	CWheelEncoderData encoderData(0, 0, 0, 0, 3);
	return encoderData;
}
