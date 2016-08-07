/*
 * HeadFaceMero.cpp
 *
 *  Created on: 2014. 6. 11.
 *      Author: msyoo
 */


#include "HeadFaceServer.h"


double CHeadFaceMero::MIN_EYEBRROW_UD_DEGREE = -36.0;
double CHeadFaceMero::MIN_EYEBRROW_CW_DEGREE = -29.0;
double CHeadFaceMero::MIN_EYELID_R_UD_DEGREE = -39.0;
double CHeadFaceMero::MIN_EYELID_L_UD_DEGREE= -39.0;
double CHeadFaceMero::MIN_EYELID_R_CW_DEGREE = -80.0;
double CHeadFaceMero::MIN_PUPIL_UD_DEGREE = -27.0;
double CHeadFaceMero::MIN_PUPIL_LR_DEGREE = -27.0;
double CHeadFaceMero::MIN_LIP_U_CW_DEGREE = -55.0;
double CHeadFaceMero::MIN_LIP_L_CW_DEGREE = -55.0;
double CHeadFaceMero::MIN_LIP_C_WP = 0;
int CHeadFaceMero::MIN_FACE_SPEED = -1;

double CHeadFaceMero::MAX_EYEBRROW_UD_DEGREE = 36.0;
double CHeadFaceMero::MAX_EYEBRROW_CW_DEGREE = 29.0;
double CHeadFaceMero::MAX_EYELID_R_UD_DEGREE = 39.0;
double CHeadFaceMero::MAX_EYELID_L_UD_DEGREE = 39.0;
double CHeadFaceMero::MAX_EYELID_R_CW_DEGREE = 80.0;
double CHeadFaceMero::MAX_PUPIL_UD_DEGREE = 27.0;
double CHeadFaceMero::MAX_PUPIL_LR_DEGREE = 27.0;
double CHeadFaceMero::MAX_LIP_U_CW_DEGREE = 55.0;
double CHeadFaceMero::MAX_LIP_L_CW_DEGREE = 55.0;
double CHeadFaceMero::MAX_LIP_C_WP = 21.0;
int CHeadFaceMero::MAX_FACE_SPEED = 100;



CHeadFaceMero::CHeadFaceMero()
{
	faceDriver->getInstance();

	robotConfig = new CRobotConfig(MEROLimits);

	if(robotConfig->loadConfig("MERO", "headface")){
		setLimits();
	}
}



CHeadFaceMero::~CHeadFaceMero()
{
}


void CHeadFaceMero::setLimits()
{
	 MIN_EYEBRROW_UD_DEGREE = MEROLimits["MIN_EYEBRROW_UD_DEGREE"];
	 MIN_EYEBRROW_CW_DEGREE = MEROLimits["MIN_EYEBRROW_CW_DEGREE"];
	 MIN_EYELID_R_UD_DEGREE = MEROLimits["MIN_EYELID_R_UD_DEGREE"];
	 MIN_EYELID_L_UD_DEGREE= MEROLimits["MIN_EYELID_L_UD_DEGREE"];
	 MIN_EYELID_R_CW_DEGREE = MEROLimits["MIN_EYELID_R_CW_DEGREE"];
	 MIN_PUPIL_UD_DEGREE = MEROLimits["MIN_PUPIL_UD_DEGREE"];
	 MIN_PUPIL_LR_DEGREE = MEROLimits["MIN_PUPIL_LR_DEGREE"];
	 MIN_LIP_U_CW_DEGREE = MEROLimits["MIN_LIP_U_CW_DEGREE"];
	 MIN_LIP_L_CW_DEGREE = MEROLimits["MIN_LIP_L_CW_DEGREE"];
	 MIN_LIP_C_WP = MEROLimits["MIN_LIP_C_WP"];
	 MIN_FACE_SPEED = MEROLimits["MIN_FACE_SPEED"];

	 MAX_EYEBRROW_UD_DEGREE = MEROLimits["MAX_EYEBRROW_UD_DEGREE"];
	 MAX_EYEBRROW_CW_DEGREE = MEROLimits["MAX_EYEBRROW_CW_DEGREE"];
	 MAX_EYELID_R_UD_DEGREE = MEROLimits["MAX_EYELID_R_UD_DEGREE"];
	 MAX_EYELID_L_UD_DEGREE = MEROLimits["MAX_EYELID_L_UD_DEGREE"];
	 MAX_EYELID_R_CW_DEGREE = MEROLimits["MAX_EYELID_R_CW_DEGREE"];
	 MAX_PUPIL_UD_DEGREE = MEROLimits["MAX_PUPIL_UD_DEGREE"];
	 MAX_PUPIL_LR_DEGREE = MEROLimits["MAX_PUPIL_LR_DEGREE"];
	 MAX_LIP_U_CW_DEGREE = MEROLimits["MAX_LIP_U_CW_DEGREE"];
	 MAX_LIP_L_CW_DEGREE = MEROLimits["MAX_LIP_L_CW_DEGREE"];
	 MAX_LIP_C_WP = MEROLimits["MAX_LIP_C_WP"];
	 MAX_FACE_SPEED = MEROLimits["MAX_FACE_SPEED"];
}


