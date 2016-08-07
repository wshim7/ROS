/***************************************	*******************************/
/*
/*  Class name      : CHeadFaceFRIRTAI.cpp
/*
/*  Description     : CHeadFaceFRIRTAI
/*
/**********************************************************************/
/*                        Update History
/*
/*      DATE           AUTHOR                    DESCRIPTION
/*   ----------   ----------------   ------------------------------
/*   2009/07/17    CIR Tech          Initial Release
/*
/**********************************************************************/

#include "HeadFaceServer.h"
#include <roscir/env/Config.h>

/**
 *
 * A Constructor.
 * Open FIFO files to access kernel.
 *
 * @param None.
 *
 * @return None.
 *
 */
int  CHeadFaceFRIRTAI::MIN_SPEED = 0;
int  CHeadFaceFRIRTAI::MAX_SPEED = 100;

int CHeadFaceFRIRTAI::MIN_EYEBROW_R_ROLL_00		=  90-15;
int CHeadFaceFRIRTAI::MAX_EYEBROW_R_ROLL_00		=  90+15;
int CHeadFaceFRIRTAI::MIN_EYEBROW_L_ROLL_01		=  90-15;
int CHeadFaceFRIRTAI::MAX_EYEBROW_L_ROLL_01		=  90+15;
int CHeadFaceFRIRTAI::MIN_EYEBROW_R_UD_02		=  90-10;
int CHeadFaceFRIRTAI::MAX_EYEBROW_R_UD_02		=  90+10;
int CHeadFaceFRIRTAI::MIN_EYEBROW_L_UD_03		=  90-10;
int CHeadFaceFRIRTAI::MAX_EYEBROW_L_UD_03		=  90+10;
int CHeadFaceFRIRTAI::MIN_UPPEREYELID_R_UD_04	=  90-35;
int CHeadFaceFRIRTAI::MAX_UPPEREYELID_R_UD_04	=  90+35;
int CHeadFaceFRIRTAI::MIN_UPPEREYELID_L_UD_05	=  90-35;
int CHeadFaceFRIRTAI::MAX_UPPEREYELID_L_UD_05	=  90+35;
int CHeadFaceFRIRTAI::MIN_LOWEREYELID_R_UD_06	=  90-25;
int CHeadFaceFRIRTAI::MAX_LOWEREYELID_R_UD_06	=  90+25;
int CHeadFaceFRIRTAI::MIN_LOWEREYELID_L_UD_07	=  90-25;
int CHeadFaceFRIRTAI::MAX_LOWEREYELID_L_UD_07	=  90+25;
int CHeadFaceFRIRTAI::MIN_PUPIL_R_UD_08		=  90-25;
int CHeadFaceFRIRTAI::MAX_PUPIL_R_UD_08		=  90+25;
int CHeadFaceFRIRTAI::MIN_PUPIL_L_UD_09		=  90-25;
int CHeadFaceFRIRTAI::MAX_PUPIL_L_UD_09		=  90+25;
int CHeadFaceFRIRTAI::MIN_PUPIL_R_RL_10		=  90-35;
int CHeadFaceFRIRTAI::MAX_PUPIL_R_RL_10		=  90+35;
int CHeadFaceFRIRTAI::MIN_PUPIL_L_RL_11		=  90-35;
int CHeadFaceFRIRTAI::MAX_PUPIL_L_RL_11		=  90+35;
int CHeadFaceFRIRTAI::MIN_LIPSUPPER_R_12	=  90-60;
int CHeadFaceFRIRTAI::MAX_LIPSUPPER_R_12	=  90+60;
int CHeadFaceFRIRTAI::MIN_LIPSUPPER_L_13	=  90-60;
int CHeadFaceFRIRTAI::MAX_LIPSUPPER_L_13	=  90+60;
int CHeadFaceFRIRTAI::MIN_LIPSLOWER_R_14	=  90-60;
int CHeadFaceFRIRTAI::MAX_LIPSLOWER_R_14	=  90+60;
int CHeadFaceFRIRTAI::MIN_LIPSLOWER_L_15	=  90-60;
int CHeadFaceFRIRTAI::MAX_LIPSLOWER_L_15	=  90+60;
int CHeadFaceFRIRTAI::MIN_LIPSCENTER_16	=  80-20;
int CHeadFaceFRIRTAI::MAX_LIPSCENTER_16	=  80+55;


