#ifndef __ROSCIR_COMMON_PANTILT_H__
#define __ROSCIR_COMMON_PANTILT_H__

#include <roscir/device/data/PanTiltPosition.h>

#ifndef DEFINE_SCHEMA_CPanTilt
#define DEFINE_SCHEMA_CPanTilt
struct PANTILT_DATA_TYPE
{
	double degreeLeftRight;
	double degreeUpDown;
	int encoderLeft;
	int encoderRight;
};
#endif /* DEFINE_SCHEMA_CPanTilt */ 


class CIRAPI CPanTilt {
public:
	virtual ~CPanTilt() {}

public:

	/** \brief
		establishing connection 
	\remarks
		try to connect device-server
	\return
		1:success  0:fail
	\author
		cspark
	*/
	virtual int on() = 0;


	/** \brief
		destroy connection 
	\remarks
		try to disconnect device-server
	\return
		1:success  0:fail
	\author
		cspark
	*/
	virtual int off() = 0;


	/** \brief
		stop
	\remarks
		stop all motor
	\return
		1:success  0:fail
	\author
		cspark
	*/
	virtual int stop() = 0;


	/** \brief
		move to home
	\remarks
		move to home position with speed
	\return
		1:success  0:fail
	\author
		cspark
	*/
	virtual int moveToHome( int speed ) = 0;


	/** \brief
		move to AbsolutePosition
	\remarks
		move to position with AbsolutePosition
	\return
		1:success  0:fail
	\author
		cspark
	*/
	virtual int moveToAbsolutePosition( double degreeLeftRight, double degreeUpDown, int speed ) = 0;

	virtual int moveToAbsolutePositionWithSpeed( double degreeLeftRight, double degreeUpDown, int speedLeftRight, int speedUpDown) = 0;


	/** \brief
		move to RelativePosition
	\remarks
		move to position with RelativePosition
	\return
		1:success  0:fail
	\author
		cspark
	*/
	virtual int moveToRelativePosition( double degreeLeftRight, double degreeUpDown, int speed ) = 0;
	
	
	/** \brief
		move2MotorSync
	\remarks
		move to position with motorID and speed.
	\return
		1:success  0:fail
	\author
		cspark
	*/
	virtual int move2MotorSync( int motorID1, int motorSpeed1, int motorPosition1, int motorID2, int motorSpeed2, int motorPosition2 )=0;


	/** \brief
		moveMotor
	\remarks
		move motor with id and speed
	\return
		1:success  0:fail
	\author
		cspark
	*/
	virtual int moveMotor( int motorID, int motorSpeed, int motorPosition )=0;
	
	
	/** \brief
		read pantilt data
	\remarks
		after funtion call, it return pantilt data
	\return
		return CPanTiltPosition
	\author
		cspark
	*/
	virtual void getPosition(CPanTiltPosition& position)=0;

	virtual int setCompliance(int option)=0;
		
	virtual int moveToABSAll(int panAngle, int tiltAngle, int xtionAngle, int panSpeed, int tiltSpeed, int xtionSpeed)=0;
	virtual int moveXtionTilt(int xtionAngle, int xtionSpeed)=0;
	virtual int getXtionTiltAngle()=0;
	virtual void emergencyStop() = 0;
	virtual void emergencyRelease() = 0;
	virtual void detectingError(short errorCode[3])=0;

};

#endif /* __ROSCIR_COMMON_PANTILT_H__ */
