/*
 * MeroTester.cpp
 *
 *  Created on: 2014. 6. 25.
 *      Author: msyoo
 */

#include "MeroTester.h"

//#ifdef WIN32
MeroTester::MeroTester() {

	 MIN_EYEBRROW_UD_DEGREE = -36.0;
	 MIN_EYEBRROW_CW_DEGREE = -29.0;
	 MIN_EYELID_R_UD_DEGREE = -39.0;
	 MIN_EYELID_L_UD_DEGREE= -39.0;
	 MIN_EYELID_R_CW_DEGREE = -80.0;
	 MIN_PUPIL_UD_DEGREE = -27.0;
	 MIN_PUPIL_LR_DEGREE = -27.0;
	 MIN_LIP_U_CW_DEGREE = -55.0;
	 MIN_LIP_L_CW_DEGREE = -55.0;
	 MIN_LIP_C_WP = 0;
	 MIN_FACE_SPEED = -1;


	 MAX_EYEBRROW_UD_DEGREE = 36.0;
	 MAX_EYEBRROW_CW_DEGREE = 29.0;
	 MAX_EYELID_R_UD_DEGREE = 39.0;
	 MAX_EYELID_L_UD_DEGREE = 39.0;
	 MAX_EYELID_R_CW_DEGREE = 80.0;
	 MAX_PUPIL_UD_DEGREE = 27.0;
	 MAX_PUPIL_LR_DEGREE = 27.0;
	 MAX_LIP_U_CW_DEGREE = 55.0;
	 MAX_LIP_L_CW_DEGREE = 55.0;
	 MAX_LIP_C_WP = 21.0;
	 MAX_FACE_SPEED = 100;

	 CConfig* config = CConfig::getInstance();
	 int robottype = config->getParamValueInt("ROBOT_TYPE");
	 if(robottype ==  7){
			this->headface = CHeadFaceClientProxy::newInstance();
			this->pantilt = CPanTiltClientProxy::newInstance();
			this->rollbend = CRollBendClientProxy::newInstance();
	 }else if(robottype ==  8){
			this->pantilt = CPanTiltClientProxy::newInstance();
			this->rollbend = CRollBendClientProxy::newInstance();
	 }else{
		 ROS_ERROR("Not Mero Type !!! ");
		 exit(0);
	 }

}

