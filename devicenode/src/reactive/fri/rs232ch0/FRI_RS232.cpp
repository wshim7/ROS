
#include <stdio.h>
#include <string>
//#include <Windows.h>
//#include <winbase.h>
//#include <setupapi.h>
//#include <MMSystem.h>

#include "FRI_RS232.h"
#include "SERIAL_ERROR.h"

#define MAX_SERIAL_PORTS 256



//------------------------------------
// needed for serial bus enumeration:
//4d36e978-e325-11ce-bfc1-08002be10318}
//DEFINE_GUID (GUID_SERENUM_BUS_ENUMERATOR, 0x4D36E978, 0xE325,
//			 0x11CE, 0xBF, 0xC1, 0x08, 0x00, 0x2B, 0xE1, 0x03, 0x18);
//------------------------------------


FRI_RS232::FRI_RS232(void)
{
//	InitializeCriticalSection(&critSec);
//	InitializeCriticalSection(&critSecNeck);

	//---------------------------------------------
//	nPorts 				= 0;
//	bPortsEnumerated 	= false;
//
//	portNamesShort = new char * [MAX_SERIAL_PORTS];
//	portNamesFriendly = new char * [MAX_SERIAL_PORTS];
//	for (int i = 0; i < MAX_SERIAL_PORTS; i++){
//		portNamesShort[i] = new char[10];
//		portNamesFriendly[i] = new char[MAX_PATH];
//	}


	//---------------------------------------------

	//---------------------------------------------
//	bVerbose = false;

}

FRI_RS232::~FRI_RS232(void)
{
	close();

	//---------------------------------------------

	//---------------------------------------------
	nPorts 				= 0;
	bPortsEnumerated 	= false;

	for (int i = 0; i < MAX_SERIAL_PORTS; i++) {
		delete [] portNamesShort[i];
		delete [] portNamesFriendly[i];
	}
	delete [] portNamesShort;
	delete [] portNamesFriendly;

	//---------------------------------------------
	bInited = false;

}

void FRI_RS232::enumerateDevices()
{
	enumerateWin32Ports();
//	printf("ofSerial: listing devices (%i total)\n", nPorts);
	for (int i = 0; i < nPorts; i++){
		printf("device %i -- %s %s", i, portNamesFriendly[i], portNamesShort[i]);
	}

}

void FRI_RS232::enumerateWin32Ports()
{
	// thanks joerg for fixes...

	if (bPortsEnumerated == true) return;

//	HDEVINFO hDevInfo = NULL;
//	SP_DEVINFO_DATA DeviceInterfaceData;
//	int i = 0;
//	DWORD dataType, actualSize = 0;
//	unsigned char dataBuf[MAX_PATH + 1];
//
//	// Reset Port List
//	nPorts = 0;
//	// Search device set
//	hDevInfo = SetupDiGetClassDevs((struct _GUID *)&GUID_SERENUM_BUS_ENUMERATOR,0,0,DIGCF_PRESENT);
//	if ( hDevInfo ){
//		while (TRUE){
//			ZeroMemory(&DeviceInterfaceData, sizeof(DeviceInterfaceData));
//			DeviceInterfaceData.cbSize = sizeof(DeviceInterfaceData);
//			if (!SetupDiEnumDeviceInfo(hDevInfo, i, &DeviceInterfaceData)){
//				// SetupDiEnumDeviceInfo failed
//				break;
//			}
//
//			if (SetupDiGetDeviceRegistryProperty(hDevInfo,
//				&DeviceInterfaceData,
//				SPDRP_FRIENDLYNAME,
//				&dataType,
//				dataBuf,
//				sizeof(dataBuf),
//				&actualSize)){
//
//					sprintf(portNamesFriendly[nPorts], "%s", dataBuf);
//					portNamesShort[nPorts][0] = 0;
//
//					// turn blahblahblah(COM4) into COM4
//
//					char *   begin    = NULL;
//					char *   end    = NULL;
//					begin          = strstr((char *)dataBuf, "COM");
//
//
//					if (begin)
//					{
//						end          = strstr(begin, ")");
//						if (end)
//						{
//							*end = 0;   // get rid of the )...
//							strcpy(portNamesShort[nPorts], begin);
//						}
//						if (nPorts++ > MAX_SERIAL_PORTS)
//							break;
//					}
//			}
//			i++;
//		}
//	}
//	SetupDiDestroyDeviceInfoList(hDevInfo);

	bPortsEnumerated = false;

}

