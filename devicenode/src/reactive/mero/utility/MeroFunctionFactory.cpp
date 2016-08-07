#include "MeroFunctionFactory.h"

using namespace reactive::mero::driver;

MeroFunctionFactory::MeroFunctionFactory() {

}

MeroFunctionFactory::~MeroFunctionFactory() {

}

MeroFunctionFactory* MeroFunctionFactory::getInstance() {
	static MeroFunctionFactory instance;
	return &instance;
}

void MeroFunctionFactory::intTo2Bytes(int n, unsigned char * bp) {
	
	// check range.. -32767 ~ 32767
	if (n > MAX_2BYTE_INT) {
		n = MAX_2BYTE_INT;
		cout << "[MeroFunctionFactory] int value is over Maximum integer " << MAX_2BYTE_INT << ", n : " << n<< endl;
	}

	if (n >= 0) {
		*(bp+1) = n;
		*bp = n >> 8;				// 32767
		
	} else {
		// 2's complement
		n = n -1;
		*(bp+1) = n ^ 0xFF;
		*bp = (n >> 8) ^ 0xFF;		// ������ �� �ֻ��� 1
		*bp = *bp | 10000000;
	}
}

void MeroFunctionFactory::intToByte(int n, unsigned char * bp) {
	if (n > 255) {
		n = 255;
		cout << "int value is over Maximum integer " << 255 << ", n : " << n<< endl;
	}

	if (n >= 0) {

		*bp = n;
	} else {
		*bp = 0;
	}

}

int MeroFunctionFactory::byte2Int(unsigned char *bp, int len) {
	int result = 0;
	int tmp = 0;
	//cout << "... in byte2Int : " ;
	//printBuffer2Binary(bp, len);

	bool bNegative = false;

	if ( (bp[0] & 0x80) == 0x80) {
		bNegative = true;
		tmp = bp[0] & 0x7f;
		result = result +  (tmp << (8 * (len-1)) );
	} else {
		tmp = bp[0] & 0xff;
		result = result +  (tmp << (8 * (len-1)) );
	}
	for (int i = 1 ; i < len; i++) {
		//cout << " i : " << i << ", bp : " << bp[i] << endl;
		tmp = bp[i] & 0xff;
		result = result +  (tmp << (8 * (len-i-1)) );
	}
	//cout << "byte2int : " << n << endl;
	if ( bNegative ) {
		result *= -1;
	}

	if (  (len == 2 && result > MAX_2BYTE_INT)  || (len == 2 && result > MAX_3BYTE_INT) ) {
		//cout << "here.. n : " << n ;
		//n -= 32768;
		//cout << ", " << n << endl;
		result = 0;
	}
	return result;
}

void MeroFunctionFactory::byte2Short(unsigned char *bp, int len, short *data) {
	int n = 0, tmp = 0;
	//cout << "... in byte2Int : " ;
	//printBuffer2Binary(bp, len);

	bool bNegative = false;

	if ( (bp[0] & 0x80) == 0x80) {
		bNegative = true;
		tmp = bp[0] & 0x7f;
		n = n +  (tmp << (8 * (len-1)) );
	} else {
		tmp = bp[0] & 0xff;
		n = n +  (tmp << (8 * (len-1)) );
	}
	for (int i = 1 ; i < len; i++) {
		//cout << " i : " << i << ", bp : " << bp[i] << endl;
		tmp = bp[i] & 0xff;
		n = n +  (tmp << (8 * (len-i-1)) );
	}
	//cout << "byte2int : " << n << endl;
	if ( bNegative ) {
		n *= -1;
	}

	*data = n;
}


unsigned char MeroFunctionFactory::getChecksum(unsigned char* packet, int packet_len) {
	
	int headerOffSet = 4;
	unsigned char xorr = 0;			//unsigned char xor = packet[0];

	for ( int i = headerOffSet ; i < packet_len ; i ++ ) {
		xorr = xorr ^ packet[i];
	}
	return xorr;
}

unsigned char MeroFunctionFactory::getChecksumWithNoOffset(unsigned char* packet, int packet_len) {
	
	unsigned char xorr = 0;			//unsigned char xor = packet[0];

	for ( int i = 0 ; i < packet_len ; i ++ ) {
		xorr = xorr ^ packet[i];
	}
	return xorr;
}

unsigned char MeroFunctionFactory::getChecksumWithStartIndex(unsigned char* packet, int packet_len, int startIndex) {
	
	int headerOffSet = 4;
	unsigned char xorr = 0;			//unsigned char xor = packet[0];

	for ( int i = headerOffSet+startIndex ; i < startIndex+packet_len ; i ++ ) {
		xorr = xorr ^ packet[i];
	}
	return xorr;
}


string MeroFunctionFactory::intToString(int intNumber)
{
	stringstream ssID;
	ssID << intNumber;
	return ssID.str();
}

int MeroFunctionFactory::StringToInt(string str)
{
	return atoi(str.c_str());
}

int MeroFunctionFactory::getReadPacketSize(unsigned char command) {

	/*
	 *	SIZE : header size + body size + checksum
	 */

	if( command == MERO_TYPE_TOUCHBUTTON) {
			return 4+2+1;
	}
	return 0;
}
