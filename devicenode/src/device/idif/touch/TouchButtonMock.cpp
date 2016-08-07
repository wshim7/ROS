/*
 * TouchButtonMock.cpp
 *
 *  Created on: 2014. 1. 14.
 *      Author: msyoo
 */

#include "TouchButtonServer.h"

CTouchButtonMock::CTouchButtonMock()
{
}



CTouchButtonMock::~CTouchButtonMock()
{
}



CTouchButtonData CTouchButtonMock::readData(int index)
{
	static unsigned  int data[] = {
			0, 0, 0, 0, 0, 0,
	};
	CTouchButtonData d(0, 0, data);

	return d;
}


CHeadTouchButtonData CTouchButtonMock::readHeadData(int index)
{

	CHeadTouchButtonData d;

	return d;
}

int CTouchButtonMock::detectingError(int touchID) {
	return 999;
}