CHeadFaceMero *CHeadFaceMero::getInstance()
{
	static CHeadFaceMero thisInstance;
	cout << "[CHeadFaceMero.getInstance] : Create Sole Instance(CHeadFaceMero).." << endl;
	return &thisInstance;
}

int  CHeadFaceMero::on()
{
	faceDriver->initFace();
	return 0;
}

int  CHeadFaceMero::off()
{
	return 0;
}

int CHeadFaceMero::express(string emotion, double intensity, int duration)
{
	return 0;
}



int CHeadFaceMero::moveAbsolutePosition(int motorID, int speed, int position)
{
	if(speed < MIN_FACE_SPEED)	speed = MIN_FACE_SPEED;

	if(speed > MAX_FACE_SPEED)	speed = MAX_FACE_SPEED;


	if(motorID == 0){
		if(position < MIN_EYEBRROW_UD_DEGREE) position = MIN_EYEBRROW_UD_DEGREE;

		if(position > MAX_EYEBRROW_UD_DEGREE) position = MAX_EYEBRROW_UD_DEGREE;

	}else if(motorID == 1){
		if(position < MIN_EYEBRROW_CW_DEGREE) position = MIN_EYEBRROW_CW_DEGREE;

		if(position > MAX_EYEBRROW_CW_DEGREE) position = MAX_EYEBRROW_CW_DEGREE;

	}else if(motorID == 2){
		if(position < MIN_EYELID_R_UD_DEGREE) position = MIN_EYELID_R_UD_DEGREE;

		if(position > MAX_EYELID_R_UD_DEGREE) position = MAX_EYELID_R_UD_DEGREE;

	}else if(motorID == 3){
		if(position < MIN_EYELID_L_UD_DEGREE) position = MIN_EYELID_L_UD_DEGREE;

		if(position > MAX_EYELID_L_UD_DEGREE) position = MAX_EYELID_L_UD_DEGREE;

	}else if(motorID == 4){
		if(position < MIN_EYELID_R_CW_DEGREE) position = MIN_EYELID_R_CW_DEGREE;

		if(position > MAX_EYELID_R_CW_DEGREE) position = MAX_EYELID_R_CW_DEGREE;

	}else if(motorID == 5){
		if(position < MIN_PUPIL_UD_DEGREE) position = MIN_PUPIL_UD_DEGREE;

		if(position > MAX_PUPIL_UD_DEGREE) position = MAX_PUPIL_UD_DEGREE;

	}else if(motorID == 6){
		if(position < MIN_PUPIL_LR_DEGREE) position = MIN_PUPIL_LR_DEGREE;

		if(position > MAX_PUPIL_LR_DEGREE) position = MAX_PUPIL_LR_DEGREE;

	}else if(motorID == 7){
		if(position < MIN_LIP_U_CW_DEGREE) position = MIN_LIP_U_CW_DEGREE;

		if(position > MAX_LIP_U_CW_DEGREE) position = MAX_LIP_U_CW_DEGREE;

	}else if(motorID == 8){
		if(position < MIN_LIP_L_CW_DEGREE) position = MIN_LIP_L_CW_DEGREE;

		if(position > MAX_LIP_L_CW_DEGREE) position = MAX_LIP_L_CW_DEGREE;

	}else if(motorID == 9){
		if(position < MIN_LIP_C_WP) position = MIN_LIP_C_WP;

		if(position > MAX_LIP_C_WP) position = MAX_LIP_C_WP;

	}
	//ROS_DEBUG("moveAbsolutePosition: ID: %d, Degree: %f, Speed: %d" ,motorID,  (double) position, speed );
	return faceDriver->moveAbsolutePosition(motorID,  (double) position, speed);
}

