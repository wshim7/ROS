#include "FRITester.h"
#include <sstream>

using namespace std;


void Sleep(int mills) {
	ros::Duration d(mills/1000.);
	d.sleep();
}

CFRITester::CFRITester(void)
{
	this->headface = CHeadFaceClientProxy::newInstance();
	this->pantilt = CPanTiltClientProxy::newInstance();
	this->rollbend = CRollBendClientProxy::newInstance();
}

CFRITester::~CFRITester(void)
{
	if(headface){
		delete headface;
		headface =NULL;
	}

	if(rollbend){
		delete rollbend;
		rollbend =NULL;
	}

	if(pantilt){
		delete pantilt;
		pantilt =NULL;
	}
}

void CFRITester::runTester()
{
	int input=0;

	while(true){
		cout<< "################### FRI TESTER ###################" << endl;
		cout<< "[1] Head Face" << endl;
		cout<< "[2] Roll Bend" << endl;
		cout<< "[3] Pan Tilt" << endl;
		cout<< "[0] EXIT" << endl;
		cout<< "Input Menu: ";
		cin >> input;
		if(input ==1){
			headFaceTest();
		}else if(input ==2){
			rollBendTest();
		}else if(input ==3){
			panTiltTest();
		}else if(input ==0){
			exit(0);
		}
		else{
			cout<< "No such Menu!!! Input again!!" << endl;
		}
	}
}

