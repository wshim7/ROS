#pragma once
#include <iostream>
#include <map>
#include "XmlSettings.h"

using namespace std;
class CRobotConfig
{
public:
	map<string, double>* m_Limits;

	CRobotConfig(map<string, double> &limits);
	~CRobotConfig(void);
	int loadConfig(string robotType, string partName);

private:
	void readXmlValue( XmlSettings &configXML, string robotName, string partsType );
	void readXmlDoubleValue( XmlSettings &configXML, string robotName, string partsType );

	XmlSettings  configXML;
};
