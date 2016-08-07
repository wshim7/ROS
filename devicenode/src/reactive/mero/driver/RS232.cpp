#include "RS232.h"

RS232::RS232(void)
{
//	nPorts 				= 0;
	_bInited = false;
	_fd = -1;
}

RS232::~RS232(void)
{
//	close();
//	nPorts 				= 0;
//	bInited = false;
	if (_bInited){
		tcsetattr(_fd,TCSANOW,&oldoptions);
		::close(_fd);
		_bInited = false;
	}
}


void RS232::close()
{
//	if (bInited){
//		SetCommTimeouts(hComm,&oldTimeout);
//		CloseHandle(hComm);
//		hComm 		= INVALID_HANDLE_VALUE;
//		bInited 	= false;
//	}
}

bool RS232::setup()
{
	return setup(0,9600);		// the first one, at 9600 is a good choice...
}

bool RS232::setup( string portName, int baudrate )
{
//	m_portname = portName;
//	m_baudrate = baudrate;
//
//	bInited = false;
//
//	hComm=CreateFileA(portName.c_str(),GENERIC_READ|GENERIC_WRITE,0,0,
//		OPEN_EXISTING,0,0);
//
//	if(hComm==INVALID_HANDLE_VALUE){
//		printf("ofSerial: unable to open port\n");
//		return false;
//	}
//	// now try the settings:
//	COMMCONFIG cfg;
//	DWORD cfgSize;
//	char  buf[80];
//
//	cfgSize=sizeof(cfg);
//	GetCommConfig(hComm,&cfg,&cfgSize);
//	int bps = baudrate;
//	sprintf_s(buf,"baud=%d parity=N data=8 stop=1",bps);
//
//	// msvc doesn't like BuildCommDCB,
//	//so we need to use this version: BuildCommDCBA
//	if(!BuildCommDCBA(buf,&cfg.dcb)){
//		printf("Serial: unable to build comm dcb; (%s)\n",buf);
//	}
//
//	// Set baudrate and bits etc.
//	// Note that BuildCommDCB() clears XON/XOFF and hardware control by default
//
//	if(!SetCommState(hComm,&cfg.dcb)){
//		printf("Serial: Can't set comm state\n");
//	}
//
//	// Set communication timeouts (NT)
//	COMMTIMEOUTS tOut;
//	GetCommTimeouts(hComm,&oldTimeout);
//	tOut = oldTimeout;
//	// Make timeout so that:
//	// - return immediately with buffered characters
//	tOut.ReadIntervalTimeout=MAXDWORD;
//	tOut.ReadTotalTimeoutMultiplier=200;
//	tOut.ReadTotalTimeoutConstant=0;
//	SetCommTimeouts(hComm,&tOut);
//
//	bInited = true;
//	return true;
	_bInited = false;

	//lets account for the name being passed in instead of the device path
	if( portName.size() > 5 && portName.substr(0, 5) != "/dev/" ){
		portName = "/dev/" + portName;
	}

	//ofLog(OF_LOG_NOTICE,"ofSerialInit: opening port %s @ %d bps", portName.c_str(), baud);
	printf("ofSerialInit: opening port %s @ %d bps\n", portName.c_str(), baudrate);
	//fd = open(portName.c_str(), O_RDWR | O_NOCTTY | O_NONBLOCK );
	//fd = open(portName.c_str(), O_RDWR | O_NOCTTY | O_NDELAY);
	_fd = open(portName.c_str(), O_RDWR | O_NOCTTY );
	if(_fd == -1){
		//ofLog(OF_LOG_ERROR,"ofSerial: unable to open port %s", portName.c_str());
		printf("ofSerial: unable to open port %s\n", portName.c_str());
		return _bInited;
	}

	struct termios options;
	tcgetattr(_fd,&oldoptions);
	options = oldoptions;
	switch(baudrate){
	   case 300:
		   cfsetispeed(&options,B300);
		   cfsetospeed(&options,B300);
		   break;
	   case 1200:
		   cfsetispeed(&options,B1200);
		   cfsetospeed(&options,B1200);
		   break;
	   case 2400:
		   cfsetispeed(&options,B2400);
		   cfsetospeed(&options,B2400);
		   break;
	   case 4800:
		   cfsetispeed(&options,B4800);
		   cfsetospeed(&options,B4800);
		   break;
	   case 9600:
		   cfsetispeed(&options,B9600);
		   cfsetospeed(&options,B9600);
		   break;
	   case 19200:
		   cfsetispeed(&options,B19200);
		   cfsetospeed(&options,B19200);
		   break;
	   case 38400:
		   cfsetispeed(&options,B38400);
		   cfsetospeed(&options,B38400);
		   break;
	   case 57600:
		   cfsetispeed(&options,B57600);
		   cfsetospeed(&options,B57600);
		   break;
	   case 115200:
		   cfsetispeed(&options,B115200);
		   cfsetospeed(&options,B115200);
		   break;
	   case 230400:
		   cfsetispeed(&options,B230400);
		   cfsetospeed(&options,B230400);
		   break;

	   default:
		   cfsetispeed(&options,B9600);
		   cfsetospeed(&options,B9600);
		   //ofLog(OF_LOG_ERROR,"ofSerialInit: cannot set %i baud setting baud to 9600", baud);
		   break;
	}

	options.c_cflag |= (CLOCAL | CREAD);
	options.c_cflag &= ~PARENB;
	options.c_cflag &= ~CSTOPB;
	options.c_cflag &= ~CSIZE;
	options.c_cflag |= CS8;
	//ijpark
	options.c_oflag=0;
	options.c_lflag=IGNPAR;
	options.c_cc[VTIME]     = 0;
	options.c_cc[VMIN]     = 4;
//		tcflush(fd,TCIFLUSH);
	tcsetattr(_fd,TCSANOW,&options);

	_bInited = true;
	//ofLog(OF_LOG_NOTICE,"success in opening serial connection");
	printf("success in opening serial connection\n");

	return _bInited;
}