int CFRITester::headFaceTest()
{
	int mode =0;
	cout<<"111111111111111"<<endl;
	while(true){
		cout<< "############ Head Face Mode #############" << endl;
		cout<< "[1] All HeadFace Component Init" << endl; 
		cout<< "[2] Set One HeadFace Component Value" << endl;
		cout<< "[3] Set All HeadFace Component Minimum Value" << endl;  
		cout<< "[4] Set All HeadFace Component Maximum Value" << endl;
		cout<< "[5] Set MoveLips" << endl;
		cout<< "[6] Set MoveLips Viseme" << endl;  	
		cout<< "[7] Previous Menu" << endl; 	
		cout<< "[8] EXIT" << endl;
		cout<< "Mode: ";
		cin >> mode;
		if(mode == 1){
			headface->moveAbsolutePosition(0, 20, 90);
			Sleep(150);
			headface->moveAbsolutePosition(1, 20, 90);
			Sleep(150);
			headface->moveAbsolutePosition(2, 20, 90);
			Sleep(150);
			headface->moveAbsolutePosition(3, 20, 90);
			Sleep(150);
			headface->moveAbsolutePosition(4, 20, 90);
			Sleep(150);
			headface->moveAbsolutePosition(5, 20, 90);
			Sleep(150);
			headface->moveAbsolutePosition(6, 20, 90);
			Sleep(150);
			headface->moveAbsolutePosition(7, 20, 90);
			Sleep(150);
			headface->moveAbsolutePosition(8, 20, 90);
			Sleep(150);
			headface->moveAbsolutePosition(9, 20, 90);
			Sleep(150);
			headface->moveAbsolutePosition(10, 20, 90);
			Sleep(150);
			headface->moveAbsolutePosition(11, 20, 90);
			Sleep(150);
			headface->moveLipViseme(0);
			
		}else if(mode ==2){
			int headid=0;
			int speed=0;
			int degree=0;
			
			while(true){
				cout<< "############ Select Head Face  Component ID #############" << endl;
				cout<< "[0] EYEBROW_R_ROLL_90+-15	[1] EYEBROW_L_ROLL_90+-15" << endl; 
				cout<< "[2] EYEBROW_R_UD_90+-10		[3] EYEBROW_L_UD_90+-10" << endl;
				cout<< "[4] UPPEREYELID_R_UD_90+-35 [5] UPPEREYELID_L_UD_90+-35 " << endl;
				cout<< "[6] LOWEREYELID_R_UD_90+-25 [7] LOWEREYEBROW_L_UD+-25" << endl;
				cout<< "[8] PUPIL_R_UD_90+-25		[9] PUPIL_L_UD_90+-25" << endl;
				cout<< "[10] PUPIL_R_RL_90+-35		[11] PUPIL_L_RL_90+-35" << endl;
				cout<< "[12] LIPSUPPER_R_90+-60		[13] LIPSUPPER_L_90+-60" << endl;
				cout<< "[14] LIPSLOWER_R_90+-60		[15] LIPSLOWER_L_90+-35" << endl;
				cout<< "[16] LIPSCENTER_80+55-20	[17] Previous"<< endl;
				cout<< "ID: ";
				cin >> headid;
				if(headid >= 0 && headid <=16){
					while(true){
						cout<< "############ Set Head Face  Component Speed #############" << endl;
						cout<< "Speed: ";
						cin >> speed;
						break;
						if(speed >=0 && speed<=100){
							break;

						}else{
							cout<< "Can't set Head Face  Component Speed!!! Input again!!" << endl;
						}

					}
					while(true){
						cout<< "############ Set Head Face  Component Degree #############" << endl;
						cout<< "Degree: ";
						cin >> degree;
						break;
						if(degree >= -360 && degree<=360){
							break;

						}else{
							cout<< "Can't set Head Face  Component Degree!!! Input again!!" << endl;
						}

					}

				}else if(headid == 17){
					break;
				}else{
					cout<< "No such Head Face  Component ID!!! Input again!!" << endl;
				}
				cout << "Input ID: " << headid << " Speed: " << speed << " Degree: " << degree << endl;
				headface->moveAbsolutePosition(headid, speed, degree);

			}

			

		}else if(mode ==3){
			headface->moveAbsolutePosition(0, 20, MIN_EYEBROW_R_ROLL_00);
			Sleep(150);
			headface->moveAbsolutePosition(1, 20, MIN_EYEBROW_L_ROLL_01);
			Sleep(150);
			headface->moveAbsolutePosition(2, 20, MIN_EYEBROW_R_UD_02);
			Sleep(150);
			headface->moveAbsolutePosition(3, 20, MIN_EYEBROW_L_UD_03);
			Sleep(150);
			headface->moveAbsolutePosition(4, 20, MIN_UPPEREYELID_R_UD_04);
			Sleep(150);
			headface->moveAbsolutePosition(5, 20, MIN_UPPEREYELID_L_UD_05);
			Sleep(150);
			headface->moveAbsolutePosition(6, 20, MIN_LOWEREYELID_R_UD_06);
			Sleep(150);
			headface->moveAbsolutePosition(7, 20, MIN_LOWEREYELID_L_UD_07);
			Sleep(150);
			headface->moveAbsolutePosition(8, 20, MIN_PUPIL_R_UD_08);
			Sleep(150);
			headface->moveAbsolutePosition(9, 20, MIN_PUPIL_L_UD_09);
			Sleep(150);
			headface->moveAbsolutePosition(10, 20, MIN_PUPIL_R_RL_10);
			Sleep(150);
			headface->moveAbsolutePosition(11, 20, MIN_PUPIL_L_RL_11);
			Sleep(150);
			headface->moveLip("7");
			Sleep(150);
			headface->moveLipViseme(0);
			//headface->moveAbsolutePosition(12, 20, MIN_LIPSUPPER_R_12);
			//Sleep(150);
			//headface->moveAbsolutePosition(13, 20, MIN_LIPSUPPER_L_13);
			//Sleep(150);
			//headface->moveAbsolutePosition(14, 20, MIN_LIPSLOWER_R_14);
			//Sleep(150);
			//headface->moveAbsolutePosition(15, 20, MIN_LIPSLOWER_L_15);
			//Sleep(150);
			//headface->moveAbsolutePosition(16, 20, MIN_LIPSCENTER_16);

		}else if(mode ==4){
			headface->moveAbsolutePosition(0, 20, MAX_EYEBROW_R_ROLL_00);
			Sleep(150);
			headface->moveAbsolutePosition(1, 20, MAX_EYEBROW_L_ROLL_01);
			Sleep(150);
			headface->moveAbsolutePosition(2, 20, MAX_EYEBROW_R_UD_02);
			Sleep(150);
			headface->moveAbsolutePosition(3, 20, MAX_EYEBROW_L_UD_03);
			Sleep(150);
			headface->moveAbsolutePosition(4, 20, MAX_UPPEREYELID_R_UD_04);
			Sleep(150);
			headface->moveAbsolutePosition(5, 20, MAX_UPPEREYELID_L_UD_05);
			Sleep(150);
			headface->moveAbsolutePosition(6, 20, MAX_LOWEREYELID_R_UD_06);
			Sleep(150);
			headface->moveAbsolutePosition(7, 20, MAX_LOWEREYELID_L_UD_07);
			Sleep(150);
			headface->moveAbsolutePosition(8, 20, MAX_PUPIL_R_UD_08);
			Sleep(150);
			headface->moveAbsolutePosition(9, 20, MAX_PUPIL_L_UD_09);
			Sleep(150);
			headface->moveAbsolutePosition(10, 20, MAX_PUPIL_R_RL_10);
			Sleep(150);
			headface->moveAbsolutePosition(11, 20, MAX_PUPIL_L_RL_11);
			Sleep(150);
			headface->moveLip("5");
			Sleep(150);
			headface->moveLipViseme(0);
			//headface->moveAbsolutePosition(12, 20, MAX_LIPSUPPER_R_12);
			//Sleep(150);
			//headface->moveAbsolutePosition(13, 20, MAX_LIPSUPPER_L_13);
			//Sleep(150);
			//headface->moveAbsolutePosition(14, 20, MAX_LIPSLOWER_R_14);
			//Sleep(150);
			//headface->moveAbsolutePosition(15, 20, MAX_LIPSLOWER_L_15);
			//Sleep(150);
			//headface->moveAbsolutePosition(16, 20, MAX_LIPSCENTER_16);

		}else if(mode ==5){
			int lipid=0;
			while(true){
				cout<< "############ Set Head Face  Move Lip ID (1~10) #############" << endl;
				cout<< "ID: ";
				cin >> lipid;

				if(lipid >= 1 && lipid<=10){
					stringstream ss;
					ss<<lipid;
					headface->moveLip(ss.str());
					break;

				}else{
					cout<< "Can't set Head Face  Component Degree!!! Input again!!" << endl;
				}

			}
		}else if(mode ==6){
			int lipid=0;
			while(true){
				cout<< "############ Set Head Face  Move Lip Viseme ID (0~22) #############" << endl;
				cout<< "ID: ";
				cin >> lipid;

				if(lipid >= 0 && lipid<=22){
					headface->moveLipViseme(lipid);
					break;

				}else{
					cout<< "Can't set Head Face  Component Degree!!! Input again!!" << endl;
				}

			}
		}else if(mode == 7){
			break;
		}else if(mode == 8){
			cout<<"terminated...."<<endl;
			exit(0);
		}else{
			cout<< "No such Menu!!! Input again!!" << endl;
		}

	}

	return 0;

}

