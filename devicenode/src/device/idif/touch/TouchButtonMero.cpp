#include "TouchButtonServer.h"


CTouchButtonMero::CTouchButtonMero()
{
	MTD = MeroTouchDriver::getInstance();
}

CTouchButtonMero::~CTouchButtonMero() {

}

CTouchButtonData CTouchButtonMero::readData( int index ) {
	unsigned short udata[2];
	MTD->getTouchButtonValue(udata, 2);
	CTouchButtonData data(udata, 2);
	return data;
}

CHeadTouchButtonData CTouchButtonMero::readHeadData( int index ) {
	return CHeadTouchButtonData();
}

int CTouchButtonMero::detectingError(int touchID) {
	cout << "CTouchButtonMero::detectingError id : " << touchID << endl;
	return MTD->detectingError(touchID);
}