int RS232::writeBytes( unsigned char * buffer, int length )
{
//	if (!bInited){
//		printf("Serial: serial not inited in writeBytes\n");
//		return SERIAL_ERROR;
//	}
//
//	DWORD written;
//	if(!WriteFile(hComm, buffer, length, &written,0)){
//		this->close();
//		Sleep(5);
//		this->setup(m_portname, m_baudrate);
//		Sleep(5);
//		return SERIAL_ERROR;
//	}
//	return (int)written;

	if (!_bInited){
		printf("ofSerial: serial not inited\n");
		return -1;
		//return OF_SERIAL_ERROR;
	}

	int numWritten = write(_fd, buffer, length);
	if(numWritten <= 0){
		if ( errno == EAGAIN )
			return 0;
		printf("ofSerial: Can't write to com port, errno %i (%s)", errno, strerror(errno));
		return -1;
	}
	//printf("ofSerial: numWritten %i\n", numWritten);
	return numWritten;
}

int RS232::readBytes( unsigned char * buffer, int length )
{
//	if (!bInited){
//		printf("Serial: serial not inited in readBytes");
//		return SERIAL_ERROR;
//	}
//
//	DWORD nRead = 0;
//	if (!ReadFile(hComm,buffer,length,&nRead,0)){
//		printf("Serial: trouble reading from port in readBytes");
//		return SERIAL_ERROR;
//	}
//	return (int)nRead;
	if (!_bInited){
		printf("ofSerial: serial not inited\n");
		return -1;
	}

	int nRead = read(_fd, buffer, length);
	if(nRead < 0){
		if ( errno == EAGAIN )
			return -1;
		printf("ofSerial: trouble reading from port, errno %i (%s)\n", errno, strerror(errno));
		return -1;
	}
	return nRead;
}

void RS232::flush( bool flushIn /*= true*/, bool flushOut /*= true*/ )
{
//	if (!bInited){
//		printf("Serial: serial not inited in flush");
//		return;
//	}
//
//	int flushType = 0;
//
//	if( flushIn && flushOut) flushType = PURGE_TXCLEAR | PURGE_RXCLEAR;
//	else if(flushIn) flushType = PURGE_RXCLEAR;
//	else if(flushOut) flushType = PURGE_TXCLEAR;
//	else return;
//
//	PurgeComm(hComm, flushType);
	if (!_bInited){
		printf("ofSerial: serial not inited\n");
		return;
	}

	int flushType = 0;

	tcflush(_fd, TCIOFLUSH);
}