int CHeadFaceMero::moveAbsolutePosition(int motorID, double degree, int speed)
{
	if(speed < MIN_FACE_SPEED)	speed = MIN_FACE_SPEED;

	if(speed > MAX_FACE_SPEED)	speed = MAX_FACE_SPEED;


	if(motorID == 0){
		if(degree < MIN_EYEBRROW_UD_DEGREE) degree = MIN_EYEBRROW_UD_DEGREE;

		if(degree > MAX_EYEBRROW_UD_DEGREE) degree = MAX_EYEBRROW_UD_DEGREE;

	}else if(motorID == 1){
		if(degree < MIN_EYEBRROW_CW_DEGREE) degree = MIN_EYEBRROW_CW_DEGREE;

		if(degree > MAX_EYEBRROW_CW_DEGREE) degree = MAX_EYEBRROW_CW_DEGREE;

	}else if(motorID == 2){
		if(degree < MIN_EYELID_R_UD_DEGREE) degree = MIN_EYELID_R_UD_DEGREE;

		if(degree > MAX_EYELID_R_UD_DEGREE) degree = MAX_EYELID_R_UD_DEGREE;

	}else if(motorID == 3){
		if(degree < MIN_EYELID_L_UD_DEGREE) degree = MIN_EYELID_L_UD_DEGREE;

		if(degree > MAX_EYELID_L_UD_DEGREE) degree = MAX_EYELID_L_UD_DEGREE;

	}else if(motorID == 4){
		if(degree < MIN_EYELID_R_CW_DEGREE) degree = MIN_EYELID_R_CW_DEGREE;

		if(degree > MAX_EYELID_R_CW_DEGREE) degree = MAX_EYELID_R_CW_DEGREE;

	}else if(motorID == 5){
		if(degree < MIN_PUPIL_UD_DEGREE) degree = MIN_PUPIL_UD_DEGREE;

		if(degree > MAX_PUPIL_UD_DEGREE) degree = MAX_PUPIL_UD_DEGREE;

	}else if(motorID == 6){
		if(degree < MIN_PUPIL_LR_DEGREE) degree = MIN_PUPIL_LR_DEGREE;

		if(degree > MAX_PUPIL_LR_DEGREE) degree = MAX_PUPIL_LR_DEGREE;

	}else if(motorID == 7){
		if(degree < MIN_LIP_U_CW_DEGREE) degree = MIN_LIP_U_CW_DEGREE;

		if(degree > MAX_LIP_U_CW_DEGREE) degree = MAX_LIP_U_CW_DEGREE;

	}else if(motorID == 8){
		if(degree < MIN_LIP_L_CW_DEGREE) degree = MIN_LIP_L_CW_DEGREE;

		if(degree > MAX_LIP_L_CW_DEGREE) degree = MAX_LIP_L_CW_DEGREE;

	}else if(motorID == 9){
		if(degree < MIN_LIP_C_WP) degree = MIN_LIP_C_WP;

		if(degree > MAX_LIP_C_WP) degree = MAX_LIP_C_WP;

	}
	//ROS_DEBUG("moveAbsolutePositionDouble: ID: %d, Degree: %f, Speed: %d" ,motorID,  degree, speed );
	return faceDriver->moveAbsolutePosition(motorID, degree, speed);
}

int CHeadFaceMero::moveLip(string visemeTime)
{
	return 0;
}