CHeadFaceFRIRTAI::CHeadFaceFRIRTAI()
{
	headface232 = new HeadFaceRS232();
	cout << "[CHeadFaceFRIRTAI] : HEADFACEFRI_HeadFaceRS232 Create OK.." << endl;

	robotConfig = new CRobotConfig(FRILimits);

	if(robotConfig->loadConfig("FRI", "headface")){
		setLimits();
		//cout << "[CHeadFaceFRIRTAI]Limits: " << FRILimits["MAX_LIPSCENTER_16"] << endl;
	}



}

/**
 *
 * A Destructor.
 * Close FIFO files.
 *
 * @param None.
 *
 * @return None.
 *
 */
CHeadFaceFRIRTAI::~CHeadFaceFRIRTAI()
{
	cout << "[CHeadFaceFRIRTAI] : Destroy Sole Instance.." << endl;

	if(robotConfig){
		delete robotConfig;
		robotConfig = NULL;
	}

	if(headface232){
		delete headface232;
		headface232 = NULL;
	}
}


CHeadFaceFRIRTAI* CHeadFaceFRIRTAI::getInstance()
{
	static CHeadFaceFRIRTAI thisInstance;
    cout << "[CHeadFaceFRIRTAI.getInstance] : Create Sole Instance(HeadFace).." << endl;
    return &thisInstance;
}

/**
 *
 * emotionID�좎룞���좎뙏�먯삕�좎떦占�吏멨뜝�숈삕 �쒎뜝�숈삕�좑옙 �좎룞�쇿뜝�숈삕�좎룞�쇿뜝占��쒎뜝�숈삕 �좎룞��
 *
 * @param emotionID an integer argument. 癰덂뜝�숈삕 �좎룞�� 1:�좎룞�쇿뜝占� 2:�좎룞��3:�좎떖占� 4: �좎떕占썲뜝�숈삕, 5: �좎룞�� 6:�좎떎恝��
 * @param intensity an integer argument. �좎룞�쇿뜝占��좎룞�쇿뜝�숈삕. �좎룞�쇿뜝�숈삕 夷⒴뜝�숈삕�좎룞�쇿뜝占��좎룞�쇿뜝占�
 *
 * @return 1 : FAIL  0 : SUCCESS
 *
 */

