#include "LEDServer.h"


CLightEmittingDiodeMock::CLightEmittingDiodeMock() {
}

CLightEmittingDiodeMock::~CLightEmittingDiodeMock() {
}

int CLightEmittingDiodeMock::on( int id, int color ) {
	int nRet = 1;
	ROS_INFO("LED ID : %d, Color: %d" , id, color);
	return nRet;
}

int CLightEmittingDiodeMock::on(int id, unsigned char bright, unsigned char red, unsigned char green, unsigned char blue)
{
	int nRet = 1;
	ROS_INFO("LED ID : %d, RED: %d, GREEN: %d, BLUE: %d" , id, red, green, blue);
	return nRet;
}