int CHeadFaceMero::moveLipViseme(int visemeID)
{
	switch(visemeID)
	{
	case 0 : //VISEME 1 silence
		faceDriver->moveAbsolutePosition(7,-5.0,100);
		faceDriver->moveAbsolutePosition(8,-10.0,100);
		faceDriver->moveAbsolutePosition(9,6.3,100);
		break;
	case 1 : //VISEME 2 ae, ax, ah
		faceDriver->moveAbsolutePosition(7,5.0,100);
		faceDriver->moveAbsolutePosition(8,5.0,100);
		faceDriver->moveAbsolutePosition(9,0.0,100);
		break;
	case 2 : //VISEME 3 aa
		faceDriver->moveAbsolutePosition(7,20.0,100);
		faceDriver->moveAbsolutePosition(8,25,100);
		faceDriver->moveAbsolutePosition(9,25.5,100);
		break;

	case 3 : //VISEME 4 ao
		faceDriver->moveAbsolutePosition(7,15.0,100);
		faceDriver->moveAbsolutePosition(8,15.0,100);
		faceDriver->moveAbsolutePosition(9,19.1,100);
		break;
	case 4 : //VISEME 5 ey, eh, uh
		faceDriver->moveAbsolutePosition(7,0.0,100);
		faceDriver->moveAbsolutePosition(8,15.0,100);
		faceDriver->moveAbsolutePosition(9,0.0,100);
		break;

	case 5 : //VISEME 6 er
		faceDriver->moveAbsolutePosition(7,20.0,100);
		faceDriver->moveAbsolutePosition(8,0.0,100);
		faceDriver->moveAbsolutePosition(9,25.5,100);
		break;

	case 6 : //VISEME 7 y, iy, ih, ix
		faceDriver->moveAbsolutePosition(7,20.0,100);
		faceDriver->moveAbsolutePosition(8,0.0,100);
		faceDriver->moveAbsolutePosition(9,0.0,100);
		break;

	case 7 : //VISEME 8 w, uw
		faceDriver->moveAbsolutePosition(7,10.0,100);
		faceDriver->moveAbsolutePosition(8,-15.0,100);
		faceDriver->moveAbsolutePosition(9,25.5,100);
		break;

	case 8 : //VISEME 9 ow
		faceDriver->moveAbsolutePosition(7,20.0,100);
		faceDriver->moveAbsolutePosition(8,0.0,100);
		faceDriver->moveAbsolutePosition(9,22.3,100);
		break;

	case 9 : //VISEME 10 aw
		faceDriver->moveAbsolutePosition(7,20.0,100);
		faceDriver->moveAbsolutePosition(8,30.0,100);
		faceDriver->moveAbsolutePosition(9,25.5,100);
		break;
	case 10 : //VISEME 11 oy
		faceDriver->moveAbsolutePosition(7,15.0,100);
		faceDriver->moveAbsolutePosition(8,40.0,100);
		faceDriver->moveAbsolutePosition(9,35.0,100);
		break;
	case 11 : //VISEME 12 ay
		faceDriver->moveAbsolutePosition(7,10.0,100);
		faceDriver->moveAbsolutePosition(8,30.0,100);
		faceDriver->moveAbsolutePosition(9,0.0,100);
		break;
	case 12 : //VISEME 13 h
		faceDriver->moveAbsolutePosition(7,-5.0,100);
		faceDriver->moveAbsolutePosition(8,0.0,100);
		faceDriver->moveAbsolutePosition(9,25.5,100);
		break;
	case 13 : //VISEME 14 r
		faceDriver->moveAbsolutePosition(7,0.0,100);
		faceDriver->moveAbsolutePosition(8,5.0,100);
		faceDriver->moveAbsolutePosition(9,25.5,100);
		break;
	case 14 : //VISEME 15 l
		faceDriver->moveAbsolutePosition(7,15.0,100);
		faceDriver->moveAbsolutePosition(8,10.0,100);
		faceDriver->moveAbsolutePosition(9,25.5,100);
		break;
	case 15 : //VISEME 16 s, z
		faceDriver->moveAbsolutePosition(7,10.0,100);
		faceDriver->moveAbsolutePosition(8,0.0,100);
		faceDriver->moveAbsolutePosition(9,0.0,100);
		break;
	case 16 : //VISEME 17 sh, ch, jh, zh
		faceDriver->moveAbsolutePosition(7,30.0,100);
		faceDriver->moveAbsolutePosition(8,0.0,100);
		faceDriver->moveAbsolutePosition(9,25.5,100);
		break;
	case 17 : //VISEME 18 th, dh
		faceDriver->moveAbsolutePosition(7,10.0,100);
		faceDriver->moveAbsolutePosition(8,-10.0,100);
		faceDriver->moveAbsolutePosition(9,0.0,100);
		break;
	case 18 : //VISEME 19 f, v
		faceDriver->moveAbsolutePosition(7,5.0,100);
		faceDriver->moveAbsolutePosition(8,-10.0,100);
		faceDriver->moveAbsolutePosition(9,19.1,100);
		break;
	case 19 : //VISEME 20 d, t, n
		faceDriver->moveAbsolutePosition(7,15.0,100);
		faceDriver->moveAbsolutePosition(8,-5.0,100);
		faceDriver->moveAbsolutePosition(9,0.0,100);
		break;
	case 20 : //VISEME 21 k, g, ng
		faceDriver->moveAbsolutePosition(7,30.0,100);
		faceDriver->moveAbsolutePosition(8,-10.0,100);
		faceDriver->moveAbsolutePosition(9,19.1,100);
		break;
	case 21 : //VISEME 22 p, b, m
		faceDriver->moveAbsolutePosition(7,-10.0,100);
		faceDriver->moveAbsolutePosition(8,-5.0,100);
		faceDriver->moveAbsolutePosition(9,6.4,100);
		break;
	case 22: // do nothing
		break;
	default:
		break;
	}
	return 0;
}



int CHeadFaceMero::changeAvatar(int avatarType)
{
	return 0;
}
