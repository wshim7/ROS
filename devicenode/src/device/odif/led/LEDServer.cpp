#include "LEDServer.h"

CLightEmittingDiodeServerProxy::CLightEmittingDiodeServerProxy() {
	
    int typeOfRobot = CConfig::getInstance()->getParamValueInt( "ROBOT_TYPE" );
    int typeOfServerDevice	= CConfig::getInstance()->getParamValueInt( "SERVER_DEVICE_TYPE" );

	switch (typeOfRobot) {

	case ROBOT_TYPE_EROBOT: // E-Robot

		if(typeOfServerDevice == SERVER_DEVICE_MOCK) {
			lightEmittingDiode = new CLightEmittingDiodeMock();
		} else{
			lightEmittingDiode = new CLightEmittingDiodeERobot();
		}
		break;
	case ROBOT_TYPE_MERO: // MERO 3
		if(typeOfServerDevice == SERVER_DEVICE_MOCK) {
			lightEmittingDiode = new CLightEmittingDiodeMock();
		}else{
			lightEmittingDiode = new CLightEmittingDiodeMero();
		}
		break;

	case ROBOT_TYPE_MERO_S: //MERO_S
		if(typeOfServerDevice == SERVER_DEVICE_MOCK) {
			lightEmittingDiode = new CLightEmittingDiodeMock();
		}else{
			lightEmittingDiode = new CLightEmittingDiodeMero();
		}
		break;
	default:
		cout << "!!!! No matching robot type  !!!! " << typeOfRobot << endl;
		lightEmittingDiode = new CLightEmittingDiodeMock();
		break;
	}

}


CLightEmittingDiodeServerProxy::~CLightEmittingDiodeServerProxy()
{
}


CLightEmittingDiodeServerProxy* CLightEmittingDiodeServerProxy::getInstance()
{
	static CLightEmittingDiodeServerProxy instance;
    return &instance;
}


int CLightEmittingDiodeServerProxy::on( int id, int color )
{
	//cout << "id : " << id << "  , color : " << color << endl;
	//return 0;
    
	return lightEmittingDiode->on( id, color );
}

int CLightEmittingDiodeServerProxy::on(int id, unsigned char bright, unsigned char red, unsigned char green, unsigned char blue) {
   		
//   	cout << "id : " << id << "  , bright : " << bright << endl;
//	cout << "id : " << id << "red : " << red << "  , green : " << green << "  , blue : " << blue << endl;

	lightEmittingDiode->on( id, bright, red, green, blue);
	return 0;
}

