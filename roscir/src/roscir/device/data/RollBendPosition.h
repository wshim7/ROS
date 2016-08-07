#pragma once

#include <iostream>
#include <ostream>
#include <roscir/device/CirApi.h>

using namespace std;

class CIRAPI CRollBendPosition
{
private :
	double degreeRoll;
	double degreeBend;
	int encoderRoll;
	int encoderBend;

public :
	CRollBendPosition();
	~CRollBendPosition();
	friend ostream& operator<<( ostream& os, const CRollBendPosition& position );

	double getDegreeRoll();
	double getDegreeBend();
	int getEncoderRoll();
	int getEncoderBend();

	void setDegreeRoll( double degreeRoll );
	void setDegreeBend( double degreeBend );
	void setEncoderRoll( int encoderRoll );
	void setEncoderBend( int encoderBend );
};