void FRI_RS232::close()
{
//	if (bInited){
//		SetCommTimeouts(hComm,&oldTimeout);
//		CloseHandle(hComm);
//		hComm 		= INVALID_HANDLE_VALUE;
//		bInited 	= false;
//	}

}

bool FRI_RS232::setup()
{
	return setup(0,9600);		// the first one, at 9600 is a good choice...
}

//************************************
// Method:    setup
// FullName:  RS232::setup
// Access:    public 
// Returns:   bool �����ϸ� true, �����ϸ� false
// Qualifier:
// Parameter: int deviceNumber
// Parameter: int baudrate
//************************************
bool FRI_RS232::setup( int deviceNumber, int baudrate )
{
	int deviceCount = 0;

	string str			= "";
	string device		= "";
	bool deviceFound	= false;

	enumerateWin32Ports();
	if (deviceNumber < nPorts){
		device = portNamesShort[deviceNumber];
		deviceFound = true;
	}

	if(deviceFound){
		return setup(device, baudrate);
	}else{
		//printf("ofSerial: could not find device %i - only %i devices found\n", deviceNumber, nPorts);
		return false;
	}

}

//************************************
// Method:    setup
// FullName:  RS232::setup
// Access:    public 
// Returns:   bool �����ϸ� true, �����ϸ� false
// Qualifier:
// Parameter: string portName
// Parameter: int baudrate
//************************************
bool FRI_RS232::setup( string portName, int baudrate )
{
//	m_portname = portName;
//	m_baudrate = baudrate;
//
//	bInited = false;
//
//	// open the serial port:
//	// "COM4", etc...
//
//	//portName = "COM7";
//	printf("FRI_RS232::setup : tryp to open serial port : %s\n", portName.c_str());
//	hComm=CreateFileA(portName.c_str(),GENERIC_READ|GENERIC_WRITE,0,0,
//		OPEN_EXISTING,0,0);
//
//	if(hComm==INVALID_HANDLE_VALUE){
//		printf("FRI_RS232::setup :  unable to open port\n");
//		return false;
//	}
//
//
//	// now try the settings:
//	COMMCONFIG cfg;
//	DWORD cfgSize;
//	char  buf[80];
//
//	cfgSize=sizeof(cfg);
//	GetCommConfig(hComm,&cfg,&cfgSize);
//	int bps = baudrate;
//	sprintf(buf,"baud=%d parity=N data=8 stop=1",bps);
//
//
//	// msvc doesn't like BuildCommDCB,
//	//so we need to use this version: BuildCommDCBA
//	if(!BuildCommDCBA(buf,&cfg.dcb)){
//		printf("ofSerial: unable to build comm dcb; (%s)\n",buf);
//	}
//
//
//	// Set baudrate and bits etc.
//	// Note that BuildCommDCB() clears XON/XOFF and hardware control by default
//
//	if(!SetCommState(hComm,&cfg.dcb)){
//		printf("ofSerial: Can't set comm state\n");
//	}
//	//ofLog(OF_LOG_NOTICE,buf,"bps=%d, xio=%d/%d",cfg.dcb.BaudRate,cfg.dcb.fOutX,cfg.dcb.fInX);
//
//	// Set communication timeouts (NT)
//	COMMTIMEOUTS tOut;
//	GetCommTimeouts(hComm,&oldTimeout);
//	tOut = oldTimeout;
//	// Make timeout so that:
//	// - return immediately with buffered characters
//	tOut.ReadIntervalTimeout=MAXDWORD;
//	tOut.ReadTotalTimeoutMultiplier=0;
//	tOut.ReadTotalTimeoutConstant=0;
//	SetCommTimeouts(hComm,&tOut);
//
//	bInited = true;
//	return true;
	//---------------------------------------------

}

