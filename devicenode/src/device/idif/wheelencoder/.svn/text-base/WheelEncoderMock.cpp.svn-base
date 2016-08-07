#include "WheelEncoderServer.h"

CWheelEncoderMock::CWheelEncoderMock() {
	cout << "CWheelEncoderMock created..." << endl;
	cout << "It send data encoder 100000, angle 0, x 100, y 100, theta 0" << endl;
}

CWheelEncoderMock::~CWheelEncoderMock() {
}

CWheelEncoderData CWheelEncoderMock::readData(int index) {
	long a[3] = {100000 ,100000, 0};
	CWheelEncoderData encoderData(a, 100, 100, 0, 3);
	return encoderData;
}
