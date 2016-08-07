#pragma once
#include <string>

using namespace std;

class Serial
{
public:

	Serial(void)
	{
	}

	virtual ~Serial(void)
	{
	}

	virtual bool setup()=0;
	virtual bool setup( string portName, int baudrate )=0;;

	virtual int writeBytes(unsigned char * buffer, int length)=0;
	virtual void flush(bool flushIn = true, bool flushOut = true)=0;

};