int CFRITester::rollBendTest()
{
	int mode =0;
	double roll = 0.0;
	double bend = 0.0;
	int speed =0;

	while(true){
		cout<< "############ Roll Bend Mode #############" << endl;
		cout<< "[1] All Roll Bend Init" << endl; 
		cout<< "[2] Set One Roll Bend Component Value" << endl;
		cout<< "[3] Set Roll Bend Minimum value" << endl; 
		cout<< "[4] Set Roll Bend Maximum Value" << endl;
		cout<< "[5] Previous Menu" << endl;	
		cout<< "[6] EXIT" << endl;
		cout<< "[7] Roll Bend Encoder Positions" << endl;
		cout<< "Mode: ";
		cin >> mode;
		system("cls");
		if(mode == 1){
			rollbend->moveToHome(20.0);
		}else if(mode ==2){
			while(true){
				cout<< "############ Set Roll Degree (-40.0 ~ 40.0)#############" << endl;
				cout<< "Roll: ";
				cin >> roll;

				if(roll >=-360&& roll<=360){
					break;

				}else{
					cout<< "Can't set Roll Degree !!! Input again!!" << endl;
				}
			}

			while(true){
				cout<< "############ Set Bend Degree (-45.0 ~ 40.0)#############" << endl;
				cout<< "Bend: ";
				cin >> bend;

				if(bend >=-360 && bend<=360){
					break;

				}else{
					cout<< "Can't set Bend Degree !!! Input again!!" << endl;
				}
			}

			while(true){
				cout<< "############ Set Roll Bend  Component Speed (0 ~ 100)#############" << endl;
				cout<< "Speed: ";
				cin >> speed;

				if(speed >=0 && speed<=100){
					break;

				}else{
					cout<< "Can't set Roll Bend  Component Speed!!! Input again!!" << endl;
				}
			}
			cout << "Roll: " << roll << " Bend: " << bend << " Speed: " << speed << endl;
			rollbend->moveToAbsolutePosition(roll,bend,speed);

		}else if(mode ==3){
			rollbend->moveToAbsolutePosition(-40.0,  -45.0, 20);

		}else if(mode ==4){
			rollbend->moveToAbsolutePosition(40.0,  40.0, 20);

		}else if(mode ==5){
			break;
		}else if(mode == 6){
			exit(0);
		}else if(mode == 7){
			CRollBendPosition pos;
			rollbend->getPosition(pos);

			cout << "Roll: " << pos.getDegreeRoll() << endl;
			cout << "Bend: " << pos.getDegreeBend() << endl;
		}else{
			cout<< "No such Menu!!! Input again!!" << endl;
		}

	}
	return 0;
}

