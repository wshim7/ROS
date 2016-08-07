#include "EWheelEncoderCore.h"

using namespace reactive::erobot::core;

EWheelEncoderCore::EWheelEncoderCore() {
	memset(_this_wheel_encoder_position, 0x00, sizeof(int) * EROBOT_WHEELENCODER_DATACOUNT);
	memset(_this_wheel_encoder_encoder, 0x00, sizeof(long) * EROBOT_WHEELENCODER_DATACOUNT);
}

EWheelEncoderCore::~EWheelEncoderCore() {

}

void EWheelEncoderCore::getWheelEncoderCommandPacket(unsigned char command, unsigned char *buffer) {
	
	int nCheckSumSize	= EROBOT_CHECKSUM_PACKET_SIZE; 
	int nBodySize		= EROBOT_COMMON_HEADER_PACKET_SIZE + nCheckSumSize;

	memset(buffer, 0x00, nBodySize);

	unsigned char checkSUM = command;

	buffer[0] = EROBOT_DEVICE_WHEELENCODER_ID;
	buffer[1] = EROBOT_DEVICE_WHEELENCODER_SUB_ID_1;
	buffer[2] = EROBOT_DEVICE_WHEELENCODER_SUB_ID_2;
	buffer[3] = command;
	buffer[4] = checkSUM;
}

void EWheelEncoderCore::addWheelEncoderCommandPacket(unsigned char command, unsigned char *buffer, const int startIndex) {

	unsigned char checkSUM = command;

	buffer[startIndex]		= EROBOT_DEVICE_WHEELENCODER_ID;
	buffer[startIndex+1]	= EROBOT_DEVICE_WHEELENCODER_SUB_ID_1;
	buffer[startIndex+2]	= EROBOT_DEVICE_WHEELENCODER_SUB_ID_2;
	buffer[startIndex+3]	= command;
	buffer[startIndex+4]	= checkSUM;
}


int EWheelEncoderCore::parseAndSetWheelEncoderDataPacket(int dataPacketSize, unsigned char* dataPacket) {
	
	unsigned char checksum = ERobotFunctionFactory::getInstance()->getChecksum(dataPacket, dataPacketSize-1);
	
	if( (dataPacket[0] != 0x01)
		|| (dataPacket[1] != 0xF1)
		|| (dataPacket[2] != 0xF1)
		|| (dataPacket[3] != 0xF4) ) {
			//cout << "[EWheelEncoderCore] res packet header is different! " << endl;
			//cout << "\t required packet 01 F1 F1 F3 " << endl;
			//printf("\t received packet %02x %02x %02x %02x \n" ,dataPacket[0],dataPacket[1],dataPacket[2],dataPacket[3] );
			return RETURN_FAILED;
	}
/*
	if (checksum != dataPacket[dataPacketSize-1]) {
		cout << "[EWheelEncoderCore] checksum check fail... " << endl;
		return RETURN_FAILED;
	}
*/
	int nBuffHeaderOff = 4;
	int nByteLen  = 0;
	int nByteSize = 3;
	_this_wheel_encoder_encoder[0] = ERobotFunctionFactory::getInstance()->byte2Int(dataPacket+nBuffHeaderOff+nByteLen,nByteSize);
	nByteLen += nByteSize;
	_this_wheel_encoder_encoder[1] = ERobotFunctionFactory::getInstance()->byte2Int(dataPacket+nBuffHeaderOff+nByteLen,nByteSize);
	nByteLen += nByteSize;
	_this_wheel_encoder_encoder[2] = ERobotFunctionFactory::getInstance()->byte2Int(dataPacket+nBuffHeaderOff+nByteLen,nByteSize);
	nByteLen += nByteSize;
	_this_wheel_encoder_position[0] = ERobotFunctionFactory::getInstance()->byte2Int(dataPacket+nBuffHeaderOff+nByteLen,nByteSize);
	nByteLen += nByteSize;
	_this_wheel_encoder_position[1] = ERobotFunctionFactory::getInstance()->byte2Int(dataPacket+nBuffHeaderOff+nByteLen,nByteSize);
	nByteLen += nByteSize;
	_this_wheel_encoder_position[2] = ERobotFunctionFactory::getInstance()->byte2Int(dataPacket+nBuffHeaderOff+nByteLen,nByteSize);
	return RETURN_SUCCESS;
}

int EWheelEncoderCore::parseAndSetWheelEncoderDataPacket(int dataPacketSize, unsigned char* dataPacket, const int startIndex) {
	unsigned char checksum = ERobotFunctionFactory::getInstance()->getChecksumWithStartIndex(dataPacket, dataPacketSize-1,startIndex);

	/*
	printf("==================\n");
	printf(" %02x \n", checksum);
	printf(" %02x \n", dataPacket[startIndex+dataPacketSize-1]);
	if (checksum != dataPacket[startIndex+dataPacketSize-1]) {
		printf("1111111111111");
	} else {
		printf("222222222222");
	}
	printf("==================\n");
	*/
/*
	if (checksum != dataPacket[startIndex+dataPacketSize-1]) {
		cout << "[EWheelEncoderCore] checksum check fail... " << endl;
		return RETURN_FAILED;
	}
	
*/
	int nBuffHeaderOff = 4 + startIndex;
	int nByteLen  = 0;
	int nByteSize = 3;
	_this_wheel_encoder_encoder[0] = ERobotFunctionFactory::getInstance()->byte2Int(dataPacket+nBuffHeaderOff+nByteLen,nByteSize);
	nByteLen += nByteSize;
	_this_wheel_encoder_encoder[1] = ERobotFunctionFactory::getInstance()->byte2Int(dataPacket+nBuffHeaderOff+nByteLen,nByteSize);
	nByteLen += nByteSize;
	_this_wheel_encoder_encoder[2] = ERobotFunctionFactory::getInstance()->byte2Int(dataPacket+nBuffHeaderOff+nByteLen,nByteSize);
	nByteLen += nByteSize;
	_this_wheel_encoder_position[0] = ERobotFunctionFactory::getInstance()->byte2Int(dataPacket+nBuffHeaderOff+nByteLen,nByteSize);
	nByteLen += nByteSize;
	_this_wheel_encoder_position[1] = ERobotFunctionFactory::getInstance()->byte2Int(dataPacket+nBuffHeaderOff+nByteLen,nByteSize);
	nByteLen += nByteSize;
	_this_wheel_encoder_position[2] = ERobotFunctionFactory::getInstance()->byte2Int(dataPacket+nBuffHeaderOff+nByteLen,nByteSize);

	return RETURN_SUCCESS;
}


void EWheelEncoderCore::getWheelEncoderValue(long* data, int* x, int* y, int* t) {
	*data = _this_wheel_encoder_encoder[0];
	*(data+1) = _this_wheel_encoder_encoder[1];
	*(data+2) = _this_wheel_encoder_encoder[2];
	*x = _this_wheel_encoder_position[0];
	*y = _this_wheel_encoder_position[1];
	*t = _this_wheel_encoder_position[2];
}

bool EWheelEncoderCore::isWheelEncoderPacket(unsigned char* buffer, const int startIndex) {
	if( (buffer[startIndex] != 0x01)
		|| (buffer[startIndex+1] != 0xF1)
		|| (buffer[startIndex+2] != 0xF1)
		|| (buffer[startIndex+3] != 0xF4) ) {
			return false;
	}
	return true;
}