void CHeadFaceFRIRTAI::setLimits()
{

	MIN_SPEED =(int) FRILimits["MIN_SPEED"];
	MAX_SPEED =(int) FRILimits["MAX_SPEED"];
	MIN_EYEBROW_R_ROLL_00	=(int)  FRILimits["MIN_EYEBROW_R_ROLL_00"];
	MAX_EYEBROW_R_ROLL_00	=(int)  FRILimits["MAX_EYEBROW_R_ROLL_00"];
	MIN_EYEBROW_L_ROLL_01	=(int)  FRILimits["MIN_EYEBROW_L_ROLL_01"];
	MAX_EYEBROW_L_ROLL_01	=(int)  FRILimits["MAX_EYEBROW_L_ROLL_01"];
	MIN_EYEBROW_R_UD_02		=(int)  FRILimits["MIN_EYEBROW_R_UD_02"];
	MAX_EYEBROW_R_UD_02		=(int)  FRILimits["MAX_EYEBROW_R_UD_02"];
	MIN_EYEBROW_L_UD_03		=(int)  FRILimits["MIN_EYEBROW_L_UD_03"];
	MAX_EYEBROW_L_UD_03		=(int)  FRILimits["MAX_EYEBROW_L_UD_03"];
	MIN_UPPEREYELID_R_UD_04	=(int)  FRILimits["MIN_UPPEREYELID_R_UD_04"];
	MAX_UPPEREYELID_R_UD_04	=(int)  FRILimits["MAX_UPPEREYELID_R_UD_04"];
	MIN_UPPEREYELID_L_UD_05	=(int)  FRILimits["MIN_UPPEREYELID_L_UD_05"];
	MAX_UPPEREYELID_L_UD_05	=(int)  FRILimits["MAX_UPPEREYELID_L_UD_05"];
	MIN_LOWEREYELID_R_UD_06	=(int)  FRILimits["MIN_LOWEREYELID_R_UD_06"];
	MAX_LOWEREYELID_R_UD_06	=(int)  FRILimits["MAX_LOWEREYELID_R_UD_06"];
	MIN_LOWEREYELID_L_UD_07	=(int)  FRILimits["MIN_LOWEREYELID_L_UD_07"];
	MAX_LOWEREYELID_L_UD_07	=(int)  FRILimits["MAX_LOWEREYELID_L_UD_07"];
	MIN_PUPIL_R_UD_08		=(int)  FRILimits["MIN_PUPIL_R_UD_08"];
	MAX_PUPIL_R_UD_08		=(int)  FRILimits["MAX_PUPIL_R_UD_08"];
	MIN_PUPIL_L_UD_09		=(int)  FRILimits["MIN_PUPIL_L_UD_09"];
	MAX_PUPIL_L_UD_09		=(int)  FRILimits["MAX_PUPIL_L_UD_09"];
	MIN_PUPIL_R_RL_10		=(int)  FRILimits["MIN_PUPIL_R_RL_10"];
	MAX_PUPIL_R_RL_10		=(int)  FRILimits["MAX_PUPIL_R_RL_10"];
	MIN_PUPIL_L_RL_11		=(int)  FRILimits["MIN_PUPIL_L_RL_11"];
	MAX_PUPIL_L_RL_11		=(int)  FRILimits["MAX_PUPIL_L_RL_11"];
	MIN_LIPSUPPER_R_12	=(int)  FRILimits["MIN_LIPSUPPER_R_12"];
	MAX_LIPSUPPER_R_12	=(int)  FRILimits["MAX_LIPSUPPER_R_12"];
	MIN_LIPSUPPER_L_13	=(int)  FRILimits["MIN_LIPSUPPER_L_13"];
	MAX_LIPSUPPER_L_13	=(int)  FRILimits["MAX_LIPSUPPER_L_13"];
	MIN_LIPSLOWER_R_14	=(int)  FRILimits["MIN_LIPSLOWER_R_14"];
	MAX_LIPSLOWER_R_14	=(int)  FRILimits["MAX_LIPSLOWER_R_14"];
	MIN_LIPSLOWER_L_15	=(int)  FRILimits["MIN_LIPSLOWER_L_15"];
	MAX_LIPSLOWER_L_15	=(int)  FRILimits["MAX_LIPSLOWER_L_15"];
	MIN_LIPSCENTER_16	=(int)  FRILimits["MIN_LIPSCENTER_16"];
	MAX_LIPSCENTER_16	=(int)  FRILimits["MAX_LIPSCENTER_16"];
}

int  CHeadFaceFRIRTAI::on()
{
	return 0;
}

int  CHeadFaceFRIRTAI::off()
{
	return 0;
}

int CHeadFaceFRIRTAI::express(string emotion, double intensity, int duration )
{
	return 0;
}

/**
 *
 * motor�좎룞���좎룞�쇿뜝�뱄옙 �좎룞�숈튂�좑옙 �좎룞�쇿뜝�숈삕 �좎떛�몄삕 �좑옙.
 *
 * @param motorID an integer argument. �좎룞�숂돌�좎룞���у뜝�숈삕 �룟뜝�ワ옙 .
 * @param speed an integer argument. �좎뙂�몄삕 0~100 �좎룞�쇿뜝占��붷뜝占�
 * @param position an integer argument. �좎떛�몄삕�좑옙 �좎룞�숈튂.
 *
 * @return 1 : FAIL  0 : SUCCESS
 *
 */

