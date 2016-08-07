#ifndef __ROSCIR_COMMON_WHEEL_H__
#define __ROSCIR_COMMON_WHEEL_H__

#include <roscir/device/CirApi.h>
#include <geometry_msgs/Twist.h>

class CIRAPI CWheel
{
protected :
	// (-800~800 mm/sec)
	


public :
	virtual ~CWheel() {}

	// Command
	

	// BLDC Servo On

	/** \brief
		establishing connection 
	\remarks
		try to connect device-server
	\return
		1:success  0:fail
	\author
		cspark
	*/
	virtual int on()=0;


	/** \brief
		destroy connection 
	\remarks
		try to disconnect device-server
	\return
		1:success  0:fail
	\author
		cspark
	*/
	virtual int off()=0;


	/** \brief
		stop
	\remarks
		stop all motor
	\return
		1:success  0:fail
	\author
		cspark
	*/
	virtual int stop()=0;


	/** \brief
		moveByTRVelocity
	\remarks
		move by translationalVelocity and rotationalVelocity
	\return
		1:success  0:fail
	\author
		cspark
	*/
	virtual int moveByTRVelocity( double translationalVelocity, double rotationalVelocity )=0;


	/** \brief
		moveByWheelVelocity
	\remarks
		move by leftWheelVelocity and rightWheelVelocity
	\return
		1:success  0:fail
	\author
		cspark
	*/
	virtual int moveByWheelVelocity( double leftWheelVelocity, double rightWheelVelocity )=0;


	/** \brief
		moveByTRVelocity
	\remarks
		move by deltaX and velocity
	\return
		1:success  0:fail
	\author
		cspark
	*/
	virtual int moveToDeltaX( int deltaX, double velocity )=0;
	
	/** \brief
		moveToDeltaTheta
	\remarks
		move by deltaTheta, radius and velocity
	\return
		1:success  0:fail
	\author
		cspark
	*/
	virtual int moveToDeltaTheta( int deltaTheta, int radius, double velocity )=0;
	
	/** \brief
		moveToDeltaXYTheta
	\remarks
		move by deltaX,deltaY,deltaTheta and velocity
	\return
		1:success  0:fail
	\author
		cspark
	*/
	virtual int moveToDeltaXYTheta( int deltaX, int deltaY, int deltaTheta, double velocity )=0;
	virtual int waitmoveToDeltaFinished()=0;
	
	/** \brief
		moveByVelocityXYT
	\remarks
		move by velX,velY and velTheta
	\return
		1:success  0:fail
	\author
		cspark
	*/
	virtual int moveByVelocityXYT( double velX, double velY, double velTheta)=0;

	virtual int moveByWheelVelocity( double wheel1Rpm, double wheel2Rpm, double wheel3Rpm)=0;
	virtual int reset()=0;

	virtual int moveByTwistMsg(const geometry_msgs::Twist& twistMsg) = 0;
	virtual int emergencyStop() = 0;
	virtual int emergencyRelease() = 0;
	virtual int emergencyMoveByVelocityXYT( double velX, double velY, double velTheta)=0;
	virtual int selfDiagnosis(short errorCode[17])=0;

};

#endif /* __ROSCIR_COMMON_WHEEL_H__ */
