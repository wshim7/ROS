#include "LEDServer.h"


CLightEmittingDiodeMero::CLightEmittingDiodeMero() {
	MLC = MeroLEDDriver::getInstance();
}

CLightEmittingDiodeMero::~CLightEmittingDiodeMero() {
}

int CLightEmittingDiodeMero::on( int id, int color ) {
	unsigned char red = color << 16;
	unsigned char green = color << 8;
	unsigned char blue = color << 0;
	unsigned char command = id;
	MLC->setLEDValue(command, red, green, blue);
	return 1;
}

int CLightEmittingDiodeMero::on(int id, unsigned char bright, unsigned char red, unsigned char green, unsigned char blue)
{
	MLC->setLEDValue(id, red, green, blue);
	return 1;
}