int CHeadFaceFRIRTAI::moveAbsolutePosition( int motorID, int speed, int position )
{
	ROS_DEBUG("CHeadFaceFRIRTAI::moveAbsolutePosition called %d, %d, %d", motorID, speed, position);
	//cout << "id : " << motorID << ", speed : " << speed << ", position :: " << position << endl;
	// Validate Velocity..
    if ( speed > MAX_SPEED )
        speed = MAX_SPEED;
    else if ( speed < MIN_SPEED )
        speed = MIN_SPEED;

	speed = speed*2.55;

	switch(motorID)
	{
		case 0 :
			if ( position > MAX_EYEBROW_R_ROLL_00 )         position = MAX_EYEBROW_R_ROLL_00;
			else if ( position < MIN_EYEBROW_R_ROLL_00 )    position = MIN_EYEBROW_R_ROLL_00;
			break;
		case 1 :
			if ( position > MAX_EYEBROW_L_ROLL_01 )         position = MAX_EYEBROW_L_ROLL_01;
			else if ( position < MIN_EYEBROW_L_ROLL_01 )    position = MIN_EYEBROW_L_ROLL_01;
			break;
		case 2 :
			if ( position > MAX_EYEBROW_R_UD_02 )         position = MAX_EYEBROW_R_UD_02;
			else if ( position < MIN_EYEBROW_R_UD_02 )    position = MIN_EYEBROW_R_UD_02;
			break;
		case 3 :
			if ( position > MAX_EYEBROW_L_UD_03 )         position = MAX_EYEBROW_L_UD_03;
			else if ( position < MIN_EYEBROW_L_UD_03 )    position = MIN_EYEBROW_L_UD_03;
			break;
		case 4 :
			if ( position > MAX_UPPEREYELID_R_UD_04 )         position = MAX_UPPEREYELID_R_UD_04;
			else if ( position < MIN_UPPEREYELID_R_UD_04 )    position = MIN_UPPEREYELID_R_UD_04;
			break;
		case 5 :
			if ( position > MAX_UPPEREYELID_L_UD_05 )         position = MAX_UPPEREYELID_L_UD_05;
			else if ( position < MIN_UPPEREYELID_L_UD_05 )    position = MIN_UPPEREYELID_L_UD_05;
			break;
		case 6 :
			if ( position > MAX_LOWEREYELID_R_UD_06 )         position = MAX_LOWEREYELID_R_UD_06;
			else if ( position < MIN_LOWEREYELID_R_UD_06 )    position = MIN_LOWEREYELID_R_UD_06;
			break;
		case 7 :
			if ( position > MAX_LOWEREYELID_L_UD_07 )         position = MAX_LOWEREYELID_L_UD_07;
			else if ( position < MIN_LOWEREYELID_L_UD_07 )    position = MIN_LOWEREYELID_L_UD_07;
			break;
		case 8 :
			if ( position > MAX_PUPIL_R_UD_08 )         position = MAX_PUPIL_R_UD_08;
			else if ( position < MIN_PUPIL_R_UD_08 )    position = MIN_PUPIL_R_UD_08;
			break;
		case 9 :
			if ( position > MAX_PUPIL_L_UD_09 )         position = MAX_PUPIL_L_UD_09;
			else if ( position < MIN_PUPIL_L_UD_09 )    position = MIN_PUPIL_L_UD_09;
			break;
		case 10 :
			if ( position > MAX_PUPIL_R_RL_10 )         position = MAX_PUPIL_R_RL_10;
			else if ( position < MIN_PUPIL_R_RL_10 )    position = MIN_PUPIL_R_RL_10;
			break;
		case 11 :
			if ( position > MAX_PUPIL_L_RL_11 )         position = MAX_PUPIL_L_RL_11;
			else if ( position < MIN_PUPIL_L_RL_11 )    position = MIN_PUPIL_L_RL_11;
			break;
		case 12 :
			if ( position > MAX_LIPSUPPER_R_12 )         position = MAX_LIPSUPPER_R_12;
		    else if ( position < MIN_LIPSUPPER_R_12 )    position = MIN_LIPSUPPER_R_12;
			break;
		case 13 :
			if ( position > MAX_LIPSUPPER_L_13 )         position = MAX_LIPSUPPER_L_13;
			else if ( position < MIN_LIPSUPPER_L_13 )    position = MIN_LIPSUPPER_L_13;
			break;
		case 14 :
			if ( position > MAX_LIPSLOWER_R_14 )         position = MAX_LIPSLOWER_R_14;
			else if ( position < MIN_LIPSLOWER_R_14 )    position = MIN_LIPSLOWER_R_14;
			break;
		case 15 :
			if ( position > MAX_LIPSLOWER_L_15 )         position = MAX_LIPSLOWER_L_15;
			else if ( position < MIN_LIPSLOWER_L_15 )    position = MIN_LIPSLOWER_L_15;
			break;
		case 16 :
			if ( position > MAX_LIPSCENTER_16 )         position = MAX_LIPSCENTER_16;
			else if ( position < MIN_LIPSCENTER_16 )    position = MIN_LIPSCENTER_16;
			break;
	}

	FriHeadfaceCmdfifo.cmd = FRI_HEADFACE_CMDFIFO_CMD_MOVEABSOLUTEPOSTION;
	FriHeadfaceCmdfifo.motorID 	= motorID;
	FriHeadfaceCmdfifo.speed 	= speed;
	FriHeadfaceCmdfifo.position = position;

	int result = headface232->sendMessageToHeadface(&FriHeadfaceCmdfifo);
	return result;
}


