#ifndef __CFRI_TESTER_H__
#define __CFRI_TESTER_H__

#include <iostream>
#include <ros/ros.h>
#include <roscir/device/client/CHeadFaceClient.h>
#include <roscir/device/client/CPanTiltClient.h>
#include <roscir/device/client/CRollBendClient.h>


using namespace std;

class CFRITester
{
public:
	CFRITester(void);
	~CFRITester(void);

	void runTester();
private:
	CHeadFace* headface;
	CRollBend* rollbend;
	CPanTilt * pantilt;

	static const int MIN_EYEBROW_R_ROLL_00		=  90-15;
	static const int MAX_EYEBROW_R_ROLL_00		=  90+15;
	static const int MIN_EYEBROW_L_ROLL_01		=  90-15;
	static const int MAX_EYEBROW_L_ROLL_01		=  90+15;
	static const int MIN_EYEBROW_R_UD_02		=  90-10;
	static const int MAX_EYEBROW_R_UD_02		=  90+10;
	static const int MIN_EYEBROW_L_UD_03		=  90-10;
	static const int MAX_EYEBROW_L_UD_03		=  90+10;
	static const int MIN_UPPEREYELID_R_UD_04	=  90-35;
	static const int MAX_UPPEREYELID_R_UD_04	=  90+35;
	static const int MIN_UPPEREYELID_L_UD_05	=  90-35;
	static const int MAX_UPPEREYELID_L_UD_05	=  90+35;
	static const int MIN_LOWEREYELID_R_UD_06	=  90-25;
	static const int MAX_LOWEREYELID_R_UD_06	=  90+25;
	static const int MIN_LOWEREYELID_L_UD_07	=  90-25;
	static const int MAX_LOWEREYELID_L_UD_07	=  90+25;
	static const int MIN_PUPIL_R_UD_08		=  90-25;
	static const int MAX_PUPIL_R_UD_08		=  90+25;
	static const int MIN_PUPIL_L_UD_09		=  90-25;
	static const int MAX_PUPIL_L_UD_09		=  90+25;
	static const int MIN_PUPIL_R_RL_10		=  90-35;
	static const int MAX_PUPIL_R_RL_10		=  90+35;
	static const int MIN_PUPIL_L_RL_11		=  90-35;
	static const int MAX_PUPIL_L_RL_11		=  90+35;
	static const int MIN_LIPSUPPER_R_12	=  90-60;
	static const int MAX_LIPSUPPER_R_12	=  90+60;
	static const int MIN_LIPSUPPER_L_13	=  90-60;
	static const int MAX_LIPSUPPER_L_13	=  90+60;
	static const int MIN_LIPSLOWER_R_14	=  90-60;
	static const int MAX_LIPSLOWER_R_14	=  90+60;
	static const int MIN_LIPSLOWER_L_15	=  90-60;
	static const int MAX_LIPSLOWER_L_15	=  90+60;
	static const int MIN_LIPSCENTER_16	=  80-20;
	static const int MAX_LIPSCENTER_16	=  80+55;


public:

	int headFaceTest();
	int rollBendTest();
	int panTiltTest();
	
	
};

#endif
