#include "UltrasonicServer.h"

CUltrasonicMock::CUltrasonicMock()
{
	cout << "CUltrasonicMock created..." << endl;
	cout << "It send data only 300" << endl;
}


CUltrasonicMock::~CUltrasonicMock()
{

}

CUltrasonicData CUltrasonicMock::readData(int index)
{
	
	unsigned short result[CUltrasonicData::NUMBER_OF_DATA];
	
	for(int i=0; i<CUltrasonicData::NUMBER_OF_DATA; i++) {
		result[i] = 300;
	}
	CUltrasonicData ultrasonicData(0, 0, result);
	return ultrasonicData;
}


void CUltrasonicMock::close() {

	
}