int CFRITester::panTiltTest()
{
	int mode =0;
	double pan =0.0;
	double tilt = 0.0;
	int speed = 0;

	while(true){
		cout<< "############ Pan Tilt Mode #############" << endl;
		cout<< "[1] All Pan Tilt Init" << endl; 
		cout<< "[2] Set One Pan Tilt Component Value" << endl;
		cout<< "[3] Set Pan Tilt Minimum value" << endl; 
		cout<< "[4] Set All Pan Tilt Component Maximum Value" << endl;
		cout<< "[5] Previous Menu" << endl;	
		cout<< "[6] EXIT" << endl;
		cout<< "[7] Pan Tilt Encoder Positions" << endl;
		cout<< "[8] Pan Tilt Compliance" << endl;
		cout<< "Mode: ";
		cin >> mode;
		system("cls");
		if(mode == 1){
			pantilt->moveToHome(20);
		}else if(mode ==2){
			while(true){
				cout<< "############ Set Pan Degree (-60.0 ~ 60.0)#############" << endl;
				cout<< "Pan: ";
				cin >> pan;

				if(pan >=-360&& pan<=360.0){
					break;

				}else{
					cout<< "Can't set Pan Degree !!! Input again!!" << endl;
				}
			}

			while(true){
				cout<< "############ Set Tilt Degree (-30.0 ~ 30.0)#############" << endl;
				cout<< "Tilt: ";
				cin >> tilt;

				if(tilt >=-360.0 && tilt<=360.0){
					break;

				}else{
					cout<< "Can't set Tilt Degree !!! Input again!!" << endl;
				}
			}

			while(true){
				cout<< "############ Set Pan Tilt Component Speed (0 ~ 100)#############" << endl;
				cout<< "Speed: ";
				cin >> speed;

				if(speed >=0 && speed<=100){
					break;

				}else{
					cout<< "Can't set Roll Bend  Component Speed!!! Input again!!" << endl;
				}
			}
			cout << "Pan: " << pan << " Tilt: " << tilt << " Speed: " << speed << endl;
			pantilt->moveToAbsolutePosition(pan,tilt,speed);
			
		}else if(mode ==3){
			pantilt->moveToAbsolutePosition(-60.0, -30.0, 20);
		}else if(mode ==4){
			pantilt->moveToAbsolutePosition(60.0, 30.0, 20);
		}else if(mode ==5){
			break;
		}else if(mode == 6){
			exit(0);
		}else if(mode == 7){
			CPanTiltPosition pos;
			pantilt->getPosition(pos);

			cout << "Pan: " << pos.getDegreeLeftRight() << endl;
			cout << "Tilt: " << pos.getDegreeUpDown() << endl;
		}else if(mode == 8){
			int mode;
			while(true){
				cout<< "############ Set Pan Tilt Compliance (1 ~ 7)#############" << endl;
				cout<< "############ normal: 2 attentionmode: 7" << endl;
				cout<< "mode: ";
				cin.clear();
				cin  >> mode;

				if(mode >=0 && mode<=7){
					break;

				}else{
					cout<< "Can't set compliance!! Input again!!" << endl;
				}
			}
			pantilt->setCompliance(mode);
		}else{
			cout<< "No such Menu!!! Input again!!" << endl;
		}
		exit(0);
	}
	return 0;
}

int main(int argc, char **argv) {
	ros::init(argc, argv, "FRI_tester");
	ROS_INFO("FRI tester initialized");


	CFRITester tester;
	tester.headFaceTest();
	cout<<"hahahahahahahaahah"<<endl;
	//ros::spin();
}


