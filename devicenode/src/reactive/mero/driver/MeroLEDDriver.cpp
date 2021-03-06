#include "MeroLEDDriver.h"

using namespace std;
using namespace reactive::mero::driver;

pthread_mutex_t MeroLEDDriver::__comunicate_mutex = PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP;

MeroLEDDriver::MeroLEDDriver() {
	_current_led_command = 0x00;
	memset(_current_led_data, 0x00, sizeof(unsigned char) * MERO_LED_DATA_PACKET_SIZE);
	utility = MeroFunctionFactory::getInstance();

	connector = MeroLEDTouchConnector::getInstance();

//	InitializeCriticalSection(&comunicate);

}

MeroLEDDriver::~MeroLEDDriver() {

}


MeroLEDDriver* MeroLEDDriver::getInstance()
{
	static MeroLEDDriver thisInstance;
	cout << "[MeroLEDDriver.getInstance] : Create Sole Instance(MeroLEDDriver).." << endl;
	return &thisInstance;
}

void MeroLEDDriver::setLEDCommandPacket( unsigned char* buffer) {
	int nCheckSumSize	= MERO_CHECKSUM_PACKET_SIZE;
	int nBodySize		= MERO_COMMON_HEADER_PACKET_SIZE + MERO_LED_DATA_PACKET_SIZE + nCheckSumSize;

	memset(buffer, 0x00, nBodySize);

	unsigned char checksum = utility->getChecksumWithNoOffset(_current_led_data, MERO_LED_DATA_PACKET_SIZE);

	buffer[0] = MERO_DEVICE_LED_ID;
	buffer[1] = MERO_DEVICE_LED_SUB_ID_1;
	buffer[2] = MERO_DEVICE_LED_SUB_ID_2;
	buffer[3] = _current_led_command;
	for( int i=0 ; i<MERO_LED_DATA_PACKET_SIZE ; i++) {
		buffer[i+4] = _current_led_data[i];
	}
	buffer[10] = checksum;
}

void MeroLEDDriver::addLEDCommandPacket( unsigned char* buffer, const int startIndex) {

	int nCheckSumSize	= MERO_CHECKSUM_PACKET_SIZE;
	int nBodySize		= MERO_COMMON_HEADER_PACKET_SIZE + MERO_LED_DATA_PACKET_SIZE + nCheckSumSize;
	unsigned char checksum = utility->getChecksumWithNoOffset(_current_led_data, MERO_LED_DATA_PACKET_SIZE);

	buffer[startIndex] = MERO_DEVICE_LED_ID;
	buffer[startIndex+1] = MERO_DEVICE_LED_SUB_ID_1;
	buffer[startIndex+2] = MERO_DEVICE_LED_SUB_ID_2;
	buffer[startIndex+3] = _current_led_command;
	for( int i=0 ; i<MERO_LED_DATA_PACKET_SIZE ; i++) {
		buffer[startIndex+i+4] = _current_led_data[i];
	}
	buffer[startIndex+10] = checksum;
}

int MeroLEDDriver::parseAndSetLEDDataPacket(int dataPacketSize, unsigned char* dataPacket) {

	return RETURN_SUCCESS;
}

int MeroLEDDriver::parseAndSetLEDDataPacket(int dataPacketSize, unsigned char* dataPacket, const int startIndex) {

	return RETURN_SUCCESS;
}

void MeroLEDDriver::setLEDValue(unsigned char id, unsigned char red, unsigned char green, unsigned char blue) {
//	EnterCriticalSection(&comunicate);
	pthread_mutex_lock(&__comunicate_mutex);

	_current_led_command = id;
	_current_led_data[0] = red;
	_current_led_data[1] = green;
	_current_led_data[2] = blue;
	_current_led_data[3] = red;
	_current_led_data[4] = green;
	_current_led_data[5] = blue;

	updateMeroLED();

//	LeaveCriticalSection(&comunicate);
	pthread_mutex_unlock(&__comunicate_mutex);
}

bool MeroLEDDriver::isLEDPacket(unsigned char* buffer, const int startIndex) {
	return false;
}

void MeroLEDDriver::updateMeroLED()
{
	int sendPacketSize				= 11;
	unsigned char* sendPacket		= new unsigned char[sendPacketSize];

	memset(sendPacket, 0x00, sendPacketSize);

	setLEDCommandPacket( sendPacket);
	connector->writeBytes( sendPacket, sendPacketSize );

	delete[] sendPacket;
}


