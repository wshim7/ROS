#include "EGyroCore.h"

EGyroCore::EGyroCore() {
	_comPort = "COM-1";
	_INIT_FLAG = false;
	init();
}

EGyroCore::~EGyroCore() {
	this->_this_thread.join();
}

void EGyroCore::init() {
//	CConfig* config		= CConfig::getInstance();
//	_comPort			= config->getParamValue("GYRO_COM_PORT");
//	int eBaudNumber		= config->getParamValueInt("GYRO_EBaudrate");
//
//	_conn.setup(_comPort,eBaudNumber);
//
//	this->_this_thread = boost::thread(boost::bind(&EGyroCore::run,this));
}

CGyroData EGyroCore::getData() {
	CGyroData data(this->_rateResult,this->_angleResult);
	return data;
}

void EGyroCore::run() {
	
	//char szBuffer[101];

//	while(ros::ok()) {
//		unsigned char* buffer = new unsigned char[100];
//		int readSize = 100;
//
//		short header;
//		short rate;
//		short angle;
//		short check_sum;
//
//		_conn.readBytes(buffer,100);
//		memcpy(&header, buffer, sizeof(short));
//
//		if(header != (short)0xFFFF){
//
//		} else	{
//			// Copy values from data string
//			memcpy(&rate, buffer+2, sizeof(short));
//			memcpy(&angle, buffer+4, sizeof(short));
//			memcpy(&check_sum, buffer+6, sizeof(short));
//
//			// Verify checksum
//			if(check_sum != (short)(0xFFFF+rate+angle))	{
//
//			} else {
//				double m_dAngle, m_dData;
//				m_dAngle = (double)angle;
//				if(_INIT_FLAG == false) {
//					_init_angle = m_dAngle/100.0;
//					_INIT_FLAG = true;
//				}
//
//				m_dData = -(m_dAngle/100.0 - _init_angle);
//
//				this->_rateResult = rate;
//				this->_angleResult = m_dData;
//			}
//		}
//		delete[] buffer;
//	}
}
