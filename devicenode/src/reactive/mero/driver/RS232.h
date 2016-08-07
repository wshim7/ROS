
#ifndef __RS232_H_XXYYZZ__
#define __RS232_H_XXYYZZ__

//#include <Windows.h>
#include <stdio.h>
//#include <winbase.h>
#include <string>
#include <cstring>

#include <termios.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

#define SERIAL_ERROR		-1
#define SERIAL_NO_DATA 	-2

using namespace std;

class RS232
{
public:
	RS232(void);
	virtual ~RS232(void);

	void close();
	bool setup();	// use default port, baud (0,9600)
	bool setup(string portName, int baudrate);
	int writeBytes(unsigned char * buffer, int length);
	int readBytes(unsigned char * buffer, int length);
	void flush(bool flushIn = true, bool flushOut = true);

private:

	bool	_bInited;
	int		_fd;

	struct 			termios oldoptions;

//	int	nPorts;
//	bool bInited;
//	HANDLE hComm;		// the handle to the serial port pc
//	COMMTIMEOUTS oldTimeout;	// we alter this, so keep a record
	unsigned long startTime;
	string m_portname;
	int m_baudrate;
};


#endif