int CHeadFaceFRIRTAI::moveAbsolutePosition( int motorID, double degree, int speed )
{
	ROS_DEBUG("CHeadFaceFRIRTAI::moveAbsolutePosition called %d, %f, %d", motorID, degree, speed);
	//cout << "id : " << motorID << ", speed : " << speed << ", position :: " << position << endl;
	// Validate Velocity..
    if ( speed > MAX_SPEED )
        speed = MAX_SPEED;
    else if ( speed < MIN_SPEED )
        speed = MIN_SPEED;

	speed = speed*2.55;

	int  position= (int)degree;

	switch(motorID)
	{
		case 0 :
			if ( position > MAX_EYEBROW_R_ROLL_00 )         position = MAX_EYEBROW_R_ROLL_00;
			else if ( position < MIN_EYEBROW_R_ROLL_00 )    position = MIN_EYEBROW_R_ROLL_00;
			break;
		case 1 :
			if ( position > MAX_EYEBROW_L_ROLL_01 )         position = MAX_EYEBROW_L_ROLL_01;
			else if ( position < MIN_EYEBROW_L_ROLL_01 )    position = MIN_EYEBROW_L_ROLL_01;
			break;
		case 2 :
			if ( position > MAX_EYEBROW_R_UD_02 )         position = MAX_EYEBROW_R_UD_02;
			else if ( position < MIN_EYEBROW_R_UD_02 )    position = MIN_EYEBROW_R_UD_02;
			break;
		case 3 :
			if ( position > MAX_EYEBROW_L_UD_03 )         position = MAX_EYEBROW_L_UD_03;
			else if ( position < MIN_EYEBROW_L_UD_03 )    position = MIN_EYEBROW_L_UD_03;
			break;
		case 4 :
			if ( position > MAX_UPPEREYELID_R_UD_04 )         position = MAX_UPPEREYELID_R_UD_04;
			else if ( position < MIN_UPPEREYELID_R_UD_04 )    position = MIN_UPPEREYELID_R_UD_04;
			break;
		case 5 :
			if ( position > MAX_UPPEREYELID_L_UD_05 )         position = MAX_UPPEREYELID_L_UD_05;
			else if ( position < MIN_UPPEREYELID_L_UD_05 )    position = MIN_UPPEREYELID_L_UD_05;
			break;
		case 6 :
			if ( position > MAX_LOWEREYELID_R_UD_06 )         position = MAX_LOWEREYELID_R_UD_06;
			else if ( position < MIN_LOWEREYELID_R_UD_06 )    position = MIN_LOWEREYELID_R_UD_06;
			break;
		case 7 :
			if ( position > MAX_LOWEREYELID_L_UD_07 )         position = MAX_LOWEREYELID_L_UD_07;
			else if ( position < MIN_LOWEREYELID_L_UD_07 )    position = MIN_LOWEREYELID_L_UD_07;
			break;
		case 8 :
			if ( position > MAX_PUPIL_R_UD_08 )         position = MAX_PUPIL_R_UD_08;
			else if ( position < MIN_PUPIL_R_UD_08 )    position = MIN_PUPIL_R_UD_08;
			break;
		case 9 :
			if ( position > MAX_PUPIL_L_UD_09 )         position = MAX_PUPIL_L_UD_09;
			else if ( position < MIN_PUPIL_L_UD_09 )    position = MIN_PUPIL_L_UD_09;
			break;
		case 10 :
			if ( position > MAX_PUPIL_R_RL_10 )         position = MAX_PUPIL_R_RL_10;
			else if ( position < MIN_PUPIL_R_RL_10 )    position = MIN_PUPIL_R_RL_10;
			break;
		case 11 :
			if ( position > MAX_PUPIL_L_RL_11 )         position = MAX_PUPIL_L_RL_11;
			else if ( position < MIN_PUPIL_L_RL_11 )    position = MIN_PUPIL_L_RL_11;
			break;
		case 12 :
			if ( position > MAX_LIPSUPPER_R_12 )         position = MAX_LIPSUPPER_R_12;
		    else if ( position < MIN_LIPSUPPER_R_12 )    position = MIN_LIPSUPPER_R_12;
			break;
		case 13 :
			if ( position > MAX_LIPSUPPER_L_13 )         position = MAX_LIPSUPPER_L_13;
			else if ( position < MIN_LIPSUPPER_L_13 )    position = MIN_LIPSUPPER_L_13;
			break;
		case 14 :
			if ( position > MAX_LIPSLOWER_R_14 )         position = MAX_LIPSLOWER_R_14;
			else if ( position < MIN_LIPSLOWER_R_14 )    position = MIN_LIPSLOWER_R_14;
			break;
		case 15 :
			if ( position > MAX_LIPSLOWER_L_15 )         position = MAX_LIPSLOWER_L_15;
			else if ( position < MIN_LIPSLOWER_L_15 )    position = MIN_LIPSLOWER_L_15;
			break;
		case 16 :
			if ( position > MAX_LIPSCENTER_16 )         position = MAX_LIPSCENTER_16;
			else if ( position < MIN_LIPSCENTER_16 )    position = MIN_LIPSCENTER_16;
			break;
	}

	FriHeadfaceCmdfifo.cmd = FRI_HEADFACE_CMDFIFO_CMD_MOVEABSOLUTEPOSTION;
	FriHeadfaceCmdfifo.motorID 	= motorID;
	FriHeadfaceCmdfifo.speed 	= speed;
	FriHeadfaceCmdfifo.position = position;

	int result = headface232->sendMessageToHeadface(&FriHeadfaceCmdfifo);
	return result;
}


