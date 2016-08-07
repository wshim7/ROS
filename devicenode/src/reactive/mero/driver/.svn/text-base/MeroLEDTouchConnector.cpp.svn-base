/*
 * MeroLEDTouchConnector.cpp
 *
 *  Created on: 2014. 5. 16.
 *      Author: msyoo
 */

#include "MeroLEDTouchConnector.h"

namespace reactive {
namespace mero {
namespace driver {

string MeroLEDTouchConnector::COMPORT = "COM5";

MeroLEDTouchConnector::MeroLEDTouchConnector() {

	serial.setup(MeroLEDTouchConnector::COMPORT, MeroLEDTouchConnector::BAUD_RATE_FACE);
	serial.flush();
}

MeroLEDTouchConnector::~MeroLEDTouchConnector() {
	serial.close();
}

MeroLEDTouchConnector* MeroLEDTouchConnector::getInstance()
{
	static MeroLEDTouchConnector thisInstance;
	return &thisInstance;
}


int MeroLEDTouchConnector::writeBytes(unsigned char *buffer, int length)
{
	return serial.writeBytes(buffer, length);
}


int MeroLEDTouchConnector::readBytes(unsigned char *buffer, int length)
{
	return serial.readBytes(buffer, length);
}

} /* namespace driver */
} /* namespace mero */
} /* namespace reactive */
