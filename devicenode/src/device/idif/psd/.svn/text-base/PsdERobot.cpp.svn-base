#include "PsdServer.h"

CPSDERobot::CPSDERobot() {
	core = ERobotCore::getInstance();
}

CPSDERobot::~CPSDERobot()
{	
}

int CPSDERobot::readData(int returnMethod, CPSDData& data) {
	unsigned short sdata[CPSDData::__NUMBER_OF_MAX_DATA];
	core->getPSDValue(sdata, CPSDData::__NUMBER_OF_MAX_DATA);
	data.setData(sdata, CPSDData::__NUMBER_OF_MAX_DATA);
	return RETURN_SUCCESS;
}
