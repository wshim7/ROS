#ifndef __ROSCIR_COMMON_ARM_H__
#define __ROSCIR_COMMON_ARM_H__

#include <roscir/device/data/ArmData.h>

class CIRAPI CArm
{
public:
	virtual ~CArm(void) {}

	/** \brief
		establishing connection 
	\remarks
		try to connect device-server
	\return
		1:success  0:fail
	\author
		cspark
	*/
	virtual int on( int armID )=0;



	/** \brief
		destroy connection 
	\remarks
		try to disconnect device-server
	\return
		1:success  0:fail
	\author
		cspark
	*/
	virtual int off( int armID )=0;


	/** \brief
		not support
	\remarks
		.
	\return
		-1
	\author
		cspark
	*/
	virtual int setPeriodic( int armID, int milisecondTime )=0;


	/** \brief
		Initialize position
	\remarks
		set arm motor to init position
	\return
		1:success  0:fail
	\author
		cspark
	*/
	virtual int moveToHome( int armID )=0;


	/** \brief
		move arm
	\remarks
		move arm with Arm id(left or right), angle and speed
	\return
		1:success  0:fail
	\author
		cspark
	*/
	virtual int moveToPositionAll( int armID, double* Angle, double Speed )=0;


	/** \brief
		move arm
	\remarks
		move arm with Arm id(left or right), angle and speed
	\return
		1:success  0:fail
	\author
		cspark
	*/
	virtual int moveToPositionWithAxisSpeed( int armID, double* Angle, double* Speed )=0;



	/** \brief
		move arm
	\remarks
		move arm with Arm id(left or right), angle and speed
	\return
		1:success  0:fail
	\author
		cspark
	*/
	virtual int moveToPositionAllWithPeriodic( int armID, double Angle, int stateType )=0;



	/** \brief
		stop arm
	\remarks
		stop arm
	\return
		1:success  0:fail
	\author
		cspark
	*/
	virtual int stop()=0;




	/** \brief
		not support
	\remarks
		return arm position data
	\return
		arm data
	\author
		cspark
	*/
	virtual CArmData waitRunOnPeriodic( float index )=0;


	//
    // for engkey
    //
    //


	/** \brief
		move arm (for engkey)
	\remarks
		move arm with angle and speed. angle array size is 6. move same speed
	\return
		void
	\author
		cspark
	*/
    virtual void moveBothArmToPositionAll(double Angle[6], int speed) = 0;


	/** \brief
		move arm (for engkey)
	\remarks
		move arm with angle and speed. angle array size is 6. move different speed
	\return
		void
	\author
		cspark
	*/
    virtual void moveBothArmToPositionWithAxisSpeed(double Angle[6], int speed[6]) = 0;

	/** \brief
		get arm position (for engkey)
	\remarks
		after funtion call, it return arm data
	\return
		void
	\author
		cspark
	*/
    virtual void getArmPosition(int armId, double angle[6]) = 0;

    virtual void setArmHomePosition() = 0;

    virtual void emergencyStop() = 0;
    virtual void emergencyRelease() = 0;
    virtual void detectingError(short errorCode[6]) = 0;

};

#endif /* __ROSCIR_COMMON_ARM_H__ */
