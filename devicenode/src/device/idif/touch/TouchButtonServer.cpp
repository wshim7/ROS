#include "TouchButtonServer.h"

CTouchButtonServerProxy::CTouchButtonServerProxy()
{
	int typeOfRobot			= CConfig::getInstance()->getParamValueInt( "ROBOT_TYPE" );
	int typeOfServerDevice	= CConfig::getInstance()->getParamValueInt( "SERVER_DEVICE_TYPE" );
	
	switch (typeOfRobot) {//1=TRot/Infotainment, 2=HRobot, 3=FRI 4=KIBO 5=Engkey 6=E-Robot
	
	case ROBOT_TYPE_EROBOT: // E-Robot
		if(typeOfServerDevice == SERVER_DEVICE_MOCK) {
			touchButton = new CTouchButtonMock;
		} else {
			touchButton = new CTouchButtonERobot();
		}
		cout << " E-Robot Touch.. " << endl;
		break;
	case ROBOT_TYPE_MERO: // MERO 3
		if(typeOfServerDevice == SERVER_DEVICE_MOCK) {
			touchButton = new CTouchButtonMock();
		}else{
			touchButton = new CTouchButtonMero();
		}
		break;

	case ROBOT_TYPE_MERO_S: //MERO_S
		if(typeOfServerDevice == SERVER_DEVICE_MOCK) {
			touchButton = new CTouchButtonMock();
		}else{
			touchButton = new CTouchButtonMero();
		}
		break;
	default:
		cout << "!!!! No matching robot type  !!!! " << typeOfRobot << endl;
		touchButton = new CTouchButtonMock;
		break;
	}
	
}

CTouchButtonServerProxy::~CTouchButtonServerProxy()
{

}


CTouchButtonServerProxy* CTouchButtonServerProxy::getInstance()
{
	static CTouchButtonServerProxy instance;
	return &instance;
}

CTouchButtonData CTouchButtonServerProxy::readData( int index )
{
    return touchButton->readData( index );
}

CHeadTouchButtonData CTouchButtonServerProxy::readHeadData( int index )
{
	return CHeadTouchButtonData();
}

int CTouchButtonServerProxy::detectingError(int touchID) {
	return touchButton->detectingError(touchID);
}


