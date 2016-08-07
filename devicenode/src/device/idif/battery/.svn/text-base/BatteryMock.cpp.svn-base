#include "BatteryServer.h"
#include <iostream>

using namespace std;

CBatteryMock::CBatteryMock(void)
{
	cout << "CBatteryMock created..." << endl;
	cout << "It send data only 1000" << endl;
}

CBatteryMock::~CBatteryMock(void)
{
}

CBatteryData CBatteryMock::readData( int index ) {
	unsigned int data[CBatteryData::NUMBER_OF_DATA];
	data[0] = 100;
	data[1] = 100;

	CBatteryData battData(0, 0, data);
	return battData;
}

bool CBatteryMock::isDocked(const int& id) {
	return false;
}

bool CBatteryMock::doCharge(const int& id) {
	return false;
}