//************************************
// Method:    writeBytes
// FullName:  RS232::writeBytes
// Access:    public 
// Returns:   int - ������ ��쿡�� write�� byte ��. ������ ��쿡�� ���� �ڵ� - ��.
// Qualifier:
// Parameter: unsigned char * buffer
// Parameter: int length
//************************************
int FRI_RS232::writeBytes( unsigned char * buffer, int length )
{
//	lock(true);
//
//	// pololu �� �� �ȵǴ� �� ���� sleep 5 �߰� 2012.7.2 cgkim
//	//Sleep(5);
//
//	if (!bInited){
////		printf("ofSerial: serial not inited in writeBytes\n");
//		return OF_SERIAL_ERROR;
//	}
//
//	DWORD written;
//	if(!WriteFile(hComm, buffer, length, &written,0)){
////		printf("###ofSerial: Can't write to com port in writeBytes\n");
//		//flush();
//		this->close();
//		Sleep(5);
//		this->setup(m_portname, m_baudrate);
//		Sleep(5);
//
//
//
////		printf("ofSerial: reopened\n");
//		return OF_SERIAL_ERROR;
//	}
////	printf("ofSerial: numWritten %i\n", (int)written);
//
//	unlock(true);
//	return (int)written;
	return 1;
}

int FRI_RS232::writeBytesSleep( unsigned char * buffer, int length, int delay )
{
//	lock(false);
//
//	//Sleep(delay);
//
//	if (!bInited){
////		printf("ofSerial: serial not inited in writeBytesSleep\n");
//		return OF_SERIAL_ERROR;
//	}
//
//	DWORD written;
//	if(!WriteFile(hComm, buffer, length, &written,0)){
//		printf("###ofSerial: Can't write to com port in writeBytesSleep\n");
//		flush();
//		printf("ofSerial: flush\n");
//		return OF_SERIAL_ERROR;
//	}
//	//	printf("ofSerial: numWritten %i\n", (int)written);
//
//
//	unlock(false);
//	return (int)written;

	return 1;
}



int FRI_RS232::readBytes( unsigned char * buffer, int length )
{
	//lock();
//	if (!bInited){
////		printf("ofSerial: serial not inited in readBytes");
//		return OF_SERIAL_ERROR;
//	}
//
//	//---------------------------------------------
//	DWORD nRead = 0;
//	if (!ReadFile(hComm,buffer,length,&nRead,0)){
//		printf("ofSerial: trouble reading from port in readBytes");
//		return OF_SERIAL_ERROR;
//	}
//	//unlock();
//	return (int)nRead;
	return 1;
}

unsigned long FRI_RS232::ofGetSystemTime()
{
//	return timeGetTime();
	return 1;
}

void FRI_RS232::ofResetElapsedTimeCounter()
{
	startTime = ofGetSystemTime();
}

int FRI_RS232::ofGetElapsedTimeMillis()
{
	return (int)(ofGetSystemTime() - startTime);
}

void FRI_RS232::flush( bool flushIn /*= true*/, bool flushOut /*= true*/ )
{
//	if (!bInited){
////		printf("ofSerial: serial not inited in flush");
//		return;
//	}
//
//	int flushType = 0;
//
//	//---------------------------------------------
//	if( flushIn && flushOut) flushType = PURGE_TXCLEAR | PURGE_RXCLEAR;
//	else if(flushIn) flushType = PURGE_RXCLEAR;
//	else if(flushOut) flushType = PURGE_TXCLEAR;
//	else return;
//
//	PurgeComm(hComm, flushType);
}


// true face
// false neck
bool FRI_RS232::lock( bool blocking/*=true*/ )
{
	//if ( blocking == true )
	//	EnterCriticalSection(&critSec);
	//else
	//	EnterCriticalSection(&critSecNeck);

	//ofLog::write(OF_LOG_WARNING, "ofxThread: we are in -- mutex is now locked");
	return true;

}

bool FRI_RS232::unlock(bool blocking)
{
	// 
	//if ( blocking == true )
	//	LeaveCriticalSection(&critSec);
	//else
	//	LeaveCriticalSection(&critSecNeck);

	return true;

}

int FRI_RS232::writeBytesPololu( unsigned char * buffer, int length )
{
//	lock(true);
//	Sleep(10);// ��ġ ������ ����� ����
//	if (!bInited){
////		printf("ofSerial: serial not inited in writeBytes\n");
//		return OF_SERIAL_ERROR;
//	}
//
//	DWORD written;
//	if(!WriteFile(hComm, buffer, length, &written,0)){
//		printf("###ofSerial: Can't write to com port in writeBytes\n");
//		flush();
//		printf("ofSerial: flush\n");
//		return OF_SERIAL_ERROR;
//	}
//	//	printf("ofSerial: numWritten %i\n", (int)written);
//
//	unlock(true);
//	return (int)written;
	return 1;
}
