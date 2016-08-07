#ifndef __RS232__H__
#define __RS232__H__

//#include <Windows.h>
#include <string>
#include "Serial.h"
#include <time.h>
#include <unistd.h>

using namespace std;

class FRI_RS232 : public Serial
{
public:
	FRI_RS232(void);
	~FRI_RS232(void);

	void enumerateDevices();
	void close();
	bool setup();	// use default port, baud (0,9600)
	bool setup(int deviceNumber, int baudrate);
	bool setup(string portName, int baudrate);
	int writeBytes(unsigned char * buffer, int length);
	int writeBytesPololu(unsigned char * buffer, int length);
	int writeBytesSleep(unsigned char * buffer, int length, int delay);

	int readBytes(unsigned char * buffer, int length);

	unsigned long ofGetSystemTime();
	void ofResetElapsedTimeCounter();
	int ofGetElapsedTimeMillis();
	void flush(bool flushIn = true, bool flushOut = true);

private:
	void enumerateWin32Ports();
	char ** portNamesShort;//[MAX_SERIAL_PORTS];
	char ** portNamesFriendly; ///[MAX_SERIAL_PORTS];
	int	nPorts;
	bool bPortsEnumerated;
	bool bInited;
//	HANDLE hComm;		// the handle to the serial port pc
//	COMMTIMEOUTS oldTimeout;	// we alter this, so keep a record
	unsigned long startTime;

	bool lock(bool blocking);
	bool unlock(bool blocking);

//	CRITICAL_SECTION  critSec;  	//same as a mutex
//	CRITICAL_SECTION  critSecNeck;  	//same as a mutex
	string m_portname;
	int m_baudrate;
};

#endif


