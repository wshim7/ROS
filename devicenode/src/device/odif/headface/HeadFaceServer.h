/*
 * HeadFaceServer.h
 *
 *  Created on: 2014. 2. 11.
 *      Author: msyoo
 */

#ifndef HEADFACESERVER_H_
#define HEADFACESERVER_H_

#include <ros/ros.h>
#include <roscir/device/common/HeadFace.h>
#include <roscir/env/Config.h>
#include <device/DeviceServerDefinition.h>
#include <reactive/mero/driver/MeroFaceDriver.h>
#include <reactive/fri/include/RT_FriHeadface.h>
#include <reactive/util/motorlimit/RobotConfig.h>
#include <reactive/fri/rs232ch0/HeadFaceRS232.h>

class CHeadFaceServerProxy : public CHeadFace
{
    private :
        CHeadFace* headFace;

        CHeadFaceServerProxy();

    public :
        virtual ~CHeadFaceServerProxy();
		static CHeadFace* getInstance();

		int on();
		int off();
        int express(string emotion, double intensity, int duration );
        int moveAbsolutePosition( int motorID, int speed, int position );
        int moveAbsolutePosition( int motorID, double degree, int speed );
		int moveLipViseme(int visemeID);
		int moveLip( string visemeTime );
		int changeAvatar(int avatarType);
};

class CHeadFaceMock : public CHeadFace
{

    public :
		CHeadFaceMock();
		virtual ~CHeadFaceMock();

		int on();
		int off();
        int express( string emotion, double intensity, int duration );
        int moveAbsolutePosition( int motorID, int speed, int position );
        int moveAbsolutePosition( int motorID, double degree, int speed );
		int moveLip( string visemeTime );
		int moveLipViseme(int visemeID);
		int changeAvatar(int avatarType);
};

class CHeadFaceMPAvatar : public CHeadFace
{

    public :
		CHeadFaceMPAvatar();
		virtual ~CHeadFaceMPAvatar();
		static CHeadFaceMPAvatar* getInstance();

		int on();
		int off();
		int express(string emotion, double intensity, int duration);
		int moveAbsolutePosition( int motorID, int speed, int position );
		int moveAbsolutePosition( int motorID, double degree, int speed );
		int moveLip( string visemeTime );
		int moveLipViseme(int visemeID);
		int changeAvatar(int avatarType);
    private :
		ros::NodeHandle n;
		ros::ServiceClient expressionClient;
		ros::ServiceClient moveFaceClient;
		ros::ServiceClient faceFactorClient;
};

class CHeadFaceMero : public CHeadFace
{

    public :
	CHeadFaceMero();
		virtual ~CHeadFaceMero();
		static CHeadFaceMero* getInstance();

		int on();
		int off();
		int express(string emotion, double intensity, int duration);
		int moveAbsolutePosition( int motorID, int speed, int position );
		int moveAbsolutePosition( int motorID, double degree, int speed );
		int moveLip( string visemeTime );
		int moveLipViseme(int visemeID);
		int changeAvatar(int avatarType);
    private:
		static double MIN_EYEBRROW_UD_DEGREE;
		static double MIN_EYEBRROW_CW_DEGREE;
		static double MIN_EYELID_R_UD_DEGREE;
		static double MIN_EYELID_L_UD_DEGREE;
		static double MIN_EYELID_R_CW_DEGREE;
		static double MIN_PUPIL_UD_DEGREE;
		static double MIN_PUPIL_LR_DEGREE;
		static double MIN_LIP_U_CW_DEGREE;
		static double MIN_LIP_L_CW_DEGREE;
		static double MIN_LIP_C_WP;
		static int MIN_FACE_SPEED;


		static double MAX_EYEBRROW_UD_DEGREE;
		static double MAX_EYEBRROW_CW_DEGREE;
		static double MAX_EYELID_R_UD_DEGREE;
		static double MAX_EYELID_L_UD_DEGREE;
		static double MAX_EYELID_R_CW_DEGREE;
		static double MAX_PUPIL_UD_DEGREE;
		static double MAX_PUPIL_LR_DEGREE;
		static double MAX_LIP_U_CW_DEGREE;
		static double MAX_LIP_L_CW_DEGREE;
		static double MAX_LIP_C_WP;
		static int MAX_FACE_SPEED;

		reactive::mero::driver::MeroFaceDriver* faceDriver;
		CRobotConfig* robotConfig;
		map<string, double> MEROLimits;
		void setLimits();

};

class CHeadFaceFRIRTAI : public CHeadFace
{
	protected :
		int mFriHeadfaceCmdfifo, mFriHeadfaceReportfifo;
		struct Fri_Headface_Cmdfifo FriHeadfaceCmdfifo;
		struct Fri_Headface_Reportfifo FriHeadfaceReportfifo;

	public:
		/* ex)
		//(0~100 mm/sec)
		*/
		static  int MIN_SPEED;
		static  int MAX_SPEED;

		static  int MIN_EYEBROW_R_ROLL_00;
		static  int MAX_EYEBROW_R_ROLL_00;
		static  int MIN_EYEBROW_L_ROLL_01;
		static  int MAX_EYEBROW_L_ROLL_01;
		static  int MIN_EYEBROW_R_UD_02;
		static  int MAX_EYEBROW_R_UD_02;
		static  int MIN_EYEBROW_L_UD_03;
		static  int MAX_EYEBROW_L_UD_03;
		static  int MIN_UPPEREYELID_R_UD_04;
		static  int MAX_UPPEREYELID_R_UD_04;
		static  int MIN_UPPEREYELID_L_UD_05;
		static  int MAX_UPPEREYELID_L_UD_05;
		static  int MIN_LOWEREYELID_R_UD_06;
		static  int MAX_LOWEREYELID_R_UD_06;
		static  int MIN_LOWEREYELID_L_UD_07;
		static  int MAX_LOWEREYELID_L_UD_07;
		static  int MIN_PUPIL_R_UD_08;
		static  int MAX_PUPIL_R_UD_08;
		static  int MIN_PUPIL_L_UD_09;
		static  int MAX_PUPIL_L_UD_09;
		static  int MIN_PUPIL_R_RL_10;
		static  int MAX_PUPIL_R_RL_10;
		static  int MIN_PUPIL_L_RL_11;
		static  int MAX_PUPIL_L_RL_11;
		static  int MIN_LIPSUPPER_R_12;
		static  int MAX_LIPSUPPER_R_12;
		static  int MIN_LIPSUPPER_L_13;
		static  int MAX_LIPSUPPER_L_13;
		static  int MIN_LIPSLOWER_R_14;
		static  int MAX_LIPSLOWER_R_14;
		static  int MIN_LIPSLOWER_L_15;
		static  int MAX_LIPSLOWER_L_15;
		static  int MIN_LIPSCENTER_16;
		static  int MAX_LIPSCENTER_16;

    private :
		int m_typeOFInterface;
		HeadFaceRS232* headface232;

		CRobotConfig* robotConfig;
		map<string, double> FRILimits;
		void setLimits();


    public :
		CHeadFaceFRIRTAI();
        ~CHeadFaceFRIRTAI();
        static CHeadFaceFRIRTAI* getInstance();

		int on();
		int off();
		int express(string emotion, double intensity, int duration);
		int moveAbsolutePosition( int motorID, int speed, int position );
		int moveAbsolutePosition( int motorID, double degree, int speed );
		int moveLip( string visemeTime );
		int moveLipViseme(int visemeID);
		int changeAvatar(int avatarType);
};

#endif /* HEADFACESERVER_H_ */



