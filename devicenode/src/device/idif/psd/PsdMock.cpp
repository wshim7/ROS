#include "PsdServer.h"

CPSDMock::CPSDMock() {
	cout << "CPSDMock created..." << endl;
	cout << "It send data only 100" << endl;
}

CPSDMock::~CPSDMock() {

}

int CPSDMock::readData(int returnMethod, CPSDData& data) {
	unsigned short sdata[CPSDData::__NUMBER_OF_MAX_DATA];
	for(int i=0; i<CPSDData::__NUMBER_OF_MAX_DATA; i++) {
		sdata[i] = 100;
	}

	data.setData(sdata, CPSDData::__NUMBER_OF_MAX_DATA);
	return 0;
}

