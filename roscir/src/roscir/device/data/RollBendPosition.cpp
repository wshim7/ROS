#include "RollBendPosition.h"


CRollBendPosition::CRollBendPosition()
{
	this->degreeRoll = 0.0;
	this->degreeBend = 0.0;
}

CRollBendPosition::~CRollBendPosition()
{
}
/**********************************************************************/
/*                                                                    */
/*  get/set Methods                                                   */
/*                                                                    */
/**********************************************************************/
double CRollBendPosition::getDegreeRoll()   { return this->degreeRoll; }
double CRollBendPosition::getDegreeBend()      { return this->degreeBend; }
int CRollBendPosition::getEncoderRoll()          { return this->encoderRoll; }
int CRollBendPosition::getEncoderBend()         { return this->encoderBend; }

void CRollBendPosition::setDegreeRoll( double degreeRoll )     { this->degreeRoll = degreeRoll; }
void CRollBendPosition::setDegreeBend( double degreeBend )           { this->degreeBend = degreeBend; }
void CRollBendPosition::setEncoderRoll( int encoderRoll )                { this->encoderRoll = encoderRoll; }
void CRollBendPosition::setEncoderBend( int encoderBend )              { this->encoderBend = encoderBend; }



/**********************************************************************/
/*                                                                    */
/*  Method Name     : operator<<                                      */
/*                                                                    */
/*  Description     : operator overloading                            */
/*                                                                    */
/*  Parameters      : ostream& - ostream                              */
/*                    const CRollBendPosition& - CRollBendPosition      */
/*                                                                    */
/*  Return Value    : ostream& - ostream                              */
/*                                                                    */
/**********************************************************************/
ostream& operator<<( ostream& os, const CRollBendPosition& position )
{
	os << " CRollBendPosition ( degreeRoll, degreeBend, encL, encR ) = ( "
		<< position.degreeRoll << ", "
		<< position.degreeBend << ", "
		<< position.encoderRoll << ", "
		<< position.encoderBend << " )" << endl;

	return os;
}