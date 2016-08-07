/*
 * MeroLEDTouchConnector.h
 *
 *  Created on: 2014. 5. 16.
 *      Author: msyoo
 */

#ifndef MEROLEDTOUCHCONNECTOR_H_
#define MEROLEDTOUCHCONNECTOR_H_


#include <reactive/mero/driver/RS232.h>
namespace reactive {
namespace mero {
namespace driver {

class MeroLEDTouchConnector {
private:
	static const int BAUD_RATE_FACE	= 115200;
	static string COMPORT	;
	RS232 serial;

public:
	MeroLEDTouchConnector();
	virtual ~MeroLEDTouchConnector();

	static MeroLEDTouchConnector* getInstance();

	int writeBytes( unsigned char * buffer, int length );
	int readBytes( unsigned char * buffer, int length );

};

} /* namespace driver */
} /* namespace mero */
} /* namespace reactive */
#endif /* MEROLEDTOUCHCONNECTOR_H_ */