/**
 *
 * �좎뙃�쎌삕�좑옙 �좎룞�쇿뜝�숈삕�좑옙. �좎룞�쇿뜝�숈삕�у뜝�숈삕 �좎룞���좎룞�숁콆 �좎룞�쇿뜝占��у뜝�숈삕�좎룞�� �쒎뜝�숈삕�좑옙.
 *
 * @param phoneID an integer argument. �좎룞�쇿뜝占��덂뜝�ワ옙.
 *
 * @return 1 : FAIL  0 : SUCCESS
 *
 */
int CHeadFaceFRIRTAI::moveLip( string visemeTime )
{
	//cout << "phoneID : " << phoneID << endl;
	//

	/*
	switch(phoneID)
	{
	case 1 : //�좎룞��
		moveAbsolutePosition(12,255,65);
		moveAbsolutePosition(13,255,115);
		moveAbsolutePosition(14,255,115);
		moveAbsolutePosition(15,255,65);
		moveAbsolutePosition(16,255,90);
		break;
	case 2 : //�좑옙
		moveAbsolutePosition(12,255,65);
		moveAbsolutePosition(13,255,115);
		moveAbsolutePosition(14,255,90);
		moveAbsolutePosition(15,255,90);
		moveAbsolutePosition(16,255,110);
		break;
	case 3 : //梨�
		moveAbsolutePosition(12,255,85);
		moveAbsolutePosition(13,255,95);
		moveAbsolutePosition(14,255,90);
		moveAbsolutePosition(15,255,90);
		moveAbsolutePosition(16,255,110);
		break;

	case 4 : //��
		moveAbsolutePosition(12,255,60);
		moveAbsolutePosition(13,255,120);
		moveAbsolutePosition(14,255,75);
		moveAbsolutePosition(15,255,105);
		moveAbsolutePosition(16,255,110);
		break;

	case 5 : //��
		moveAbsolutePosition(12,255,85);
		moveAbsolutePosition(13,255,95);
		moveAbsolutePosition(14,255,90);
		moveAbsolutePosition(15,255,90);
		moveAbsolutePosition(16,255,80);
		break;

	case 6 : //汝�
		moveAbsolutePosition(12,255,85);
		moveAbsolutePosition(13,255,95);
		moveAbsolutePosition(14,255,100);
		moveAbsolutePosition(15,255,80);
		moveAbsolutePosition(16,255,75);
		break;

	case 7 : //��
		moveAbsolutePosition(12,255,85);
		moveAbsolutePosition(13,255,95);
		moveAbsolutePosition(14,255,110);
		moveAbsolutePosition(15,255,70);
		moveAbsolutePosition(16,255,80);
		break;

	case 8 : //移잌뜝占�
		moveAbsolutePosition(12,255,95);
		moveAbsolutePosition(13,255,85);
		moveAbsolutePosition(14,255,85);
		moveAbsolutePosition(15,255,95);
		moveAbsolutePosition(16,255,75);
		break;

	case 9 : //sil
		break;	//

	case 10 : //free
		moveAbsolutePosition(12,255,80);
		moveAbsolutePosition(13,255,100);
		moveAbsolutePosition(14,255,100);
		moveAbsolutePosition(15,255,80);
		moveAbsolutePosition(16,255,80);
		break;
	}
	*/
	return 0;
}