MeroTester::~MeroTester() {
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

void MeroTester::runTester()
{
	int input=0;
	while(true){
		system("cls");
		cout<< "################### MERO TESTER ###################" << endl;
		cout<< "[1] Head Face" << endl;
		cout<< "[2] Roll Bend" << endl;
		cout<< "[3] Pan Tilt" << endl;
		cout<< "[4] Robot Init" << endl;
		cout<< "[0] EXIT" << endl;
		cout<< "Input Menu: ";
		cin >> input;
		if(input ==1){
			 CConfig* config = CConfig::getInstance();
			 int robottype = config->getParamValueInt("ROBOT_TYPE");
			 if(robottype ==  7){
				headFaceTest();
			 }else{
				 cout << "Not Mero Type !!!" << endl;
			 }
		}else if(input ==2){
			rollBendTest();
		}else if(input ==3){
			panTiltTest();
		}else if(input ==4){
			 CConfig* config = CConfig::getInstance();
			 int robottype = config->getParamValueInt("ROBOT_TYPE");
			 if(robottype ==  7){
					this->pantilt->on();
					this->headface->on();
			 }else{
				 this->pantilt->on();
			 }

		}else if(input ==0){
			ros::shutdown();
		}
		else{
			cout<< "No such Menu!!! Input again!!" << endl;
		}
	}
}



int MeroTester::headFaceTest()
{
	int mode =0;
		while(true){
			system("cls");
			cout<< "############ Head Face Mode #############" << endl;
			cout<< "[1] All HeadFace Component Init" << endl;
			cout<< "[2] Set One HeadFace Component Value" << endl;
			cout<< "[3] Set All HeadFace Component Minimum Value" << endl;
			cout<< "[4] Set All HeadFace Component Maximum Value" << endl;
			cout<< "[5] Set MoveLips Viseme" << endl;
			cout<< "[6] Previous Menu" << endl;
			cout<< "[7] EXIT" << endl;
			cout<< "Mode: ";
			cin >> mode;
			if(mode == 1){

				for(int i = 0; i < 10; i++){
					headface->moveAbsolutePosition(i, 20, 90);
				}

			}else if(mode ==2){
				int headid=0;
				int speed=0;
				int degree=0;

				while(true){
					cout<< "############ Select Head Face  Component ID #############" << endl;
					cout<< "[0] EYEBROW_UD 0+-36	[1] EYEBROW_CW 0+-29" << endl;
					cout<< "[2] EYELID_R_UD 0+-39	[3] EYELID_L_UD 0+-39" << endl;
					cout<< "[4] EYELID_ROT_CW 0+-80 [5] PUPIL_UD +-27" << endl;
					cout<< "[6] PUPIL_LR 0+-27 [7] LIP_U_CW 0+-56" << endl;
					cout<< "[8] LIP_L_CW 0+-56		[9]LIP_C_WP 0~21" << endl;
					cout<< "[10] Previous"<< endl;
					cout<< "ID: ";
					cin >> headid;
					if(headid >= 0 && headid <=9){
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

					}else if(headid == 10){
						break;
					}else{
						cout<< "No such Head Face  Component ID!!! Input again!!" << endl;
					}
					cout << "Input ID: " << headid << " Speed: " << speed << " Degree: " << degree << endl;
					headface->moveAbsolutePosition(headid, speed, degree);

				}



			}else if(mode ==3){
				headface->moveAbsolutePosition(0, 50, MIN_EYEBRROW_UD_DEGREE);

				headface->moveAbsolutePosition(1, 50, MIN_EYEBRROW_CW_DEGREE);

				headface->moveAbsolutePosition(2, 50, MIN_EYELID_R_UD_DEGREE);

				headface->moveAbsolutePosition(3, 50, MIN_EYELID_L_UD_DEGREE);

				headface->moveAbsolutePosition(4, 50, MIN_EYELID_R_CW_DEGREE);

				headface->moveAbsolutePosition(5, 50, MIN_PUPIL_UD_DEGREE);

				headface->moveAbsolutePosition(6, 50, MIN_PUPIL_LR_DEGREE);

				headface->moveAbsolutePosition(7, 50, MIN_LIP_U_CW_DEGREE);

				headface->moveAbsolutePosition(8, 50, MIN_LIP_L_CW_DEGREE);

				headface->moveAbsolutePosition(9, 50, MIN_LIP_C_WP);


			}else if(mode ==4){
				headface->moveAbsolutePosition(0, 50, MAX_EYEBRROW_UD_DEGREE);

				headface->moveAbsolutePosition(1, 50, MAX_EYEBRROW_CW_DEGREE);

				headface->moveAbsolutePosition(2, 50, MAX_EYELID_R_UD_DEGREE);

				headface->moveAbsolutePosition(3, 50, MAX_EYELID_L_UD_DEGREE);

				headface->moveAbsolutePosition(4, 50, MAX_EYELID_R_CW_DEGREE);

				headface->moveAbsolutePosition(5, 50, MAX_PUPIL_UD_DEGREE);

				headface->moveAbsolutePosition(6, 50, MAX_PUPIL_LR_DEGREE);

				headface->moveAbsolutePosition(7, 50, MAX_LIP_U_CW_DEGREE);

				headface->moveAbsolutePosition(8, 50, MAX_LIP_L_CW_DEGREE);

				headface->moveAbsolutePosition(9, 50, MAX_LIP_C_WP);

			}else if(mode ==5){
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
			}
			else if(mode == 6){
				break;
			}else if(mode == 7){
				cout<<"terminated...."<<endl;
				ros::shutdown();
			}else{
				cout<< "No such Menu!!! Input again!!" << endl;
			}

		}

		return 0;
}



int MeroTester::rollBendTest()
{
	int mode =0;
	double roll = 0.0;
	double bend = 0.0;
	int speed =0;

	while(true){
		system("cls");
		cout<< "############ Roll Bend Mode #############" << endl;
		cout<< "[1] All Roll Bend Init" << endl;
		cout<< "[2] Set One Roll Bend Component Value" << endl;
		cout<< "[3] Set Roll Bend Minimum value" << endl;
		cout<< "[4] Set Roll Bend Maximum Value" << endl;
		cout<< "[5] Previous Menu" << endl;
		cout<< "[6] Roll Bend Encoder Positions" << endl;
		cout<< "[7] EXIT" << endl;
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
			rollbend->moveToAbsolutePosition(-10.0,  -10.0, 20);

		}else if(mode ==4){
			rollbend->moveToAbsolutePosition(10.0,  10.0, 20);

		}else if(mode ==5){
			break;
		}else if(mode == 7){
			ros::shutdown();
		}else if(mode == 6){
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



int MeroTester::panTiltTest()
{
	int mode =0;
		double pan =0.0;
		double tilt = 0.0;
		int speed = 0;

		while(true){
			system("cls");
			cout<< "############ Pan Tilt Mode #############" << endl;
			cout<< "[1] All Pan Tilt Init" << endl;
			cout<< "[2] Set One Pan Tilt Component Value" << endl;
			cout<< "[3] Set Pan Tilt Minimum value" << endl;
			cout<< "[4] Set All Pan Tilt Component Maximum Value" << endl;
			cout<< "[5] Pan Tilt Encoder Positions" << endl;
			cout<< "[6] Pan Tilt Compliance" << endl;
			cout<< "[7] Previous Menu" << endl;
			cout<< "[8] EXIT" << endl;

			cout<< "Mode: ";
			cin >> mode;
			system("cls");
			if(mode == 1){
				cout << "1111111111111" <<  endl;
				pantilt->moveToHome(20);
				cout << "2222222222222" <<  endl;
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
			}else if(mode ==7){
				break;
			}else if(mode == 8){
				ros::shutdown();
			}else if(mode == 5){
				CPanTiltPosition pos;
				pantilt->getPosition(pos);

				cout << "Pan: " << pos.getDegreeLeftRight() << endl;
				cout << "Tilt: " << pos.getDegreeUpDown() << endl;
			}else if(mode == 6){
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
		}
		return 0;
}
//#endif

int main(int argc, char **argv){
//#ifdef WIN32
	ros::init(argc, argv, "MeroTester");
	MeroTester* tester = new MeroTester();
	tester->runTester();
//#endif // WIN32
	return 0;
}

