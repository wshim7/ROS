/*
 * MeroTester.h
 *
 *  Created on: 2014. 6. 25.
 *      Author: msyoo
 */

#ifndef MEROTESTER_H_
#define MEROTESTER_H_

//#ifdef WIN32
#include <iostream>
//#include <windows.h>
#include <ros/ros.h>
#include <roscir/device/client/CHeadFaceClient.h>
#include <roscir/device/client/CPanTiltClient.h>
#include <roscir/device/client/CRollBendClient.h>

using namespace std;

class MeroTester {
public:
	MeroTester();
	virtual ~MeroTester();

	void runTester();

private:
	CHeadFace* headface;
	CRollBend* rollbend;
	CPanTilt * pantilt;

	double MIN_EYEBRROW_UD_DEGREE;
	double MIN_EYEBRROW_CW_DEGREE;
	double MIN_EYELID_R_UD_DEGREE;
	double MIN_EYELID_L_UD_DEGREE;
	double MIN_EYELID_R_CW_DEGREE;
	double MIN_PUPIL_UD_DEGREE;
	double MIN_PUPIL_LR_DEGREE;
	double MIN_LIP_U_CW_DEGREE;
	double MIN_LIP_L_CW_DEGREE;
	double MIN_LIP_C_WP;
	int MIN_FACE_SPEED;


	double MAX_EYEBRROW_UD_DEGREE;
	double MAX_EYEBRROW_CW_DEGREE;
	double MAX_EYELID_R_UD_DEGREE;
	double MAX_EYELID_L_UD_DEGREE;
	double MAX_EYELID_R_CW_DEGREE;
	double MAX_PUPIL_UD_DEGREE;
	double MAX_PUPIL_LR_DEGREE;
	double MAX_LIP_U_CW_DEGREE;
	double MAX_LIP_L_CW_DEGREE;
	double MAX_LIP_C_WP;
	int MAX_FACE_SPEED;

	int headFaceTest();
	int rollBendTest();
	int panTiltTest();
};

//#endif

#endif /* MEROTESTER_H_ */