int CHeadFaceFRIRTAI::moveLipViseme( int visemeID )
{
	//cout << "phoneID : " << phoneID << endl;
	//
	ROS_DEBUG("CHeadFaceFRIRTAI : moveLipViseme called");
	switch(visemeID)
	{
	case 0 : //VISEME 1 silence
		moveAbsolutePosition(12,255,90+5);
		moveAbsolutePosition(13,255,90-5);
		moveAbsolutePosition(14,255,90-10);
		moveAbsolutePosition(15,255,90+10);
		moveAbsolutePosition(16,255,90-10);
		break;
	case 1 : //VISEME 2 ae, ax, ah
		moveAbsolutePosition(12,255,90-5);
		moveAbsolutePosition(13,255,90+5);
		moveAbsolutePosition(14,255,90+5);
		moveAbsolutePosition(15,255,90-5);
		moveAbsolutePosition(16,255,90-20);
		break;
	case 2 : //VISEME 3 aa
		moveAbsolutePosition(12,255,90-20);
		moveAbsolutePosition(13,255,90+20);
		moveAbsolutePosition(14,255,90+25);
		moveAbsolutePosition(15,255,90-25);
		moveAbsolutePosition(16,255,90+20);
		break;

	case 3 : //VISEME 4 ao
		moveAbsolutePosition(12,255,90-15);
		moveAbsolutePosition(13,255,90+15);
		moveAbsolutePosition(14,255,90+15);
		moveAbsolutePosition(15,255,90-15);
		moveAbsolutePosition(16,255,90+10);
		break;
	case 4 : //VISEME 5 ey, eh, uh
		moveAbsolutePosition(12,255,90);
		moveAbsolutePosition(13,255,90);
		moveAbsolutePosition(14,255,90+15);
		moveAbsolutePosition(15,255,90-15);
		moveAbsolutePosition(16,255,90-20);
		break;

	case 5 : //VISEME 6 er
		moveAbsolutePosition(12,255,90-20);
		moveAbsolutePosition(13,255,90+20);
		moveAbsolutePosition(14,255,90);
		moveAbsolutePosition(15,255,90);
		moveAbsolutePosition(16,255,90+20);
		break;

	case 6 : //VISEME 7 y, iy, ih, ix
		moveAbsolutePosition(12,255,90-20);
		moveAbsolutePosition(13,255,90+20);
		moveAbsolutePosition(14,255,90);
		moveAbsolutePosition(15,255,90);
		moveAbsolutePosition(16,255,90-20);
		break;

	case 7 : //VISEME 8 w, uw
		moveAbsolutePosition(12,255,90-10);
		moveAbsolutePosition(13,255,90+10);
		moveAbsolutePosition(14,255,90-15);
		moveAbsolutePosition(15,255,90+15);
		moveAbsolutePosition(16,255,90+20);
		break;

	case 8 : //VISEME 9 ow
		moveAbsolutePosition(12,255,90-20);
		moveAbsolutePosition(13,255,90+20);
		moveAbsolutePosition(14,255,90);
		moveAbsolutePosition(15,255,90);
		moveAbsolutePosition(16,255,90+15);
		break;

	case 9 : //VISEME 10 aw
		moveAbsolutePosition(12,255,90-20);
		moveAbsolutePosition(13,255,90+20);
		moveAbsolutePosition(14,255,90+30);
		moveAbsolutePosition(15,255,90-30);
		moveAbsolutePosition(16,255,90+20);
		break;
	case 10 : //VISEME 11 oy
		moveAbsolutePosition(12,255,90-15);
		moveAbsolutePosition(13,255,90+15);
		moveAbsolutePosition(14,255,90+40);
		moveAbsolutePosition(15,255,90-40);
		moveAbsolutePosition(16,255,90+35);
		break;
	case 11 : //VISEME 12 ay
		moveAbsolutePosition(12,255,90-10);
		moveAbsolutePosition(13,255,90+10);
		moveAbsolutePosition(14,255,90+30);
		moveAbsolutePosition(15,255,90-30);
		moveAbsolutePosition(16,255,90-20);
		break;
	case 12 : //VISEME 13 h
		moveAbsolutePosition(12,255,90+5);
		moveAbsolutePosition(13,255,90-5);
		moveAbsolutePosition(14,255,90);
		moveAbsolutePosition(15,255,90);
		moveAbsolutePosition(16,255,90-20);
		break;
	case 13 : //VISEME 14 r
		moveAbsolutePosition(12,255,90);
		moveAbsolutePosition(13,255,90);
		moveAbsolutePosition(14,255,90+5);
		moveAbsolutePosition(15,255,90-5);
		moveAbsolutePosition(16,255,90+20);
		break;
	case 14 : //VISEME 15 l
		moveAbsolutePosition(12,255,90-15);
		moveAbsolutePosition(13,255,90+15);
		moveAbsolutePosition(14,255,90+10);
		moveAbsolutePosition(15,255,90-10);
		moveAbsolutePosition(16,255,90+20);
		break;
	case 15 : //VISEME 16 s, z
		moveAbsolutePosition(12,255,90-10);
		moveAbsolutePosition(13,255,90+10);
		moveAbsolutePosition(14,255,90);
		moveAbsolutePosition(15,255,90);
		moveAbsolutePosition(16,255,90-20);
		break;
	case 16 : //VISEME 17 sh, ch, jh, zh
		moveAbsolutePosition(12,255,90-30);
		moveAbsolutePosition(13,255,90+30);
		moveAbsolutePosition(14,255,90);
		moveAbsolutePosition(15,255,90);
		moveAbsolutePosition(16,255,90+20);
		break;
	case 17 : //VISEME 18 th, dh
		moveAbsolutePosition(12,255,90-10);
		moveAbsolutePosition(13,255,90+10);
		moveAbsolutePosition(14,255,90-10);
		moveAbsolutePosition(15,255,90+10);
		moveAbsolutePosition(16,255,90-20);
		break;
	case 18 : //VISEME 19 f, v
		moveAbsolutePosition(12,255,90-5);
		moveAbsolutePosition(13,255,90+5);
		moveAbsolutePosition(14,255,90-10);
		moveAbsolutePosition(15,255,90+10);
		moveAbsolutePosition(16,255,90+10);
		break;
	case 19 : //VISEME 20 d, t, n
		moveAbsolutePosition(12,255,90-15);
		moveAbsolutePosition(13,255,90+15);
		moveAbsolutePosition(14,255,90-5);
		moveAbsolutePosition(15,255,90+5);
		moveAbsolutePosition(16,255,90-20);
		break;
	case 20 : //VISEME 21 k, g, ng
		moveAbsolutePosition(12,255,90-30);
		moveAbsolutePosition(13,255,90+30);
		moveAbsolutePosition(14,255,90-10);
		moveAbsolutePosition(15,255,90+10);
		moveAbsolutePosition(16,255,90+10);
		break;
	case 21 : //VISEME 22 p, b, m
		moveAbsolutePosition(12,255,90+10);
		moveAbsolutePosition(13,255,90-10);
		moveAbsolutePosition(14,255,90-5);
		moveAbsolutePosition(15,255,90+5);
		moveAbsolutePosition(16,255,90-10);
		break;
	case 22: // do nothing
		break;
	default:
		break;
	}

	return 0;
}

int CHeadFaceFRIRTAI::changeAvatar(int avatarType) {
	return 0;
}


